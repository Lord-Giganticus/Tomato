#include "Export.h"
#define arrsize(arr) sizeof(arr)/sizeof(arr[0])

using namespace std;

BmgFileHolder* LoadBMG(char* path) {
    BmgFileHolder* res = new BmgFileHolder(path);
    res->loadBmg();
    return res;
}

BCSV* LoadBCSV(char* path) {
    return BCSV::loadBcsv(path);
}

unsigned long GetFeildCount(BCSV* ptr) {
    auto fields = ptr->mFields;
    return arrsize(fields);
}

list(Field) GetFeilds(BCSV* ptr) {
    list(Field) res;
    auto size = GetFeildCount(ptr);
    for (unsigned long i = 0; i < size; i++) {
        res.push_back(ptr->mFields[i]);
    }
    return res;
}

BMGINFO::BMGINFO(BmgFileHolder* bmg, BCSV* tbl) {
    BMG = bmg;
    TBL = tbl;
    TBLEntryNum = tbl->mEntryNum;
    TBLFieldNum = tbl->mFieldNum;
    TBLDataAdr = tbl->mDataAdr;
    TBLEntrySize = tbl->mEntrySize;
    TBLFields = tbl->mFields;
}

EXPORT BMGINFO LoadBMGInfo(char* BMGPath, char* TBLPath) {
    return BMGINFO(LoadBMG(BMGPath), LoadBCSV(TBLPath));
}

bool BMGINFO::Write(BMGINFO& info, char* XMLName) {
    const char* name = "Message.xml";
    if (XMLName != nullptr)
        name = XMLName;
    XmlWriter writer = XmlWriter(name, info.BMG, info.TBL);
    return writer.writeXml();
}

EXPORT bool ToXML(BMGINFO info, char* XMLName) {
    return BMGINFO::Write(info, XMLName);
}

EXPORT bool LoadXML(char* XMLPath, char* BMGName, char* TBLName, bool LittleEndian) {
    auto writer = BmgWriter(XMLPath, BMGName, TBLName);
    return writer.writeBmg(LittleEndian);
}

extern "C" bool BMGToXML(char* BMGPath, char* TBLPath) {
    BMGINFO info = BMGINFO(LoadBMG(BMGPath), LoadBCSV(TBLPath));
    return BMGINFO::Write(info, "Message.xml");
}

extern "C" bool XMLToBMG(char* XMLPath, bool LittleEndian) {
    auto writer = BmgWriter(XMLPath, "Message.bmg", "MessageId.tbl");
    return writer.writeBmg(LittleEndian);
}