#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<Windows.h>
#include<iomanip>
using namespace std;

void Menu();
void Menu_admin();
void Menu_user();
void Display_cars();

//using template input validation
template<class T>
void Validation(T& a) {
    while (cin.fail()) {
    cin.clear();
    cout << "Enter Asked Variable : ";
    cin >> a;
    }
}

//class for car information
class Cars {
    private:
    string car_name;
    string model;
    string colour;
    int manufacturing_year;
    double price_per_hour;
    double price_per_day;
public:
    Cars() {
        price_per_day = 0.0;
        price_per_hour = 0.0;
    }
    string car() {
        return car_name;
    }
    string car_model() {
        return model;
    }
    string car_colour() {
        return colour;
    }
    int year() {
        return manufacturing_year;
    }
    double car_pph() {
        return price_per_hour;
    }
    double car_ppd() {
        return price_per_day;
    }
    void SetData(string cname, string mod, string col, int y, double pph, double ppd){
        manufacturing_year = y;
        car_name = cname;
        model = mod;
        colour = col;
        price_per_hour = pph;
        price_per_day = ppd;
    }
};

//class for person information
//wishing to rent a car
class Person : public Cars {
private:
    string person_name;
    string address;
    string CNIC;
    string phone_number;
public:
    string name() {
        return person_name;
    }
    string add() {
        return address;
    }
    string cnic() {
        return CNIC;
    }
    string phone() {
        return phone_number;
    }
    void SetData(string name, string add, string cnic, string phone) {
        person_name = name;
        address = add;
        CNIC = cnic;
        phone_number = phone;
    }
};
void Person_Info(Person& p);

//Information of booked cars
//only for admins
class BookedCars : public Cars {
private:
    int booked;
public:
    BookedCars() {
        booked = 0;
    }
    void Add() {
        booked += 1;
    }
    void SetBooked(Cars& C, Person& P) {
        ofstream Write;
        Write.open("Cars Info.txt", ios::app);
        if (Write.is_open()) {
            Write << "BOOKED CAR : " << endl;
            Write << "================" << endl << endl;
            Write << "\t\tCAR INFO : " << endl;
            Write << "\t\t========== " << endl;
            Write << "\t\t\t Car Name : " << C.car() << "\n\t\t\t Car Model : " << C.car_model()
            << "\n\t\t\t Car Manufacturing : " << C.year() << "\n\t\t\t Car Colour : " << C.car_colour() << "\n\n";
            Write << "\t\tCUSTOMER INFO : \n";
            Write << "\t\t===============\n";
            Write << "\t\t\t Name : " << P.name() << "\n\t\t\t CNIC : " << P.cnic()
            << "\n\t\t\t Phone Number : " << P.phone() << "\n\t\t\t Address : " << P.add() << endl << endl;
        }
    }
    void GetBooked() {
        ifstream Read;
        Read.open("Cars Info.txt", ios::in);
        char data;
        const char* fileName = "Booked cars.txt";
        if (Read.is_open()) {
            while (!Read.eof()) {
                Read >> noskipws >> data;
                cout << data;
            }
            Read.close();
        }
        else {
            cout << "File Not Found ! \n";
        }
    }
};

//calculation of total rent
//depending on rent duration
class TotalRent : public Cars {
private:
    double total;
    int days;
    double hours;
public:
    TotalRent() {
        total = hours = 0;
        days = 0;
    }
    int rent_days() {
        return days;
    }
    double rent_hours() {
        return hours;
    }
    void SetData_days(int d) {
        days = d;
    }
    void SetData_hours(double h) {
        hours = h;
    }
    double Cal_days(Cars& obj) {
        total = obj.car_ppd() * days;
        return total;
    }
    double Cal_hours(Cars& obj) {
        total = obj.car_pph() * hours;
        return total;
    }
    double  GetTotal() {
        return total;
    }
};
void Show_Rent(Cars& C, Person& P, TotalRent& R, int check);

//main function begins
int main() {
    Cars Info;
    Person data;
    BookedCars booked;
    TotalRent Rent;

    int choice, use;
    do {
        Menu();
        cout << "\t Enter 1 for admin \n\t Enter 2 for user  \n\t Enter 3 to Exit.\n";
        do {
            cin >> use;
            Validation(use);
            if (use < 1 || use>3) {
                cout << "Enter 1 to 3 : ";
            }
        } while (use < 1 ||  use > 3);

    system("cls");
    string username, password;
    int a = 0;
    int bookment;
    int no_days;
    double no_hours;
    int checking;

    //switch case
    switch (use) {
    case 1:
        Menu_admin();
        do {
            cout << "Enter your User name ( Minimum 4 Letters... ) : ";
            cin >> username;
            if (!(username.size() > 3)) {
                cout << "Error ! : " << endl;
            }
        } while (!(username.size() > 3));
        do {
            cout << "Enter Password ( Minimum 4 Letters... ) : ";
            cin >> password;
            if (!(password.size() > 3)) {
                cout << "Error ! : " << endl;
            }
        } while (!(password.size() > 3));
        system("cls");
        Menu_admin();
        if (username == "admin") {
            a++;
        }
        if (password == "pass") {
            a++;
        }
        if (a == 2) {
            cout << "Loading the data of Customers who Rented the cars from us... ";
            Sleep(4500);
            system("cls");
            Menu_admin();
            cout << endl;
            booked.GetBooked();
            cout << "Press Any Key to Logout or Go to MAIN menu : ";
        }
        else {
            cout << "Username or Password is Incorrect !!\n\n";
            cout << "Press Any Key to go to MAIN menu : ";
        }
        system("pause");
        break;

    case 2:
        Menu_user();
        Display_cars();
        cout << "Enter one of the given Number : ";
        do {
            cin >> choice;
            Validation(choice);
            if (choice < 1 || choice>6) {
                cout << "Enter Number from 1 to 6 : ";
            }
        } while (choice < 1 || choice>6);
        system("cls");
        switch (choice) {
        case 1:
            Info.SetData("Tesla", "Model-S", "GREY", 2021, 1200, 10000);
            Menu_user();
            cout << "\t Enter 1 to BOOK\n\t Enter 2 to exit. \n ";
            do {
                cin >> bookment;
                Validation(bookment);
                if (bookment < 1 || bookment>2) {
                    cout << "Enter 1 or 2 : ";
                }
            } while (bookment < 1 || bookment>2);
            if (bookment == 1) {
                booked.Add();
                system("cls");
                Menu_user();
                cout << "Enter Your Information : \n";
                cout << "=========================\n";
                Person_Info(data);
                booked.SetBooked(Info, data);
                system("cls");
                Menu_user();
                cout << "Enter 1 if you want to Rent A Car for some Days \n";
                cout << "Enter 2 if you want to Rent A Car for some Hours \n\n";
                do {
                    cin >> checking;
                    Validation(checking);
                    if (checking != 1 && checking != 2) {
                        cout << "Error ! : " << endl;
                    }
                } while (checking != 1 && checking != 2);
                system("cls");
                Menu_user();
                if (checking == 1) {
                    cout << "Enter Number of Days you want to Rent A Car : ";
                    cin >> no_days;
                    Validation(no_days);
                    while (no_days < 1) {
                        cout << "Enter Positive Number of Days : ";
                        cin >> no_days;
                        Validation(no_days);
                    }
                    Rent.SetData_days(no_days);
                    Rent.Cal_days(Info);
                }
                else if (checking == 2) {
                    cout << "Enter Number of Hours you want to Rent A Car : ";
                    cin >> no_hours;
                    Validation(no_hours);
                    while (no_hours < 1) {
                        cout << "Enter Positive Number of Hours : ";
                        cin >> no_hours;
                        Validation(no_hours);
                    }
                    Rent.SetData_hours(no_hours);
                    Rent.Cal_hours(Info);
                }
                system("cls");
                Menu_user();

                cout << "\t\t\t\tCalculating and Saving Rent...";
                Sleep(3000);
                system("cls");
                cout << "\t\t\t\t\t\tDisplaying Total Rent...";
                Sleep(1000);
                system("cls");
                Menu_user();
                cout << endl;
                Show_Rent(Info, data, Rent, checking);
            }
            else { break;}
            break;

        case 2:
            Info.SetData("MG", "Hector Plus", "RED", 2023, 800, 9000);
            Menu_user();
            cout << "\t Enter 1 to BOOK\n\t Enter 2 to exit. \n ";
            do {
                cin >> bookment;
                Validation(bookment);
                if (bookment < 1 || bookment>2) {
                    cout << "Enter 1 or 2 : ";
                }
            } while (bookment < 1 || bookment>2);
            if (bookment == 1) {
                booked.Add();
                system("cls");
                Menu_user();
                cout << "Enter Your Information : \n";
                cout << "=========================\n";
                Person_Info(data);
                booked.SetBooked(Info, data);
                system("cls");
                Menu_user();
                cout << "Enter 1 if you want to Rent A Car for some Days \n";
                cout << "Enter 2 if you want to Rent A Car for some Hours \n\n";
                do {
                    cin >> checking;
                    Validation(checking);
                    if (checking != 1 && checking != 2) {
                        cout << "Error ! : " << endl;
                    }
                } while (checking != 1 && checking != 2);
                system("cls");
                Menu_user();
                if (checking == 1) {
                    cout << "Enter Number of Days you want to Rent A Car : ";
                    cin >> no_days;
                    Validation(no_days);
                    while (no_days < 1) {
                        cout << "Enter Positive Number of Days : ";
                        cin >> no_days;
                        Validation(no_days);
                    }
                    Rent.SetData_days(no_days);
                    Rent.Cal_days(Info);
                }
                else if (checking == 2) {
                    cout << "Enter Number of Hours you want to Rent A Car : ";
                    cin >> no_hours;
                    Validation(no_hours);
                    while (no_hours < 1) {
                        cout << "Enter Positive Number of Hours : ";
                        cin >> no_hours;
                        Validation(no_hours);
                    }
                    Rent.SetData_hours(no_hours);
                    Rent.Cal_hours(Info);
                }
                system("cls");
                Menu_user();

                cout << "\t\t\t\tCalculating and Saving Rent...";
                Sleep(3000);
                system("cls");
                cout << "\t\t\t\t\t\tDisplaying Total Rent...";
                Sleep(1000);
                system("cls");
                Menu_user();
                cout << endl;
                Show_Rent(Info, data, Rent, checking);
            }
            break;

        case 3:
            Info.SetData("Renault", "Triber", "NAVY BLUE", 2022, 700, 8000);
            Menu_user();
            cout << "\t Enter 1 to BOOK\n\t Enter 2 to exit. \n ";
            do {
                cin >> bookment;
                Validation(bookment);
                if (bookment < 1 || bookment>2) {
                    cout << "Enter 1 or 2 : ";
                }
            } while (bookment < 1 || bookment>2);
            if (bookment == 1) {
                booked.Add();
                system("cls");
                Menu_user();
                cout << "Enter Your Information : \n";
                cout << "=========================\n";
                Person_Info(data);
                booked.SetBooked(Info, data);
                system("cls");
                Menu_user();
                cout << "Enter 1 if you want to Rent A Car for some Days \n";
                cout << "Enter 2 if you want to Rent A Car for some Hours \n\n";
                do {
                    cin >> checking;
                    Validation(checking);
                    if (checking != 1 && checking != 2) {
                        cout << "Error ! : " << endl;
                    }
                } while (checking != 1 && checking != 2);
                system("cls");
                Menu_user();
                if (checking == 1) {
                    cout << "Enter Number of Days you want to Rent A Car : ";
                    cin >> no_days;
                    Validation(no_days);
                    while (no_days < 1) {
                        cout << "Enter Positive Number of Days : ";
                        cin >> no_days;
                        Validation(no_days);
                    }
                    Rent.SetData_days(no_days);
                    Rent.Cal_days(Info);
                }
                else if (checking == 2) {
                    cout << "Enter Number of Hours you want to Rent A Car : ";
                    cin >> no_hours;
                    Validation(no_hours);
                    while (no_hours < 1) {
                        cout << "Enter Positive Number of Hours : ";
                        cin >> no_hours;
                        Validation(no_hours);
                    }
                    Rent.SetData_hours(no_hours);
                    Rent.Cal_hours(Info);
                }
                system("cls");
                Menu_user();

                cout << "\t\t\t\tCalculating and Saving Rent...";
                Sleep(3000);
                system("cls");
                cout << "\t\t\t\t\t\tDisplaying Total Rent...";
                Sleep(1000);
                system("cls");
                Menu_user();
                cout << endl;
                Show_Rent(Info, data, Rent, checking);
            }
            break;

        case 4:
            Info.SetData("Honda City", "Hybrid", "BLUE", 2024, 1200, 11000);
            Menu_user();
            cout << "\t Enter 1 to BOOK\n\t Enter 2 to exit. \n ";
            do {
                cin >> bookment;
                Validation(bookment);
                if (bookment < 1 || bookment>2) {
                    cout << "Enter 1 or 2 : ";
                }
            } while (bookment < 1 || bookment>2);
            if (bookment == 1) {
                booked.Add();
                system("cls");
                Menu_user();
                cout << "Enter Your Information : \n";
                cout << "=========================\n";
                Person_Info(data);
                booked.SetBooked(Info, data);
                system("cls");
                Menu_user();
                cout << "Enter 1 if you want to Rent A Car for some Days \n";
                cout << "Enter 2 if you want to Rent A Car for some Hours \n\n";
                do {
                    cin >> checking;
                    Validation(checking);
                    if (checking != 1 && checking != 2) {
                        cout << "Error ! : " << endl;
                    }
                } while (checking != 1 && checking != 2);
                system("cls");
                Menu_user();
                if (checking == 1) {
                    cout << "Enter Number of Days you want to Rent A Car : ";
                    cin >> no_days;
                    Validation(no_days);
                    while (no_days < 1) {
                        cout << "Enter Positive Number of Days : ";
                        cin >> no_days;
                        Validation(no_days);
                    }
                    Rent.SetData_days(no_days);
                    Rent.Cal_days(Info);
                }
                else if (checking == 2) {
                    cout << "Enter Number of Hours you want to Rent A Car : ";
                    cin >> no_hours;
                    Validation(no_hours);
                    while (no_hours < 1) {
                        cout << "Enter Positive Number of Hours : ";
                        cin >> no_hours;
                        Validation(no_hours);
                    }
                    Rent.SetData_hours(no_hours);
                    Rent.Cal_hours(Info);
                }
                system("cls");
                Menu_user();

                cout << "\t\t\t\tCalculating and Saving Rent...";
                Sleep(3000);
                system("cls");
                cout << "\t\t\t\t\t\tDisplaying Total Rent...";
                Sleep(1000);
                system("cls");
                Menu_user();
                cout << endl;
                Show_Rent(Info, data, Rent, checking);
            }
            break;

        case 5:
            Info.SetData("Mahindra", "XUV300", "ORANGE", 2023, 600, 5000);
            Menu_user();
            cout << "\t Enter 1 to BOOK\n\t Enter 2 to exit. \n ";
            do {
                cin >> bookment;
                Validation(bookment);
                if (bookment < 1 || bookment>2) {
                    cout << "Enter 1 or 2 : ";
                }
            } while (bookment < 1 || bookment>2);
            if (bookment == 1) {
                booked.Add();
                system("cls");
                Menu_user();
                cout << "Enter Your Information : \n";
                cout << "=========================\n";
                Person_Info(data);
                booked.SetBooked(Info, data);
                system("cls");
                Menu_user();
                cout << "Enter 1 if you want to Rent A Car for some Days \n";
                cout << "Enter 2 if you want to Rent A Car for some Hours \n\n";
                do {
                    cin >> checking;
                    Validation(checking);
                    if (checking != 1 && checking != 2) {
                        cout << "Error ! : " << endl;
                    }
                } while (checking != 1 && checking != 2);
                system("cls");
                Menu_user();
                if (checking == 1) {
                    cout << "Enter Number of Days you want to Rent A Car : ";
                    cin >> no_days;
                    Validation(no_days);
                    while (no_days < 1) {
                        cout << "Enter Positive Number of Days : ";
                        cin >> no_days;
                        Validation(no_days);
                    }
                    Rent.SetData_days(no_days);
                    Rent.Cal_days(Info);
                }
                else if (checking == 2) {
                    cout << "Enter Number of Hours you want to Rent A Car : ";
                    cin >> no_hours;
                    Validation(no_hours);
                    while (no_hours < 1) {
                        cout << "Enter Positive Number of Hours : ";
                        cin >> no_hours;
                        Validation(no_hours);
                    }
                    Rent.SetData_hours(no_hours);
                    Rent.Cal_hours(Info);
                }
                system("cls");
                Menu_user();

                cout << "\t\t\t\tCalculating and Saving Rent...";
                Sleep(3000);
                system("cls");
                cout << "\t\t\t\t\t\tDisplaying Total Rent...";
                Sleep(1000);
                system("cls");
                Menu_user();
                cout << endl;
                Show_Rent(Info, data, Rent, checking);
            }
            break;
        case 6:
            break;
        }
    }
    system("cls");
    } while (use != 3);
    system("pause");
}

//Menus to show Car rental system dashboard
//at any time
void Menu() {
    cout << "\t\t\t=================================================\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t|        -----------------------------          |\n";
    cout << "\t\t\t|        |     CAR RENTAL SYSTEM     |          |\n";
    cout << "\t\t\t|        -----------------------------          |\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t|                    MADE  BY :                 |\n";
    cout << "\t\t\t|                   -----------                 |\n";
    cout << "\t\t\t|           Harsh Kumar       23103315          |\n";
    cout << "\t\t\t|           Avinash           23103316          |\n";
    cout << "\t\t\t|           Vivek Kumar       23103332          |\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t=================================================\n\n\n";
}
void Menu_admin() {
    cout << "\t\t\t=================================================\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t|        -----------------------------          |\n";
    cout << "\t\t\t|        |     CAR RENTAL SYSTEM     |          |\n";
    cout << "\t\t\t|        -----------------------------          |\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t|                    MADE  BY :                 |\n";
    cout << "\t\t\t|                   -----------                 |\n";
    cout << "\t\t\t|           Harsh Kumar       23103315          |\n";
    cout << "\t\t\t|           Avinash           23103316          |\n";
    cout << "\t\t\t|           Vivek Kumar       23103332          |\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t=================================================\n\n\n";
    cout << "\t\t\t                   <<<ADMIN>>>                  \n\n\n";
}
void Menu_user() {
    cout << "\t\t\t=================================================\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t|        -----------------------------          |\n";
    cout << "\t\t\t|        |     CAR RENTAL SYSTEM     |          |\n";
    cout << "\t\t\t|        -----------------------------          |\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t|                    MADE  BY :                 |\n";
    cout << "\t\t\t|                   -----------                 |\n";
    cout << "\t\t\t|           Harsh Kumar       23103315          |\n";
    cout << "\t\t\t|           Avinash           23103316          |\n";
    cout << "\t\t\t|           Vivek Kumar       23103332          |\n";
    cout << "\t\t\t|                                               |\n";
    cout << "\t\t\t=================================================\n\n\n";
    cout << "\t\t\t                   <<<USERS>>>                  \n\n\n";
}

void Person_Info(Person & P) {
    bool check = false;
    string fname;
    string lname;
    string name;
    string Number, cnic, address;
    int a = 0;
    do { // first name
        a = 0;
        cout << "Enter Your First Name ( Minimum 3 Letters... ) : ";
        cin.ignore();
        getline(cin, fname);
        for (int i = 0; i < fname.size(); i++) {
            if (!(isalpha(fname[i]))) {
                a++;
            }
            else {
                check = false;
            }
        }
        if (a != 0 || !(fname.size()>=3)) {
            cout << "Error ! : " << endl;
            check = true;
        }
    } while (!(fname.size() >= 3) || check == true);

    do { //last name
        a = 0;
        cout << "Enter Your last Name ( Minimum 3 Letters... ) : ";
        getline(cin, lname);
        for (int i = 0; i < lname.size(); i++) {
            if (!(isalpha(lname[i]))) {
                a++;
            }
            else {
                check = false;
            }
        }
        if (a != 0 || !(lname.size()>=3)) {
            cout << "Error ! : " << endl;
            check = true;
        }
    } while (!(lname.size() >= 3) || check == true);
    name = fname + " " + lname;

    do { //CNIC
        a = 0;
        cout << "Enter your CNIC ( 13 Digits without Dashes... ) : ";
        getline(cin, cnic);
        for (int i = 0; i < cnic.size(); i++) {
            if (!(isdigit(cnic[i]))) {
                a++;
            }
            else {
                check = false;
            }
        }
        if (a != 0 || cnic.size()!=13) {
            cout << "Error ! : " << endl;
            check = true;
        }
    } while (!(cnic.size() == 13) || check == true);

    do { //mobile number
        a = 0;
        cout << "Enter your Mobile Number ( 10 digits without Dashes... ) : ";
        cin >> Number;
        for (int i = 0; i < Number.size(); i++) {
            if (!(isdigit(Number[i]))) {
                a++;
            }
            else {
                check = false;
            }
        }
        if (a != 0 || Number.size() != 10) {
            cout << "Error ! : " << endl;
            check = true;
        }
    } while (!(Number.size() == 10) || check == true);

    do { //address
        cout << "Enter you Present Address ( Full & Minimum 6 Letters or Digits... ) : ";
        cin.ignore();
        getline(cin, address);
    } while (!(address.size() > 5));

P.SetData(name, address, cnic, Number);
// Setting values to person class setdata function
}

//showing the available cars
void Display_cars() {
    cout << "\t\tPlease Select a Car: " << endl;
    cout << "\t\tEnter 1 for Tesla 2021." << endl;
    cout << "\t\tEnter 2 for MG 2023." << endl;
    cout << "\t\tEnter 3 for Renault 2022." << endl;
    cout << "\t\tEnter 4 for Honda City 2024." << endl;
    cout << "\t\tEnter 5 for Mahindra 2023." << endl;
    cout << "\t\tEnter 6 to Exit." << endl;
    cout << endl;
}
void Show_Rent(Cars & C, Person & P, TotalRent & R, int check) {
    cout << "\n\t\t                       Car Rental - Customer Invoice                  " << endl;
    cout << "\t\t ///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t | Invoice No. :" << "------------------|" << setw(18) << "#Cnb81353" << " |" << endl;
    cout << "\t\t | Customer Name:" << "-----------------|" << setw(18) << P.name() << " |" << endl;
    cout << "\t\t | Car Name  :" << "--------------------|" << setw(18) << C.car() << " |" << endl;
    cout << "\t\t | Car Model :" << "--------------------|" << setw(18) << C.car_model() << " |" << endl;
    cout << "\t\t | Car Manufactured :" << "-------------|" << setw(18) << C.year() << " |" << endl;
    if (check == 1) {
        cout << "\t\t | Number of days :" << "---------------|" << setw(18) << R.rent_days() << " |" << endl;
    }
    else if (check == 2) {
        cout << "\t\t | Number of hours :" << "--------------|" << setw(18) << R.rent_hours() << " |" << endl;
    }

    cout << "\t\t | Your Rental Amount is :" << "--------|" << setw(18) << R.GetTotal() << " |" << endl;
    cout << "\t\t | Caution Money :" << "----------------|" << setw(18) << "500" << " |" << endl;
    cout << "\t\t | Advance :" << "----------------------|" << setw(18) << "200" << " |" << endl;
    cout << "\t\t ________________________________________________________" << endl;
    cout << "\n";

    cout << "\t\t | Total Rental Amount is :" << "-------|" << setw(18) << (R.GetTotal()+700) << " |" << endl;
    cout << "\t\t ________________________________________________________" << endl;
    cout << "\t\t # This is a computer generated invoce and it does not" << endl;
    cout << "\t\t require an authorised signature #" << endl;
    cout << " " << endl;

    cout << "\t\t ///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t You are advised to pay up the amount before due date." << endl;
    cout << "\t\t Otherwise penalty fee will be applied" << endl;
    cout << "\t\t ///////////////////////////////////////////////////////////" << endl;
    cout << endl << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tThanks for Visiting us... \n";
    system("pause");
    system("cls");

    cout << "\t\t\t\t\t\t Loading Main Menu... ";
    Sleep(1500);
    system("cls");
}

