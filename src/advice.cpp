using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/advice.hh"
#include "./../include/hospital.hh"

advice::advice()
{
    id = -1;
    text = "";
    doctorid=-1;
    patientid = -1;
    effect=0;
}
void advice::fillMap()
{
    fstream f;
    f.open("./data/advice.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        advice n;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s2, s3, s4;
        //reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, s2, ',');
        getline(s, s3, ',');
        getline(s, n.text, ',');
        getline(s, s4, ',');
        n.id = strToNum(s1);
        n.doctorid=strToNum(s2);
        n.patientid=strToNum(s3);
        n.effect=strToNum(s4);
        hospital::adviceList[n.id] = n;
    }
    f.close();
    return;
}
void advice::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    f << "AdviceId,DoctorID,PatientID,Text,Effect\n";
    for (auto i : hospital::adviceList)
        f << i.second.id << "," << i.second.doctorid << "," << i.second.patientid << "," << i.second.text
          << "," << i.second.effect <<endl;
    f.close();
    remove("./data/advice.csv");
    rename("./data/temp.csv", "./data/advice.csv");
    return;
}
void advice::addAdvice()
{
    if (hospital::adviceList.size() == hospital::adviceLimit)
    {
        cout << "\n\nAdvice limit reached, can't add more!\n\n";
        return;
    }
    cout << "\nEnter DoctorID: ";
    cin>>doctorid;
    cout << "\nEnter PatientID: ";
    cin>>patientid;
    cout << "\nEnter the content: ";
    cin>>text;
    getchar();
    // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;
    if (hospital::adviceList.rbegin() != hospital::adviceList.rend())
        id = ((hospital::adviceList.rbegin())->first) + 1;
    else
        id = 1;
    effect=1;
    hospital::adviceList[id] = *this;

    fstream f;
    f.open("./data/adviceHistory.csv", ios::app);
    f << id << "," << doctorid << "," << patientid << "," << text << endl;
    f.close();

    cout << "\nAdd successfully!\n";
    cout << "ID is: " << id << "\n";

    return;
}
void advice::printDetails()
{
    if (id == -1&&effect==1)
        return;
    cout << "\nDetails:\n";
    cout << "ID              : " << id << "\n";
    cout << "DoctorID        : " << doctorid<< "\n";
    cout << "PatientID       : " << patientid << "\n";
    cout << "Contents        : " << text << "\n";
    return;
}
void advice::printDetailsFromHistory()
{
    // if (id == -1)
    //     return;
    // person::printDetailsFromHistory();
    // stringstream k(extraDetails);
    // string s1, s2;
    // getline(k, s1, ',');
    // getline(k, s2, ',');
    // if (extraDetails == "")
    // {
    //     fstream f;
    //     f.open("./data/nursesHistory.csv", ios::in);
    //     string temp;
    //     //skipping the first row containing column headers;
    //     getline(f >> ws, temp);
    //     //analyzing each entry afterwards;
    //     while (getline(f >> ws, temp))
    //     {
    //         nurse n;
    //         //creating a string stream object to read from string 'temp';
    //         stringstream s(temp);
    //         string s4, s5, s7;
    //         //reading from the string stream object 's';
    //         getline(s, n.firstName, ',');
    //         getline(s, n.lastName, ',');
    //         getline(s, s4, ',');
    //         getline(s, s5, ',');
    //         getline(s, n.mobNumber, ',');

    //         if (n.firstName == firstName && n.lastName == lastName && n.mobNumber == mobNumber)
    //         {

    //             getline(s, s7, ',');
    //             getline(s, n.type, ',');
    //             getline(s, s1, ',');
    //             getline(s, s2, ',');
    //         }
    //     }
    //     f.close();
    // }
    // cout << "Type            : " << type << "\n";
    // cout << "Left Work?      : " << s1 << "\n";
    // if (s1 == "Y")
    //     cout << "Reason          : " << s2 << "\n";
    return;
}
void advice::getDetails()
{
    int opt = 0;
    cout << "\nOPTIONS:\n[1]: Filter by ID\n[2]: Filter by DoctorID\n[3]: Filter by PatientID\n\n";
    cout << "option 1, 2 or 3?";
    cin >> opt;
    while (opt != 1 && opt != 2 && opt != 3){
        cout << "option 1, 2 or 3?";
        cin >> opt;
    }
    //1: Filter by ID;
    if (opt == 1)
    {
        int reqId;
        cout << "\nEnter ID:";
        cin >> reqId;
        int recorednumber=0;
        for (auto i : hospital::adviceList){
            if(i.second.id==reqId&&i.second.effect==1){
                i.second.printDetails();
                recorednumber++;
            }
        }
        cout<<"\nFind "<<recorednumber<<" Records!\n";
    }
    //2: Filter by name;
    else if (opt == 2)
    {
        int reqdoctorId;
        cout << "\nEnter DoctorID:";
        cin >> reqdoctorId;
        int recorednumber=0;
        for (auto i : hospital::adviceList){
            if(i.second.doctorid==reqdoctorId&&i.second.effect==1){
                i.second.printDetails();
                recorednumber++;
            }
        }
        cout<<"\nFind "<<recorednumber<<" Records!\n";
    }
    //3: Filter by type;
    else if (opt == 3)
    {
        int reqpatientId;
        cout << "\nEnter PatientID:";
        cin >> reqpatientId;
        int recorednumber=0;
        for (auto i : hospital::adviceList){
            if(i.second.patientid==reqpatientId&&i.second.effect==1){
                i.second.printDetails();
                recorednumber++;
            }
        }
        cout<<"\nFind "<<recorednumber<<" Records!\n";
    }
    return;
}
void advice::getDetailsFromHistory()
{
    // int opt = 0;
    // cout << "\nOPTIONS:\n[1]: Filter by Name\n[2]: Filter by Type\n\n";
    // cin >> opt;
    // while (opt != 1 && opt != 2)
    //     cout << "option 1 or 2?\n", cin >> opt;

    // //1: Filter by name;
    // if (opt == 1)
    // {
    //     string reqFName, reqLName;
    //     cout << "First Name:\n";
    //     getline(cin >> ws, reqFName);
    //     cout << "\nLast Name:\n";
    //     getline(cin, reqLName);
    //     vector<nurse> matchingRecords;
    //     vector<string> extraDetails;
    //     fstream f;
    //     f.open("./data/nursesHistory.csv", ios::in);
    //     string temp;
    //     //skipping the first row containing column headers;
    //     getline(f >> ws, temp);
    //     //analyzing each entry afterwards;
    //     while (getline(f >> ws, temp))
    //     {
    //         nurse n;
    //         //creating a string stream object to read from string 'temp';
    //         stringstream s(temp);
    //         string s4, s5, s7, s9;
    //         //reading from the string stream object 's';
    //         getline(s, n.firstName, ',');
    //         getline(s, n.lastName, ',');

    //         if (n.firstName == reqFName && n.lastName == reqLName)
    //         {
    //             getline(s, s4, ',');
    //             getline(s, s5, ',');
    //             getline(s, n.mobNumber, ',');
    //             getline(s, s7, ',');
    //             getline(s, n.type, ',');
    //             getline(s, s9);
    //             n.id = 0;
    //             n.gender = s4[0];
    //             n.age = strToNum(s5);
    //             n.add.strToAdd(s7);
    //             matchingRecords.push_back(n);
    //             extraDetails.push_back(s9);
    //         }
    //     }
    //     f.close();
    //     cout << "\n";
    //     cout << matchingRecords.size() << " matching record(s) found!\n";
    //     for (int i = 0; i < matchingRecords.size(); i++)
    //         matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
    // }
    // //2: Filter by type;
    // else if (opt == 2)
    // {
    //     string reqType;
    //     cout << "Enter the type of nurse required:\n";
    //     getline(cin >> ws, reqType);
    //     vector<nurse> matchingRecords;
    //     vector<string> extraDetails;
    //     fstream f;
    //     f.open("./data/nursesHistory.csv", ios::in);
    //     string temp;
    //     //skipping the first row containing column headers;
    //     getline(f >> ws, temp);
    //     //analyzing each entry afterwards;
    //     while (getline(f >> ws, temp))
    //     {
    //         nurse n;
    //         //creating a string stream object to read from string 'temp';
    //         stringstream s(temp);
    //         string s4, s5, s7, s9;
    //         //reading from the string stream object 's';
    //         getline(s, n.firstName, ',');
    //         getline(s, n.lastName, ',');
    //         getline(s, s4, ',');
    //         getline(s, s5, ',');
    //         getline(s, n.mobNumber, ',');
    //         getline(s, s7, ',');
    //         getline(s, n.type, ',');
    //         if (n.type == reqType)
    //         {
    //             getline(s, s9);
    //             n.id = 0;
    //             n.gender = s4[0];
    //             n.age = strToNum(s5);
    //             n.add.strToAdd(s7);
    //             matchingRecords.push_back(n);
    //             extraDetails.push_back(s9);
    //         }
    //     }
    //     f.close();
    //     cout << "\n";
    //     cout << matchingRecords.size() << " matching record(s) found!\n";
    //     for (int i = 0; i < matchingRecords.size(); i++)
    //         matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
    // }
    return;
}
void advice::removeAdvice()
{
    cout << "\nEnter the ID of advice you want to remove:";
    int tmp;
    cin>>tmp;
    getchar();
    if (tmp <=0||tmp>((hospital::adviceList.rbegin())->first)){
        cout<<"\nInvaild ID!\n";
        return;
    }
    for (auto i : hospital::adviceList){
        if(i.second.id==tmp){
            i.second.effect=0;
        }
    }
    cout<<"\nRemove Successfully!\n";
    return;
}