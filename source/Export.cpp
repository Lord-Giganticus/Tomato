#include "../include/Export.h"
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

BMGINFO::BMGINFO(BmgFileHolder* bmg, BCSV* tbl) {
    BMG = bmg;
    TBL = tbl;
    TBLEntryNum = tbl->mEntryNum;
    TBLFieldNum = tbl->mFieldNum;
    TBLDataAdr = tbl->mDataAdr;
    TBLEntrySize = tbl->mEntrySize;
    TBLFields = tbl->mFields;
}

bool BMGINFO::Write(char* XMLName) {
    const char* name = "Message.xml";
    if (XMLName != nullptr)
        name = XMLName;
    XmlWriter writer = XmlWriter(name, BMG, TBL);
    return writer.writeXml();
}

bool BMGToXML(char* bmgpath, char* tblpath) {
    BMGINFO info = BMGINFO(LoadBMG(bmgpath), LoadBCSV(tblpath));
    return info.Write("Message.xml");
}

bool XMLToBMG(char* xmlpath, bool littleendian) {
    auto writer = BmgWriter(xmlpath, "Message.bmg", "MessageId.tbl");
    return writer.writeBmg(littleendian);
}