#ifndef MEDICINE
#define MEDICINE

using namespace std;
#include <string>

class medicine
{
protected:
    int id;
    string name;
    int number;
    bool re;

public:
    medicine();
    void fillMap();
    void saveMap();
    void addMedicine();
    void printDetails();
    void printDetailsFromHistory();
    void getDetails();
    void getDetailsFromHistory();
    void removeMedicine();
    void sellMedicine();
    bool MMinus();
};
#endif