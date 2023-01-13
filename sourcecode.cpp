#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <iomanip>
#include <conio.h>

using namespace std;

int amt, flag;
float tamt;
void real_train();
void sign_up();
void login();
void admin();
void pass_details();
void can_ticket_details();
void user_menu();
void chart(int tnum, char bp1[100], char dest1[100], char day2[20], int nd, int nm, int ny);
void res();
void reservation();
void can();
void cancellation();
void forgot_pass();
int main();

//Class for registering the user
class Registration
{
private:
    int i = 0, j = 0;
    char ch, cha;
    string name, surname, mail, m, pass, uname, u;
    //char uname[31], u[31] , pass[11] ;

public:
    Registration()
    {
        system("CLS");
        cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "*****SIGN UP*****";
        cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

        cout << "Name: ";
        cin >> name;

        cout << "Surname: ";
        cin >> surname;

    target:
        cout << "Do you want to register with your email address?\n";
        cout << "y==YES | n==NO\n";
        cin >> ch;

        if (ch == 'y' || ch == 'Y')
        {
            cin.ignore();
            cout << "Email: ";
            getline(cin, mail);

            fstream check("u&p.txt", ios::in | ios::app);

            while (!check.eof())
            {
                check.seekg(i);
                getline(check, m, '\n');

                if (m == mail)
                {
                    cout << "Account linked with this email address already exists..\n";
                    cout << "Enter new email address: ";
                    goto target;
                }
                i++;
            }
            check.close();
        }
        else
        {
            main();
        }

        cin.ignore();

    target2:
        cout << "\n(Username must be of maximum 30 characters only and there should be no space in between!)\n";
        cout << "Username: ";
        getline(cin, uname);
        cin.ignore();

        fstream check2("u&p.txt", ios::in | ios::app);

        while (!check2.eof())
        {
            check2.seekg(j);
            getline(check2, u, '\n');

            if (u == uname)
            {
                cout << "Entered Username already exists..\n";
                cout << "Please enter unique Username: ";
                cin.get();
                goto target2;
            }
            j++;
        }
        check2.close();

        cout << "\n(Password must be of maximum 10 characters only and there should be no space in between!)\n";
        cout << "Password: ";
        //cin.getline(pass, 11);

        while (true)
        {
            cha = getch();
            if (cha == 13)
                break;
            else if (cha == 8)
            {
                pass.pop_back();
                cout << "\b\b";
            }
            else
                pass.push_back(cha);
            cout << "*";
        }
        char b;

        cout << "\nPress 'y' to see your password\n";

        cin >> b;
        if (b == 'Y' || b == 'y')
        {
            cout << pass << endl;
        }
        cin.get();

        ofstream g("u&p.txt", ios::out | ios::app);
        if (!g.is_open())
        {
            cout << "\nCould not open file..\n";
        }
        else
        {
            g << mail << '\n'
              << uname << '\n'
              << pass << "*\n";
            g.close();
            cout << "Sign up was successfull..";
            cin.get();
            cin.get();
            main();
        }
    }
};

//Class for adding train details, used by admin
class Detail
{
public:
    int tno;
    char tname[100];
    char bp[100];
    char dest[100];
    char station[5][100];
    int c1, c1fare;
    int c2, c2fare;
    int c3, c3fare;

    void getDetail()
    {
        cout << "\n--Add New details--\n";
        cout << "Train no: ";
        cin >> tno;
        cout << "\nTrain Name: (Avoid space, you can write for example Shatabdi_Express) ";
        cin >> tname;
        cout << "\nYou can add 3 Stops/Station between Boarding point and Destination point\n";

        cout << "\nBoarding point: ";
        cin >> bp;

        strcpy(station[0], bp);
        for (int i = 1; i < 4; i++)
        {
            cout << "\nEnter Station/Stop " << i << ": ";
            cin >> station[i];
        }
        cout << "\nDestination pt: ";
        cin >> dest;
        strcpy(station[4], dest);

        cout << "No of seats in 1A-Class & fare per ticket: \n";
        cout << "Please add seats as 10 and then your desired ticket fare; for eg: 10 2000\n";
        cin >> c1 >> c1fare;
        cout << "No of seats in 2A-Class & fare per ticket: \n";
        cout << "Please add seats as 10 and then your desired ticket fare; for eg: 10 2000\n";
        cin >> c2 >> c2fare;
        cout << "No of seats in 3SL-Class & fare per ticket: \n";
        cout << "Please add seats as 10 and then your desired ticket fare; for eg: 10 2000\n";
        cin >> c3 >> c3fare;

        cout << "Train Details added succesfully!..";
    }

    void displaydetail()
    {
        cout << "\n|Train No."
             << "\t"
             << "|Train Name"
             << "\t\t"
             << "|Boarding pt."
             << "\t\t"
             << "|Destination pt."
             << "\t\t";

        cout << "\n|" << tno << "\t\t"
             << "|" << tname << "\t";

        cout << "|" << station[0];
        cout << "\t\t\t|" << station[4];

        cout << "\n\n|1A-Class"
             << "\t"
             << "|1A-Class Fare"
             << "\t"
             << "|2A-Class"
             << "\t"
             << "|2A-Class Fare"
             << "\t"
             << "|3SL-Class"
             << "\t"
             << "|3SL-Class Fare"
             << "\t";

        cout << "\n|" << c1 << "\t\t"
             << "|" << c1fare << "\t\t"
             << "|" << c2 << "\t\t"
             << "|" << c2fare << "\t\t"
             << "|" << c3 << "\t\t"
             << "|" << c3fare << "\t\t";

        cout << "\n\n|Route and Day of Departure"
             << "\n";

        cout << "|";
        for (int i = 0; i < 4; i++)
        {
            cout << station[i] << " -> ";
        }
        cout << station[4];
        cout << endl;

        cout << "|Monday(M)-Monday(M)-Tuesday(T)-Tuesday(T)-Wednesday(W)" << endl;
    }
};

//Class for taking and showing reservation details
//Class for checking current availability, changing availability after reservation or cancellation
class Reservation : public Detail
{
public:
    int pnr;
    int tno;
    char tname[100]; // '\0'
    char bp[100];
    char dest[100];
    char pname[10][100];
    char fc[5][100], sc[5][100], slc[5][100];
    int fc1[5][10], sc1[5][10], slc1[5][10];
    int fc2[5][10], sc2[5][10], slc2[5][10];
    int age[10];
    int seats[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char clas;
    int nosr, day;
    char day1[20];
    int i;
    int d, m, y;
    float amc;
    int count = 10;

    Reservation()
    {
        fstream f1, f2, f3;
        f1.open("available_fc1.txt", ios::in | ios::out | ios::binary | ios::trunc);
        f2.open("available_sc1.txt", ios::in | ios::out | ios::binary | ios::trunc);
        f3.open("available_slc1.txt", ios::in | ios::out | ios::binary | ios::trunc);

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                fc2[i][j] = j + 1;
                sc2[i][j] = j + 1;
                slc2[i][j] = j + 1;
            }
        }

        f1.write((char *)&fc2, sizeof(fc2));
        f2.write((char *)&sc2, sizeof(sc2));
        f3.write((char *)&slc2, sizeof(slc2));
        f1.close();
        f2.close();
        f3.close();
    }

    void change_availability(int tnum, char clas1, char bp1[100], char dest1[100], int nosr1, char day2[20], int seats1[10])
    {
        Detail a;
        int l = nosr1, k = 0; //for displaying seats
        fstream f1, f2, f3;   //for 1A class
        fstream f4, f5;       //for 2A class
        fstream f6, f7;       //for SL class

        f2.open("trains.txt", ios::in | ios::out | ios::binary);
        f1.open("available_fc1.txt", ios::in | ios::out | ios::binary);
        f4.open("available_sc1.txt", ios::in | ios::out | ios::binary);
        f6.open("available_slc1.txt", ios::in | ios::out | ios::binary);

        while (f1.read((char *)&fc1, sizeof(fc1)) && f4.read((char *)&sc1, sizeof(sc1)) && f6.read((char *)&slc1, sizeof(slc1)))
        {
            while (f2.read((char *)&a, sizeof(a)))
            {
                if (a.tno == tnum)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        //Printing Names of station in first column
                        strcpy(fc[i], a.station[i]);
                        strcpy(sc[i], a.station[i]);
                        strcpy(slc[i], a.station[i]);
                    }

                    //For AC 1A class
                    if (clas1 == '1')
                    {
                        //From Delhi
                        if (strcmp(bp1, a.station[0]) == 0)
                        {
                            i = 0;

                            //On Monday
                            if (strcmp(day2, "Monday") == 0)
                            {
                                //between Boarding point and station 1
                                if (strcmp(dest1, a.station[1]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 1; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            fc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                    f3.write((char *)&fc1, sizeof(fc1));
                                    f3.close();
                                }

                                //between Boarding point and station 2
                                else if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 2; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            fc1[i][seats1[j] - 1] = seats1[j];
                                            fc1[i + 1][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                    f3.write((char *)&fc1, sizeof(fc1));
                                    f3.close();
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 3; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            fc1[i][seats1[j] - 1] = seats1[j];
                                            fc1[i + 1][seats1[j] - 1] = seats1[j];
                                            fc1[i + 2][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                    f3.write((char *)&fc1, sizeof(fc1));
                                    f3.close();
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 4; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            fc1[i][seats1[j] - 1] = seats1[j];
                                            fc1[i + 1][seats1[j] - 1] = seats1[j];
                                            fc1[i + 2][seats1[j] - 1] = seats1[j];
                                            fc1[i + 3][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                    f3.write((char *)&fc1, sizeof(fc1));
                                    f3.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << fc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << fc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }

                        //From Lucknow
                        if (strcmp(bp1, a.station[1]) == 0)
                        {
                            i = 1;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {

                                //between Boarding point and station 2
                                if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 2; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            fc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                    f3.write((char *)&fc1, sizeof(fc1));
                                    f3.close();
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 3; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            fc1[i][seats1[j] - 1] = seats1[j];
                                            fc1[i + 1][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                    f3.write((char *)&fc1, sizeof(fc1));
                                    f3.close();
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 4; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            fc1[i][seats1[j] - 1] = seats1[j];
                                            fc1[i + 1][seats1[j] - 1] = seats1[j];
                                            fc1[i + 2][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                    f3.write((char *)&fc1, sizeof(fc1));
                                    f3.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << fc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << fc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }

                        //From Varanasi
                        if (strcmp(bp1, a.station[2]) == 0)
                        {
                            i = 2;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {

                                //between Boarding point and station 3
                                if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 3; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            fc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                    f3.write((char *)&fc1, sizeof(fc1));
                                    f3.close();
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 4; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            fc1[i][seats1[j] - 1] = seats1[j];
                                            fc1[i + 1][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                    f3.write((char *)&fc1, sizeof(fc1));
                                    f3.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << fc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << fc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }

                        //From Patna
                        if (strcmp(bp1, a.station[3]) == 0)
                        {
                            i = 3;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {

                                //between Boarding point and station 4
                                if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 3; i < 4; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            fc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                    f3.write((char *)&fc1, sizeof(fc1));
                                    f3.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << fc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << fc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }
                    }

                    //For AC 2A class
                    if (clas1 == '2')
                    {
                        //From Delhi
                        if (strcmp(bp1, a.station[0]) == 0)
                        {
                            i = 0;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {
                                //between Boarding point and station 1
                                if (strcmp(dest1, a.station[1]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 1; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            sc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                    f5.write((char *)&sc1, sizeof(sc1));
                                    f5.close();
                                }

                                //between Boarding point and station 2
                                else if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 2; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            sc1[i][seats1[j] - 1] = seats1[j];
                                            sc1[i + 1][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                    f5.write((char *)&sc1, sizeof(sc1));
                                    f5.close();
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 3; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            sc1[i][seats1[j] - 1] = seats1[j];
                                            sc1[i + 1][seats1[j] - 1] = seats1[j];
                                            sc1[i + 2][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                    f5.write((char *)&sc1, sizeof(sc1));
                                    f5.close();
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 4; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            sc1[i][seats1[j] - 1] = seats1[j];
                                            sc1[i + 1][seats1[j] - 1] = seats1[j];
                                            sc1[i + 2][seats1[j] - 1] = seats1[j];
                                            sc1[i + 3][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                    f5.write((char *)&sc1, sizeof(sc1));
                                    f5.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << sc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << sc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }

                        //From Lucknow
                        if (strcmp(bp1, a.station[1]) == 0)
                        {
                            i = 1;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {

                                //between Boarding point and station 2
                                if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 2; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            sc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                    f5.write((char *)&sc1, sizeof(sc1));
                                    f5.close();
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 3; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            sc1[i][seats1[j] - 1] = seats1[j];
                                            sc1[i + 1][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                    f5.write((char *)&sc1, sizeof(sc1));
                                    f5.close();
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 4; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            sc1[i][seats1[j] - 1] = seats1[j];
                                            sc1[i + 1][seats1[j] - 1] = seats1[j];
                                            sc1[i + 2][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                    f5.write((char *)&sc1, sizeof(sc1));
                                    f5.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << sc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << sc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }

                        //From Varanasi
                        if (strcmp(bp1, a.station[2]) == 0)
                        {
                            i = 2;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {

                                //between Boarding point and station 3
                                if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 3; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            sc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                    f5.write((char *)&sc1, sizeof(sc1));
                                    f5.close();
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 4; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            sc1[i][seats1[j] - 1] = seats1[j];
                                            sc1[i + 1][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                    f5.write((char *)&sc1, sizeof(sc1));
                                    f5.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << sc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << sc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }

                        //From Patna
                        if (strcmp(bp1, a.station[3]) == 0)
                        {
                            i = 3;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {

                                //between Boarding point and station 4
                                if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 3; i < 4; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            sc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                    f5.write((char *)&sc1, sizeof(sc1));
                                    f5.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << sc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << sc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }
                    }

                    //For SL class
                    if (clas1 == '3')
                    {
                        //From Delhi
                        if (strcmp(bp1, a.station[0]) == 0)
                        {
                            i = 0;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {
                                //between Boarding point and station 1
                                if (strcmp(dest1, a.station[1]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 1; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            slc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                    f7.write((char *)&slc1, sizeof(slc1));
                                    f7.close();
                                }

                                //between Boarding point and station 2
                                else if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 2; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            slc1[i][seats1[j] - 1] = seats1[j];
                                            slc1[i + 1][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                    f7.write((char *)&slc1, sizeof(slc1));
                                    f7.close();
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 3; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            slc1[i][seats1[j] - 1] = seats1[j];
                                            slc1[i + 1][seats1[j] - 1] = seats1[j];
                                            slc1[i + 2][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                    f7.write((char *)&slc1, sizeof(slc1));
                                    f7.close();
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 4; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            slc1[i][seats1[j] - 1] = seats1[j];
                                            slc1[i + 1][seats1[j] - 1] = seats1[j];
                                            slc1[i + 2][seats1[j] - 1] = seats1[j];
                                            slc1[i + 3][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                    f7.write((char *)&slc1, sizeof(slc1));
                                    f7.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << slc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << slc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }

                        //From Lucknow
                        if (strcmp(bp1, a.station[1]) == 0)
                        {
                            i = 1;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {
                                //between Boarding point and station 2
                                if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 2; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            slc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                    f7.write((char *)&slc1, sizeof(slc1));
                                    f7.close();
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 3; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            slc1[i][seats1[j] - 1] = seats1[j];
                                            slc1[i + 1][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                    f7.write((char *)&slc1, sizeof(slc1));
                                    f7.close();
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 4; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            slc1[i][seats1[j] - 1] = seats1[j];
                                            slc1[i + 1][seats1[j] - 1] = seats1[j];
                                            slc1[i + 2][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                    f7.write((char *)&slc1, sizeof(slc1));
                                    f7.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << slc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << slc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }

                        //From Varanasi
                        if (strcmp(bp1, a.station[2]) == 0)
                        {
                            i = 2;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {
                                //between Boarding point and station 3
                                if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 3; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            slc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                    f7.write((char *)&slc1, sizeof(slc1));
                                    f7.close();
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 4; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            slc1[i][seats1[j] - 1] = seats1[j];
                                            slc1[i + 1][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                    f7.write((char *)&slc1, sizeof(slc1));
                                    f7.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << slc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << slc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }

                        //From Patna
                        if (strcmp(bp1, a.station[3]) == 0)
                        {
                            i = 3;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {
                                //between Boarding point and station 4
                                if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 3; i < 4; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    for (int j = 0; j < nosr1; j++)
                                    {
                                        if (seats1[j] != 0)
                                        {
                                            slc1[i][seats1[j] - 1] = seats1[j];
                                        }
                                    }

                                    f1.close();
                                    f4.close();
                                    f6.close();

                                    f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                    f7.write((char *)&slc1, sizeof(slc1));
                                    f7.close();
                                }

                                cout << "Seats cancelled: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats1[i] << " ";
                                }
                                cout << endl;

                                cout << "Availability after Cancellation: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << slc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << slc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
        f2.close();
    }

    void check_availability(int tnum, char clas1, char bp1[100], char dest1[100], int nosr1, char day2[20])
    {
        Detail a;
        int l = nosr1, k = 0;
        fstream f1, f2, f3; //for 1A class
        fstream f4, f5;     //for 2A class
        fstream f6, f7;     //for SL class

        f2.open("trains.txt", ios::in | ios::out | ios::binary);
        f1.open("available_fc1.txt", ios::in | ios::out | ios::binary);
        f4.open("available_sc1.txt", ios::in | ios::out | ios::binary);
        f6.open("available_slc1.txt", ios::in | ios::out | ios::binary);

        while (f1.read((char *)&fc1, sizeof(fc1)) && f4.read((char *)&sc1, sizeof(sc1)) && f6.read((char *)&slc1, sizeof(slc1)))
        {
            while (f2.read((char *)&a, sizeof(a)))
            {
                if (a.tno == tnum)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        //Printing Names of station in first column
                        strcpy(fc[i], a.station[i]);
                        strcpy(sc[i], a.station[i]);
                        strcpy(slc[i], a.station[i]);
                    }

                    //For AC 1A class
                    if (clas1 == '1')
                    {
                        //From Delhi
                        if (strcmp(bp1, a.station[0]) == 0)
                        {
                            i = 0;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {
                                //between Boarding point and station 1
                                if (strcmp(dest1, a.station[1]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 1; i++)
                                    {
                                        cout << fc[i] << " -> \t";

                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (fc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count << endl;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (fc1[i][j] != 0 && (fc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                fc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }

                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                        f3.write((char *)&fc1, sizeof(fc1));
                                        f3.close();
                                    }

                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 2
                                else if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 2; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (fc1[i][j] == 0 || fc1[i + 1][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (fc1[i][j] != 0 && fc1[i + 1][j] != 0 && (fc1[i][j] == (j + 1)) && (fc1[i + 1][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                fc1[i][j] = 0;
                                                fc1[i + 1][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }

                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                        f3.write((char *)&fc1, sizeof(fc1));
                                        f3.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 3; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (fc1[i][j] == 0 || fc1[i + 1][j] == 0 || fc1[i + 2][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (fc1[i][j] != 0 && fc1[i + 1][j] != 0 && fc1[i + 2][j] != 0 && (fc1[i][j] == (j + 1)) && (fc1[i + 1][j] == (j + 1)) && (fc1[i + 2][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                fc1[i][j] = 0;
                                                fc1[i + 1][j] = 0;
                                                fc1[i + 2][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                        f3.write((char *)&fc1, sizeof(fc1));
                                        f3.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 4; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (fc1[i][j] == 0 || fc1[i + 1][j] == 0 || fc1[i + 2][j] == 0 || fc1[i + 3][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (fc1[i][j] != 0 && fc1[i + 1][j] != 0 && fc1[i + 2][j] != 0 && fc1[i + 3][j] != 0 && (fc1[i][j] == (j + 1)) && (fc1[i + 1][j] == (j + 1)) && (fc1[i + 2][j] == (j + 1)) && (fc1[i + 3][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                fc1[i][j] = 0;
                                                fc1[i + 1][j] = 0;
                                                fc1[i + 2][j] = 0;
                                                fc1[i + 3][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                        f3.write((char *)&fc1, sizeof(fc1));
                                        f3.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << fc[i] << " -> \t";
                                    //Display final availability
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << fc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Mondays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }

                        //From Lucknow
                        if (strcmp(bp1, a.station[1]) == 0)
                        {
                            i = 1;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {
                                //between Boarding point and station 2
                                if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 2; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (fc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (fc1[i][j] != 0 && (fc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                fc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                        f3.write((char *)&fc1, sizeof(fc1));
                                        f3.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 3; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (fc1[i][j] == 0 || fc1[i + 1][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (fc1[i][j] != 0 && fc1[i + 1][j] != 0 && (fc1[i][j] == (j + 1)) && (fc1[i + 1][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                fc1[i][j] = 0;
                                                fc1[i + 1][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                        f3.write((char *)&fc1, sizeof(fc1));
                                        f3.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 4; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (fc1[i][j] == 0 || fc1[i + 1][j] == 0 || fc1[i + 2][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (fc1[i][j] != 0 && fc1[i + 1][j] != 0 && fc1[i + 2][j] != 0 && (fc1[i][j] == (j + 1)) && (fc1[i + 1][j] == (j + 1)) && (fc1[i + 2][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                fc1[i][j] = 0;
                                                fc1[i + 1][j] = 0;
                                                fc1[i + 2][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                        f3.write((char *)&fc1, sizeof(fc1));
                                        f3.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << fc[i] << " -> \t";
                                    //Display final availability
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << fc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Mondays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }

                        //From Varanasi
                        if (strcmp(bp1, a.station[2]) == 0)
                        {
                            i = 2;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {
                                //between Boarding point and station 3
                                if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 3; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (fc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (fc1[i][j] != 0 && (fc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                fc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                        f3.write((char *)&fc1, sizeof(fc1));
                                        f3.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 4; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (fc1[i][j] == 0 || fc1[i + 1][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (fc1[i][j] != 0 && fc1[i + 1][j] != 0 && (fc1[i][j] == (j + 1)) && (fc1[i + 1][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                fc1[i][j] = 0;
                                                fc1[i + 1][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                        f3.write((char *)&fc1, sizeof(fc1));
                                        f3.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << fc[i] << " -> \t";
                                    //Display final availability
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << fc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Tuesdays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }

                        //From Patna
                        if (strcmp(bp1, a.station[3]) == 0)
                        {
                            i = 3;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {
                                //between Boarding point and station 4
                                if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 3; i < 4; i++)
                                    {
                                        cout << fc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << fc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (fc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (fc1[i][j] != 0 && (fc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                fc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f3.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                                        f3.write((char *)&fc1, sizeof(fc1));
                                        f3.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << fc[i] << " -> \t";
                                    //Display final availability
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << fc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Tuesdays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }
                    }

                    //For AC 2A class
                    if (clas1 == '2')
                    {
                        //From Delhi
                        if (strcmp(bp1, a.station[0]) == 0)
                        {
                            i = 0;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {
                                //between Boarding point and station 1
                                if (strcmp(dest1, a.station[1]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 1; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (sc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (sc1[i][j] != 0 && (sc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                sc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                        f5.write((char *)&sc1, sizeof(sc1));
                                        f5.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 2
                                else if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 2; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (sc1[i][j] == 0 || sc1[i + 1][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (sc1[i][j] != 0 && sc1[i + 1][j] != 0 && (sc1[i][j] == (j + 1)) && (sc1[i + 1][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                sc1[i][j] = 0;
                                                sc1[i + 1][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                        f5.write((char *)&sc1, sizeof(sc1));
                                        f5.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 3; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (sc1[i][j] == 0 || sc1[i + 1][j] == 0 || sc1[i + 2][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (sc1[i][j] != 0 && sc1[i + 1][j] != 0 && sc1[i + 2][j] != 0 && (sc1[i][j] == (j + 1)) && (sc1[i + 1][j] == (j + 1)) && (sc1[i + 2][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                sc1[i][j] = 0;
                                                sc1[i + 1][j] = 0;
                                                sc1[i + 2][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                        f5.write((char *)&sc1, sizeof(sc1));
                                        f5.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 4; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (sc1[i][j] == 0 || sc1[i + 1][j] == 0 || sc1[i + 2][j] == 0 || sc1[i + 3][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (sc1[i][j] != 0 && sc1[i + 1][j] != 0 && sc1[i + 2][j] != 0 && sc1[i + 3][j] != 0 && (sc1[i][j] == (j + 1)) && (sc1[i + 1][j] == (j + 1)) && (sc1[i + 2][j] == (j + 1)) && (sc1[i + 3][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                sc1[i][j] = 0;
                                                sc1[i + 1][j] = 0;
                                                sc1[i + 2][j] = 0;
                                                sc1[i + 3][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                        f5.write((char *)&sc1, sizeof(sc1));
                                        f5.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << sc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << sc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Mondays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }

                        //From Lucknow
                        if (strcmp(bp1, a.station[1]) == 0)
                        {
                            i = 1;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {
                                //between Boarding point and station 2
                                if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 2; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (sc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (sc1[i][j] != 0 && (sc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                sc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                        f5.write((char *)&sc1, sizeof(sc1));
                                        f5.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 3; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (sc1[i][j] == 0 || sc1[i + 1][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (sc1[i][j] != 0 && sc1[i + 1][j] != 0 && (sc1[i][j] == (j + 1)) && (sc1[i + 1][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                sc1[i][j] = 0;
                                                sc1[i + 1][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                        f5.write((char *)&sc1, sizeof(sc1));
                                        f5.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 4; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (sc1[i][j] == 0 || sc1[i + 1][j] == 0 || sc1[i + 2][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (sc1[i][j] != 0 && sc1[i + 1][j] != 0 && sc1[i + 2][j] != 0 && (sc1[i][j] == (j + 1)) && (sc1[i + 1][j] == (j + 1)) && (sc1[i + 2][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                sc1[i][j] = 0;
                                                sc1[i + 1][j] = 0;
                                                sc1[i + 2][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                        f5.write((char *)&sc1, sizeof(sc1));
                                        f5.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << sc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << sc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Mondays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }

                        //From Varanasi
                        if (strcmp(bp1, a.station[2]) == 0)
                        {
                            i = 2;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {

                                //between Boarding point and station 3
                                if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 3; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (sc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (sc1[i][j] != 0 && (sc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                sc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                        f5.write((char *)&sc1, sizeof(sc1));
                                        f5.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 4; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (sc1[i][j] == 0 || sc1[i + 1][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (sc1[i][j] != 0 && sc1[i + 1][j] != 0 && (sc1[i][j] == (j + 1)) && (sc1[i + 1][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                sc1[i][j] = 0;
                                                sc1[i + 1][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                        f5.write((char *)&sc1, sizeof(sc1));
                                        f5.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << sc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << sc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Tuesdays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }

                        //From Patna
                        if (strcmp(bp1, a.station[3]) == 0)
                        {
                            i = 3;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {

                                //between Boarding point and station 4
                                if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 3; i < 4; i++)
                                    {
                                        cout << sc[i] << " -> \t";
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << sc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (sc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (sc1[i][j] != 0 && (sc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                sc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f5.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                                        f5.write((char *)&sc1, sizeof(sc1));
                                        f5.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << sc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << sc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Tuesdays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }
                    }

                    //For SL class
                    if (clas1 == '3')
                    {
                        //From Delhi
                        if (strcmp(bp1, a.station[0]) == 0)
                        {
                            i = 0;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {
                                //between Boarding point and station 1
                                if (strcmp(dest1, a.station[1]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 1; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (slc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (slc1[i][j] != 0 && (slc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                slc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                        f7.write((char *)&slc1, sizeof(slc1));
                                        f7.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 2
                                else if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 2; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (slc1[i][j] == 0 || slc1[i + 1][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (slc1[i][j] != 0 && slc1[i + 1][j] != 0 && (slc1[i][j] == (j + 1)) && (slc1[i + 1][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                slc1[i][j] = 0;
                                                slc1[i + 1][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                        f7.write((char *)&slc1, sizeof(slc1));
                                        f7.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 3; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (slc1[i][j] == 0 || slc1[i + 1][j] == 0 || slc1[i + 2][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (slc1[i][j] != 0 && slc1[i + 1][j] != 0 && slc1[i + 2][j] != 0 && (slc1[i][j] == (j + 1)) && (slc1[i + 1][j] == (j + 1)) && (slc1[i + 2][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                slc1[i][j] = 0;
                                                slc1[i + 1][j] = 0;
                                                slc1[i + 2][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                        f7.write((char *)&slc1, sizeof(slc1));
                                        f7.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 0; i < 4; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (slc1[i][j] == 0 || slc1[i + 1][j] == 0 || slc1[i + 2][j] == 0 || slc1[i + 3][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (slc1[i][j] != 0 && slc1[i + 1][j] != 0 && slc1[i + 2][j] != 0 && slc1[i + 3][j] != 0 && (slc1[i][j] == (j + 1)) && (slc1[i + 1][j] == (j + 1)) && (slc1[i + 2][j] == (j + 1)) && (slc1[i + 3][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                slc1[i][j] = 0;
                                                slc1[i + 1][j] = 0;
                                                slc1[i + 2][j] = 0;
                                                slc1[i + 3][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                        f7.write((char *)&slc1, sizeof(slc1));
                                        f7.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << slc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << slc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Mondays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }

                        //From Lucknow
                        if (strcmp(bp1, a.station[1]) == 0)
                        {
                            i = 1;

                            //On Mondays
                            if (strcmp(day2, "Monday") == 0)
                            {

                                //between Boarding point and station 2
                                if (strcmp(dest1, a.station[2]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 2; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (slc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (slc1[i][j] != 0 && (slc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                slc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                        f7.write((char *)&slc1, sizeof(slc1));
                                        f7.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 3
                                else if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 3; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (slc1[i][j] == 0 || slc1[i + 1][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (slc1[i][j] != 0 && slc1[i + 1][j] != 0 && (slc1[i][j] == (j + 1)) && (slc1[i + 1][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                slc1[i][j] = 0;
                                                slc1[i + 1][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                        f7.write((char *)&slc1, sizeof(slc1));
                                        f7.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 1; i < 4; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (slc1[i][j] == 0 || slc1[i + 1][j] == 0 || slc1[i + 2][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (slc1[i][j] != 0 && slc1[i + 1][j] != 0 && slc1[i + 2][j] != 0 && (slc1[i][j] == (j + 1)) && (slc1[i + 1][j] == (j + 1)) && (slc1[i + 2][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                slc1[i][j] = 0;
                                                slc1[i + 1][j] = 0;
                                                slc1[i + 2][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                        f7.write((char *)&slc1, sizeof(slc1));
                                        f7.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << slc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << slc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Mondays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }

                        //From Varanasi
                        if (strcmp(bp1, a.station[2]) == 0)
                        {
                            i = 2;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {

                                //between Boarding point and station 3
                                if (strcmp(dest1, a.station[3]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 3; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (slc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (slc1[i][j] != 0 && (slc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                slc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                        f7.write((char *)&slc1, sizeof(slc1));
                                        f7.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                //between Boarding point and station 4
                                else if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 2; i < 4; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (slc1[i][j] == 0 || slc1[i + 1][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (slc1[i][j] != 0 && slc1[i + 1][j] != 0 && (slc1[i][j] == (j + 1)) && (slc1[i + 1][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                slc1[i][j] = 0;
                                                slc1[i + 1][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                        f7.write((char *)&slc1, sizeof(slc1));
                                        f7.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << slc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << slc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Tuesdays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }

                        //From Patna
                        if (strcmp(bp1, a.station[3]) == 0)
                        {
                            i = 3;

                            //On Tuesdays
                            if (strcmp(day2, "Tuesday") == 0)
                            {

                                //between Boarding point and station 4
                                if (strcmp(dest1, a.station[4]) == 0)
                                {
                                    cout << "Current availability of seats between Boarding point and Destination:\n";

                                    //Displaying Current availability
                                    for (int i = 3; i < 4; i++)
                                    {
                                        cout << slc[i] << " -> \t";
                                        //Display final availability
                                        for (int j = 0; j < 10; j++)
                                        {
                                            cout << slc1[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    //Calculating available seats
                                    for (int j = 0; j < 10; j++)
                                    {
                                        if (slc1[i][j] == 0)
                                        {
                                            --count;
                                        }
                                    }

                                    //Displaying available seats
                                    cout << "\nAvailable seats are: " << count;

                                    //Checking availability
                                    if (count >= nosr1)
                                    {
                                        for (int j = 0; j < 10; j++)
                                        {
                                            if (slc1[i][j] != 0 && (slc1[i][j] == (j + 1)) && nosr1 > 0)
                                            {
                                                slc1[i][j] = 0;
                                                seats[k] = j + 1;
                                                k++;
                                                nosr1--;
                                            }
                                        }
                                        f1.close();
                                        f4.close();
                                        f6.close();

                                        f7.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                                        f7.write((char *)&slc1, sizeof(slc1));
                                        f7.close();
                                    }
                                    else
                                    {
                                        cout << "Sorry seats are not available between the entered Boarding point and Destination.\n";
                                        cin.get();
                                        cin.get();
                                        user_menu();
                                    }
                                }

                                cout << "\nBooked seats: ";
                                for (int i = 0; i < l; i++)
                                {
                                    cout << seats[i] << " ";
                                }
                                cout << endl;

                                cout << "\nAvailability after Booking: \n";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << slc[i] << " -> \t";
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << slc1[i][j] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "This train runs " << a.station[i] << " on only Tuesdays.";
                                cin.get();
                                cin.get();
                                user_menu();
                            }
                        }
                    }
                }
            }
        }
        f2.close();
    }

    void dayofweek(int d, int m, int y)
    {
        int day;
        char week[][20] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        static int t[] = {0, 3, 2, 5, 0, 3,
                          5, 1, 4, 6, 2, 4};
        y -= m < 3;
        day = ((y + y / 4 - y / 100 +
                y / 400 + t[m - 1] + d) %
               7);
        cout << "Day: " << week[day - 1] << endl;

        strcpy(day1, week[day - 1]);
    }

    void getresdet()
    {
        cout << "\n\nEnter the details as follows\n";
        cout << "Train no: ";
        cin >> tno;
        cout << "Train name: ";
        cin >> tname;
        cout << "Boarding point: ";
        cin >> bp;
        cout << "Destination pt: ";
        cin >> dest;
        cout << "Date of travel: ";
        cin >> d >> m >> y;
        dayofweek(d, m, y);

        cout << "Enter the class-> 1 for 1A class | 2 for 2A class | 3 for 3A class: ";
        cin >> clas;
        cout << "No of seats required: ";
        cin >> nosr;

        chart(tno, bp, dest, day1, d, m, y);
        //change_availability(tno, clas, bp, dest, nosr, day1, seats);
        check_availability(tno, clas, bp, dest, nosr, day1);

        for (i = 0; i < nosr; i++)
        {
            cout << "Passenger name: ";
            cin >> pname[i];
            cout << "Passenger age: ";
            cin >> age[i];
        }

        cout << "\n\n*******END OF GETTING DETAILS*******\n\n";
    }

    void displayresdet()
    {
        cout << "\n\n*******TICKET BOOKED*******\n";
        cout << "Pnr no: " << pnr;
        cout << "\nTrain no: " << tno;
        cout << "\nTrain name: " << tname;
        cout << "\nBoarding point: " << bp;
        cout << "\nDestination pt: " << dest;
        cout << "\nDate of reservation: " << d << "-" << m << "-" << y;
        cout << "\nDay of travel: " << day1;
        cout << "\nYour class: ";
        cout << clas;
        cout << "\nNo of seats reserved: " << nosr;
        for (i = 0; i < nosr; i++)
        {
            cout << "\nPassenger name: " << pname[i];
            cout << "\nPassenger age: " << age[i];
            cout << "\nSeat Number: " << seats[i];
        }

        cout << "\nYou must pay: " << amc << endl;
        cout << "***********************************\n";
    }
};

//Class for taking and showing details of Cancellation
class Cancellation : public Reservation
{
public:
    int c_pnr;
    int c_tno;
    char c_tname[100];
    char c_bp[100];
    char c_dest[100];
    char c_pname[10][100];
    int c_age[10];
    int c_seats[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char c_clas;
    int nosc;
    char c_day1[20];
    int cd, cm, cy;
    int td, tm, ty;
    float c_amc;

    void getcancdet()
    {
        cout << "Enter the details as follows\n";
        cout << "Pnr no: ";
        cin >> c_pnr;

        cout << "Date of cancellation: ";
        cin >> td >> tm >> ty;
        cout << "\n\n*******END OF GETTING DETAILS*******\n\n";
    }

    void displaycancdet()
    {
        cout << "************************.\n";
        cout << "************************.\n";
        cout << "Pnr no: " << c_pnr;
        cout << "\nTrain no: " << c_tno;
        cout << "\nTrain name: ";
        cout << c_tname;
        cout << "\nBoarding point: ";
        cout << c_bp;
        cout << "\nDestination pt: ";
        cout << c_dest;
        cout << "\nYour class: ";
        cout << c_clas;
        cout << "\nNo of seats to be cancelled: " << nosc;
        for (int i = 0; i < nosc; i++)
        {
            cout << "\nPassenger name: ";
            cout << c_pname[i];
            cout << "\nPassenger age: " << c_age[i];
            cout << "\nSeat Number: " << c_seats[i];
        }

        cout << "\nDate of cancellation: " << td << "-" << tm << "-" << ty;
        cout << "\nYou can collect: " << c_amc << " rs" << endl;
        cout << "\n*****************************************\n";
        cout << "*****CANCELLED SUCCESSFULLY*****\n";
        cout << "*****************************************\n";

        change_availability(c_tno, c_clas, c_bp, c_dest, nosc, c_day1, c_seats);
    }

    void display_cancel_admin()
    {
        cout << "************************.\n";
        cout << "Pnr no: " << c_pnr;
        cout << "\nTrain no: " << c_tno;
        cout << "\nTrain name: ";
        cout << c_tname;
        cout << "\nBoarding point: ";
        cout << c_bp;
        cout << "\nDestination pt: ";
        cout << c_dest;
        cout << "\nYour class: ";
        cout << c_clas;
        cout << "\nNo of seats cancelled: " << nosc;

        for (int i = 0; i < nosc; i++)
        {
            cout << "\nPassenger name: ";
            cout << c_pname[i];
            cout << "\nPassenger age: " << c_age[i];
            cout << "\nSeat Number: " << c_seats[i];
        }

        cout << "\nDate of cancellation: " << td << "-" << tm << "-" << ty;
        cout << "\n*****************************************\n\n";
        
    }
};

int main()
{
    system("CLS");
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << endl;
    cout << setw(90);
    cout << "------------------------------------------------------------------------ WELCOME TO ---------------------------------------------------------------------------------\n";
    cout << "--------------------------------------------------------------- TICKETING & RESERVATION SYSTEM ----------------------------------------------------------------------\n";
    cout << endl;
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << endl;
    cout << setw(110);
    cout << "\t\t****DISCLAIMER: DUE TO CURRENT COVID SITUATIONS AND POLICIES OF GOVERNMENT WE REQUEST ALL OUR USERS TO FOLLOW THE SAFETY PRECAUTIONS:****\n";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << endl;
    cout << setw(90);
    cout << "\t\t\t\t*********1.Please wear masks. 2.Sanitize your hand frequently. 3.Follow Social Distancing.***********\n";
    cout << setw(90);
    cout << "\t1.No linen and blankets shall be provided in trains. 2.Catering facilities are not available. 3.Please download Arogya Setu App prior coming to stations.\n";
    cout << endl;
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << endl;
    cout << setw(110);
    cout << "*********************PRESS ENTER TO CONTINUE*********************";
    cin.get();
    real_train();
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(110);
    cout << "*****WELCOME TO RAILWAY TICKET RESERVATION SYSTEM*****";
    cout << "\n\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    while (1)
    {
        cout << "\n\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << setw(90);
        cout << "*****MAIN MENU*****";
        cout << "\n\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\n\nEnter the action you want to perform:\n";
        cout << "1. Sign up\n2. Login\n3. Forgot Password?\n4. Exit the portal\n\n";

        char choice;
        cin >> choice;
        switch (choice)
        {
        case '1':
            sign_up();
            break;
        case '2':
            login();
            break;
        case '3':
            forgot_pass();
        case '4':
            exit(0);
        }
    }
}

void sign_up()
{
    real_train();
    Registration r1;
}

void login()
{
    real_train();
    string un, ps, u, p;
    char cha;
    int i = 0;
    system("CLS");

    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(90);
    cout << "*****Login*****";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    cin.ignore();
    cout << "Username: ";
    getline(cin, un);

    cout << "Password: ";
    //getline(cin, ps);

    while (true)
    {
        cha = getch();
        if (cha == 13)
            break;
        else if (cha == 8)
        {
            ps.pop_back();
            cout << "\b\b";
        }
        else
            ps.push_back(cha);
        cout << "*";
    }
    char b;

    cout << "\nPress 'y' to see your password\n";
    cin >> b;
    if (b == 'Y' || b == 'y')
    {
        cout << ps << endl;
    }

    if (un == "admin" && ps == "123456")
    {
        admin();
        cin.get();
        cin.get();
    }

    ifstream input("u&p.txt");

    //Created a while loop for searching every line of a file
    while (!input.eof())
    {
        input.seekg(i);
        getline(input, u, '\n');

        if (u == un)
        {
            getline(input, p, '*');

            if (p == ps)
            {
                cout << "You successfully logged in to the portal..";
                input.close();
                cin.get();
                user_menu();
                break;
            }
        }
        i++;
    }
    input.close();
    cout << "Sorry! You are entering wrong Username or Password..\n";
    cout << "Try entering correct Username and Password or create a new account..\n";
    cin.get();
    cin.get();
    main();
}

void forgot_pass()
{
    real_train();
    string mail, m, u, p, s;
    int i = 0;
    system("CLS");

    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(90);
    cout << "*****Forgot Password*****";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    cin.ignore();
    cout << "Enter the email address linked with your account: ";
    getline(cin, mail);

    fstream input("u&p.txt");

    while (!input.eof())
    {
        input.seekg(i);
        getline(input, m, '\n');

        if (m == mail)
        {
            cout << "Congratulations! We found your account..\n";
            getline(input, u, '\n');
            //cout << "You Username is: " << u << "\n";
            getline(input, p, '*');
            cout << "You Password is: " << p << "\n";
            cout << "You can now proceed with the login..\n";
            cin.get();
            cin.get();
            main();
        }
        i++;
    }
    input.close();
    cout << "Sorry! We could not find your account linked with the entered email id..\n";
    cout << "Try to enter a new email id or create a new account..\n";
    cin.get();
    cin.get();
    main();
}

void admin()
{
    real_train();
    Detail a;
    fstream train;
    int ch;
    system("CLS");
    cout << setw(90);
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(90);
    cout << "*****Welcome Admin*****";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    do
    {
        cout << "\n --- ADMINISTRATOR MENU --- \n";
        cout << "1. Add Train details \n";
        cout << "2. Display Train details \n";
        cout << "3. Diplay Passenger reservation details \n";
        cout << "4. Diplay Cancelled tickets \n";
        cout << "5. Return to Main Menu \n";

        cout << "Enter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            train.open("trains.txt", ios::in | ios::out | ios::app | ios::binary);
            a.getDetail();
            train.write((char *)&a, sizeof(a));
            train.close();
            break;

        case 2:
            train.open("trains.txt", ios::in | ios::out | ios::app | ios::binary);
            while (train.read((char *)&a, sizeof(a)))
            {
                a.displaydetail();
            }
            train.close();
            break;

        case 3:
            pass_details();
            break;
        case 4:
            can_ticket_details();
            break;
        case 5:
            main();
        }

    } while (ch < 6);
}

void pass_details()
{
    real_train();
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(90);
    cout << "*****Passenger Details*****";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    fstream f1, f2;
    Reservation b;
    Cancellation c;
    f1.open("res_details.txt", ios::in | ios::out | ios::binary);
    f2.open("can_details.txt", ios::in | ios::out | ios::binary);

    f1.seekg(0);

    while (f1.read((char *)&b, sizeof(b)))
    {
        flag = 0;
        while (f2.read((char *)&c, sizeof(c)))
        {
            if (b.pnr == c.c_pnr)
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            b.displayresdet();
        }
    }

    f1.close();
    f2.close();
    cin.get();
    cin.get();
    admin();
}

void can_ticket_details()
{
    real_train();
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(90);
    cout << "*****Cancelled Passenger Details*****";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    fstream f1;
    Cancellation c;

    f1.open("can_details.txt", ios::in | ios::out | ios::binary);

    f1.seekg(0);

    while (f1.read((char *)&c, sizeof(c)))
    {
        c.display_cancel_admin();
    }

    f1.close();
    cin.get();
    cin.get();
    admin();
}

void res_ticket_details()
{
    real_train();
    system("CLS");
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(90);
    cout << "*****Passenger Details*****";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    fstream f1, f2;
    Reservation b;
    Cancellation c;
    int pnr;
    cout << "\nEnter your PNR number: ";
    cin >> pnr;
    cout << endl
         << endl;

    f1.open("res_details.txt", ios::in | ios::out | ios::binary);
    f2.open("can_details.txt", ios::in | ios::out | ios::binary);

    f1.seekg(0);

    while (f1.read((char *)&b, sizeof(b)))
    {
        flag = 0;
        if (b.pnr == pnr)
        {
            while (f2.read((char *)&c, sizeof(c)))
            {
                if (pnr == c.c_pnr)
                {
                    cout << "Sorry! PNR status expired due to ticket cancellation.";
                    f1.close();
                    f2.close();
                    cin.get();
                    cin.get();
                    user_menu();
                }
            }
            b.displayresdet();
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "Invalid PNR status.. Try entering again!";
    }
    f1.close();
    f2.close();
    cin.get();
    cin.get();
    user_menu();
}

void user_view()
{
    fstream train;
    train.open("trains.txt", ios::in | ios::out | ios::app | ios::binary);
    Detail a;
    while (train.read((char *)&a, sizeof(a)))
    {
        a.displaydetail();
    }
    train.close();
}

void user_menu()
{
    real_train();
    int ch;
    Detail a;
    fstream train;
    system("CLS");

    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(90);
    cout << "*****User Menu*****";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    do
    {
        cout << "\n1. Show available trains\n2. Reserve a ticket\n3. Show Reserved Ticket\n4. Cancel a ticket\n5. Return to the main menu\n";

        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            user_view();
            break;
        case 2:
            res();
            break;
        case 3:
            res_ticket_details();
            break;
        case 4:
            can();
            break;
        case 5:
            main();
        }
    } while (ch <= 4);
}

void res()
{
    real_train();
    int ch;
    system("CLS");
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "*****Reservation Ticket Menu*****";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    do
    {
        cout << "\n1. Reserve a ticket\n2. Return to the User menu\n3. Return to the Main menu";
        cout << "\n\nEnter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            reservation();
            break;
        case 2:
            user_menu();
        case 3:
            main();
        }
    } while (ch <= 3);
}

void reservation()
{
    Detail a;
    Reservation b;
    fstream f1, f2;
    time_t t;

    f1.open("trains.txt", ios::in | ios::out | ios::binary);
    f2.open("res_details.txt", ios::in | ios::out | ios::binary | ios::app);
    int ch;

    b.getresdet();
    while (f1.read((char *)&a, sizeof(a)))
    {
        if (a.tno == b.tno)
        {
            if (b.clas == '1')
            {
                if (a.c1 >= b.nosr)
                {
                    amt = a.c1fare;
                    b.amc = b.nosr * amt;

                    //Generating random PNR
                    srand((unsigned)time(&t));
                    b.pnr = rand();
                    f2.write((char *)&b, sizeof(b));
                    b.displayresdet();
                    cout << "\n-----Your ticket is reserved-----\n";
                }
                else
                {
                    cout << "**********Sorry req seats not available********\n";
                }
            }

            else if (b.clas == '2')
            {
                if (a.c2 >= b.nosr)
                {
                    amt = a.c2fare;
                    b.amc = b.nosr * amt;

                    //Generating random PNR
                    srand((unsigned)time(&t));
                    b.pnr = rand();
                    f2.write((char *)&b, sizeof(b));
                    b.displayresdet();
                    cout << "\n-----Your ticket is reserved-----\n";
                }
                else
                {
                    cout << "********Sorry req no of seats not available*******\n";
                }
            }
            else if (b.clas == '3')
            {
                if (a.c3 >= b.nosr)
                {
                    amt = a.c3fare;
                    b.amc = b.nosr * amt;

                    //Generating random PNR
                    srand((unsigned)time(&t));
                    b.pnr = rand();
                    f2.write((char *)&b, sizeof(b));
                    b.displayresdet();
                    cout << "\n-----Your ticket is reserved-----\n";
                }
                else
                {
                    cout << "********Sorry req no of seats not available_fc1*******\n";
                }
            }
        }
    }

    f1.close();
    f2.close();
}

void can()
{
    real_train();
    int ch;
    system("CLS");
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(90);
    cout << "*****Cancellation Ticket Menu*****";
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    do
    {
        cout << "\n1. Cancel a ticket\n2. Return to the User menu\n3. Return to the Main menu";
        cout << "\n\nEnter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cancellation();
            break;
        case 2:
            user_menu();
        case 3:
            main();
        }
    } while (ch <= 3);
}

void cancellation()
{
    Reservation b;
    Cancellation c;
    fstream f1, f2;

    f1.open("res_details.txt", ios::in | ios::out | ios::binary);
    f2.open("can_details.txt", ios::in | ios::out | ios::binary | ios::app);

    cout << "\n\n**********CANCELLATION MENU*********\n\n";
    c.getcancdet();

    while (f1.read((char *)&b, sizeof(b)))
    {
        flag = 1;
        if (b.pnr == c.c_pnr)
        {
            c.c_tno = b.tno;
            strcpy(c.c_tname, b.tname);
            strcpy(c.c_bp, b.bp);
            strcpy(c.c_dest, b.dest);
            c.cd = b.d;
            c.cm = b.m;
            c.cy = b.y;
            strcpy(c.c_day1, b.day1);
            c.nosc = b.nosr;

            for (int j = 0; j < c.nosc; j++)
            {
                strcpy(c.c_pname[j], b.pname[j]);
                c.c_age[j] = b.age[j];
                c.c_seats[j] = b.seats[j];
            }
            c.c_clas = b.clas;

            //For class 1 ticket
            if (c.c_clas == '1')
            {
                tamt = b.amc;

                if ((c.td == b.d) && (c.tm == b.m))
                {
                    cout << "You are cancelling at the date of departure\n";
                    c.c_amc = tamt - ((tamt * 60) / 100);
                }
                else if (c.tm == b.m)
                {
                    cout << "You are cancelling within the month of departure\n";
                    c.c_amc = tamt - ((tamt * 50) / 100);
                }
                else if (b.m > c.tm)
                {
                    cout << "You are cancelling one month before the date of departure\n";
                    c.c_amc = tamt - ((tamt * 20) / 100);
                }
                else
                {
                    cout << "Cancelling after the departure\n";
                    cout << "Your request cannot be completed\n";
                }
                flag = 1;
                chart(c.c_tno, c.c_bp, c.c_dest, c.c_day1, c.cd, c.cm, c.cy);
                f2.write((char *)&c, sizeof(c));
                c.displaycancdet();
                break;
            }

            //For class 2 ticket
            else if (c.c_clas == '2')
            {
                tamt = b.amc;
                if ((c.td == b.d) && (c.tm == b.m))
                {
                    cout << "You are cancelling at the date of departure\n";
                    c.c_amc = tamt - ((tamt * 60) / 100);
                }
                else if (c.tm == b.m)
                {
                    cout << "You are cancelling within the month of departure\n";
                    c.c_amc = tamt - ((tamt * 50) / 100);
                }
                else if (b.m > c.tm)
                {
                    cout << "You are cancelling one month before the date of departure\n";
                    c.c_amc = tamt - ((tamt * 20) / 100);
                }
                else
                {
                    cout << "Cancelling after the departure\n";
                    cout << "Your request cannot be completed\n";
                }
                flag = 1;
                c.displaycancdet();
                chart(c.c_tno, c.c_bp, c.c_dest, c.c_day1, c.cd, c.cm, c.cy);
                f2.write((char *)&c, sizeof(c));
                break;
            }

            //For class 3 ticket
            else if (c.c_clas == '3')
            {
                tamt = b.amc;
                if ((c.td == b.d) && (c.tm == b.m))
                {
                    cout << "You are cancelling at the date of departure\n";
                    c.c_amc = tamt - ((tamt * 60) / 100);
                }
                else if (c.tm == b.m)
                {
                    cout << "You are cancelling within the month of departure\n";
                    c.c_amc = tamt - ((tamt * 50) / 100);
                }
                else if (b.m > c.tm)
                {
                    cout << "You are cancelling one month before the date of departure\n";
                    c.c_amc = tamt - ((tamt * 20) / 100);
                }
                else
                {
                    cout << "Cancelling after the departure\n";
                    cout << "Your request cannot be completed\n";
                }
                flag = 1;
                c.displaycancdet();
                chart(c.c_tno, c.c_bp, c.c_dest, c.c_day1, c.cd, c.cm, c.cy);
                f2.write((char *)&c, sizeof(c));
                break;
            }
        }
        else
        {
            flag = 0;
        }
    }
    if (flag == 0)
    {
        cout << "Enter the correct pnr no\n";
    }
    f1.close();
    f2.close();
}

void real_train()
{
    system("CLS");
    cout << "                                                                                                                  ~  ~__   |~~~~~|" << endl;
    cout << "                                                                                                                  Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                                                                                                 {||||CU|,|____|" << endl;
    cout << "                                                                                                                //oo---OO=OO     OOO     OOO  ********";
    Sleep(85);
    system("CLS");
    cout << "                                                                                                          ~  __   |~~~~|" << endl;
    cout << "                                                                                                          Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                                                                                         {||||CU|,|____|" << endl;
    cout << "                                                                                                        //oo---OO=OO     OOO     OOO  ************";
    Sleep(85);
    system("CLS");
    cout << "                                                                                                  ~~  __   |~~~~~|" << endl;
    cout << "                                                                                                  Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                                                                                 {||||CU|,|____|" << endl;
    cout << "                                                                                                //oo---OO=OO     OOO     OOO  **************";
    Sleep(85);
    system("CLS");
    cout << "                                                                                            ~__   |~~~~|" << endl;
    cout << "                                                                                          Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                                                                         {||||CU|,|____|" << endl;
    cout << "                                                                                        //oo---OO=OO     OOO     OOO  ****************";
    Sleep(85);
    system("CLS");
    cout << "                                                                                  ~  ~__   |~~~~~|" << endl;
    cout << "                                                                                  Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                                                                 {||||CU|,|____|" << endl;
    cout << "                                                                                //oo---OO=OO     OOO     OOO  ********************";
    Sleep(85);
    system("CLS");
    cout << "                                                                          ~  ~__   |~~~~~|" << endl;
    cout << "                                                                          Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                                                         {||||CU|,|____|" << endl;
    cout << "                                                                        //oo---OO=OO     OOO     OOO  **********************";
    Sleep(85);
    system("CLS");
    cout << "                                                                  ~  ~__   |~~~~~|" << endl;
    cout << "                                                                  Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                                                 {||||CU|,|____|" << endl;
    cout << "                                                                //oo---OO=OO     OOO     OOO  ************************";
    Sleep(85);
    system("CLS");
    cout << "                                                          ~  ~__   |~~~~~|" << endl;
    cout << "                                                          Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                                         {||||CU|,|____|" << endl;
    cout << "                                                        //oo---OO=OO     OOO     OOO  ****************************";
    Sleep(85);
    system("CLS");
    cout << "                                                  ~  ~__   |~~~~~|" << endl;
    cout << "                                                  Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                                 {||||CU|,|____|" << endl;
    cout << "                                                //oo---OO=OO     OOO     OOO  ******************************";
    Sleep(85);
    system("CLS");
    cout << "                                          ~  __   |~~~~|" << endl;
    cout << "                                          Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                         {||||CU|,|____|" << endl;
    cout << "                                        //oo---OO=OO     OOO     OOO  ********************************";
    Sleep(85);
    system("CLS");
    cout << "                                  ~~  __   |~~~~~|" << endl;
    cout << "                                  Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                                 {||||CU|,|____|" << endl;
    cout << "                                //oo---OO=OO     OOO     OOO  ************************************";
    Sleep(85);
    system("CLS");
    cout << "                            ~__   |~~~~|" << endl;
    cout << "                          Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                         {||||CU|,|____|" << endl;
    cout << "                        //oo---OO=OO     OOO     OOO  **************************************";
    Sleep(85);
    system("CLS");
    cout << "                  ~  ~__   |~~~~~|" << endl;
    cout << "                  Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "                 {||||CU|,|____|" << endl;
    cout << "                //oo---OO=OO     OOO     OOO  ****************************************";
    Sleep(85);
    system("CLS");
    cout << "          ~  ~__   |~~~~~|" << endl;
    cout << "          Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << "         {||||CU|,|____|" << endl;
    cout << "        //oo---OO=OO     OOO     OOO  ********************************************";
    Sleep(85);
    system("CLS");
    cout << "  ~  __   |~~~~|" << endl;
    cout << "  Y_,_|[]|   | PLEASE WAIT!|" << endl;
    cout << " {||||CU|,|____|" << endl;
    cout << "//oo---OO=OO     OOO     OOO  **********************************************";
    Sleep(85);
    system("CLS");
}

void chart(int tnum, char bp1[100], char dest1[100], char day2[20], int nd, int nm, int ny)
{
    Reservation b;
    Cancellation c;
    fstream fr, fc;
    fstream f1, f2, f3;

    int m = nd + 1; //m=monday
    int t = nd - 1; //t=tuesday

    fr.open("res_details.txt", ios::in | ios::out | ios::binary);
    fc.open("can_details.txt", ios::in | ios::out | ios::binary);

    //Reading reservation details file
    while (fr.read((char *)&b, sizeof(b)))
    {
        //if same date found, then go further
        if (b.tno == tnum && b.d == nd || b.d == m && strcmp(day2, "Monday") == 0 && b.m == nm && b.y == ny)
        {
            flag = 1;

            //Reading ticket cancellation file
            while (fc.read((char *)&c, sizeof(c)))
            {
                //If pnr found cancelled then exit
                if (b.pnr == c.c_pnr)
                {
                    flag = 0;
                }
            }

            if (flag == 1)
            {
                //For AC 1A class
                if (b.clas == '1')
                {

                    f1.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                    f1.write((char *)&b.fc1, sizeof(b.fc1));
                    f1.close();
                }

                //For AC 2A class
                if (b.clas == '2')
                {
                    f2.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                    f2.write((char *)&b.sc1, sizeof(b.sc1));
                    f2.close();
                }

                //For SL class
                if (b.clas == '3')
                {
                    f3.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                    f3.write((char *)&b.slc1, sizeof(b.slc1));
                    f3.close();
                }
            }
        }

        else if (b.tno == tnum && b.d == nd || b.d == t && strcmp(day2, "Tuesday") == 0 && b.m == nm && b.y == ny)
        {
            flag = 1;
            //Reading ticket cancellation file
            while (fc.read((char *)&c, sizeof(c)))
            {
                //If pnr found cancelled then exit
                if (b.pnr == c.c_pnr)
                {
                    flag = 0;
                }
            }

            if (flag == 1)
            {
                //For AC 1A class
                if (b.clas == '1')
                {

                    f1.open("available_fc1.txt", ios::out | ios::binary | ios::trunc);
                    f1.write((char *)&b.fc1, sizeof(b.fc1));
                    f1.close();
                }

                //For AC 2A class
                if (b.clas == '2')
                {
                    f2.open("available_sc1.txt", ios::out | ios::binary | ios::trunc);
                    f2.write((char *)&b.sc1, sizeof(b.sc1));
                    f2.close();
                }

                //For SL class
                if (b.clas == '3')
                {
                    f3.open("available_slc1.txt", ios::out | ios::binary | ios::trunc);
                    f3.write((char *)&b.slc1, sizeof(b.slc1));
                    f3.close();
                }
            }
        }
    }
    fr.close();
    fc.close();
}
