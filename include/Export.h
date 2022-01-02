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
    static bool Write(BMGINFO& info, char* XMLName);
};

BmgFileHolder* LoadBMG(char* path);

BCSV* LoadBCSV(char* path);

list(Field) LoadFields(BCSV* ptr);

extern "C" {
    EXPORT BMGINFO __stdcall LoadBMGInfo(char* BMGPath, char* TBLPath);
    EXPORT bool __stdcall ToXML(BMGINFO info, char* XMLName);
    EXPORT bool __stdcall LoadXML(char* XMLPath, char* BMGName, char* TBLName, bool LittleEndian);
};