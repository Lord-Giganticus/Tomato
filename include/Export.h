#include "Tomato.h"
#include <vector>
#define EXPORT __declspec(dllexport)
#define list(type) vector<type>

using namespace std;
using namespace MESGbmg1;

unsigned long GetFeildCount(BCSV* ptr);

class BMGINFO {
private:
    BmgFileHolder* BMG;
    BCSV* TBL;
public:
    unsigned long TBLEntryNum;
    unsigned long TBLFieldNum;
    unsigned long TBLDataAdr;
    unsigned long TBLEntrySize;
    Field* TBLFields;
    BMGINFO(BmgFileHolder* bmg, BCSV* tbl);
    bool Write(char* XMLName);
};

BmgFileHolder* LoadBMG(char* path);

BCSV* LoadBCSV(char* path);

list(Field) LoadFields(BCSV* ptr);

extern "C" {
    bool BMGToXML(char* bmgpath, char* tblpath);
    bool XMLToBMG(char* xmlpath, bool littleendian);
}