using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/medicine.hh"
#include "./../include/hospital.hh"

medicine::medicine()
{
    id = -1;
    name = "";
    number = -1;
    re=0;
}
void medicine::fillMap()
{
    fstream f;
    f.open("./data/medicine.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        medicine n;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s2, s3, s4;
        //reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, s2, ',');
        getline(s, s3, ',');
        getline(s,s4,',');
        n.id = strToNum(s1);
        n.name = s2;
        n.number = strToNum(s3);
        n.re=strToNum(s4);
        hospital::medicineList[n.id] = n;
    }
    f.close();
    return;
}
void medicine::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "medicineId,Name,Number,Remove\n";
    for (auto i : hospital::medicineList)
        f << i.second.id << "," << i.second.name << "," << i.second.number<<","<<i.second.re<< endl;
    f.close();
    remove("./data/medicine.csv");
    rename("./data/temp.csv", "./data/medicine.csv");
    return;
}
void medicine::addMedicine()
{
     if (hospital::medicineList.size() == hospital::medicineLimit)
    {
        cout << "\n\nMedicine limit reached, can't add more!\n\n";
        return;
    }
    cout << "\nEnter Name: \n";
    cin>>name;
    cout << "\nEnter Number: \n";
    cin>>number;
    getchar();
    // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;
    if (hospital::medicineList.rbegin() != hospital::medicineList.rend())
        id = ((hospital::medicineList.rbegin())->first) + 1;
    else
        id = 1;
    re=0;
    hospital::medicineList[id] = *this;

    fstream f;
    f.open("./data/adviceHistory.csv", ios::app);
    f << id << "," << name << "," << number << endl;
    f.close();

    cout << "\nAdd successfully!\n";
    cout << "ID is: " << id << "\n";

    return;
}
void medicine::printDetails()
{
    if (id == -1&&re==0)
         return;
    cout << "\nDetails:\n";
    cout << "ID              : " << id << "\n";
    cout << "Name            : " << name << "\n";
    cout << "Number          : " << number << "\n";
    return;
}
void medicine::printDetailsFromHistory()
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
void medicine::getDetails()
{
    int opt = 0;
    cout << "\nOPTIONS:\n[1]: Filter by ID\n[2]: Filter by Name\n";
    cout << "option 1or2?";
    cin >> opt;
    while (opt != 1 && opt != 2 ){
        cout << "option 1or2?";
        cin >> opt;
    }
    //1: Filter by ID;
    if (opt == 1)
    {
        int reqId;
        cout << "\nEnter ID:\n";
        cin >> reqId;
        int recorednumber=0;
        for (auto i : hospital::medicineList){
            if(i.second.id==reqId&&i.second.re==0){
                i.second.printDetails();
                recorednumber++;
            }
        }
        cout<<"\nFind "<<recorednumber<<" Records!\n";
    }
    //2: Filter by name;
    else if (opt == 2)
    {
        string reqName;
        cout << "\nEnter Name:\n";
        cin >> reqName;
        int recorednumber=0;
        for (auto i : hospital::medicineList){
            if(i.second.name==reqName&&i.second.re==0){
                i.second.printDetails();
                recorednumber++;
            }
        }
        cout<<"\nFind "<<recorednumber<<" Records!\n";
    }
    return;
}
void medicine ::getDetailsFromHistory()
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
void medicine::removeMedicine()
{
    cout << "\nEnter the ID of advice you want to remove.\n";
    int tmp;
    cin>>tmp;
    getchar();
    if (tmp <=0||tmp>((hospital::medicineList.rbegin())->first)){
        cout<<"\nInvaild ID\n";
        return;
    }
    for (auto i : hospital::medicineList){
        if(i.second.id==tmp){
            i.second.re=1;
        }
    }
    cout<<"\nRemove Successfully!\n";
    return;
}
void medicine::sellMedicine(){
    int reqId;
    cout << "\nEnter ID:\n";
    cin >> reqId;
    int recorednumber=0;
    for (auto i : hospital::medicineList){
        if(i.second.id==reqId&&i.second.re==0){
            i.second.printDetails();
            if(i.second.MMinus()==1){
                cout<<"\nSuccessfully!\n";
            }
            else{
                cout<<"\nThere isn't enough medicine!\n";
            }
        }
    }
    if(recorednumber==0){
        cout<<"\nInvalid ID!\n";
    }
    return;
}
bool medicine::MMinus(){
    int reqnum;
    cout<<"\nEnter your request:";
    cin>>reqnum;
    if(number<=reqnum){
        number-=reqnum;
        return 1;
    }
    else{
        return 0;
    }

}