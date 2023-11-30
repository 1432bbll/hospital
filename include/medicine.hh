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
    bool remain;

public:
    medicine();
    void fillMap();
    void saveMap();
    void addMedicine();
    void printDetails();
    void printDetailsFromHistory();
    void getDetails(int rec = 0);
    void getDetailsFromHistory();
    void removeMedicine();
    void sellMedicine();
};
#endif