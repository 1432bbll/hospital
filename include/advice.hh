#ifndef ADVICE
#define ADVICE

using namespace std;
#include <string>

class advice
{
protected:
    int id;
    string text;
    bool effect;
    int doctorid;
    int patientid;

public:
    advice();
    void fillMap();
    void saveMap();
    void addAdvice();
    void printDetails();
    void printDetailsFromHistory();
    void getDetails();
    void getDetailsFromHistory();
    void removeAdvice();
};
#endif