#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits> // for numeric_limits
using namespace std;

class BankAccount {
private:
    int accNo;
    char name[25];
    char Fname[25];
    char cnic[25];
    char P_no[25];
    char email[25];
    float amount;
    int search;

public:
    BankAccount() : accNo(0), amount(0), search(0) {} 
    void createAccount();
    void depositAmount();
    void withdrawAmount();
    void checkInfo();
};

void BankAccount::createAccount() {
    srand(time(0));
    accNo = rand() * rand() + rand() * rand();
    
    cout << "Enter Your name :: ";
    cin.ignore(); // ignore any leftover newline characters
    cin.getline(name, 25);
    
    cout << "Enter Your Father name :: ";
    cin.getline(Fname, 25);

    cout << "Enter Your CNIC :: ";
    cin.getline(cnic, 25);
    
    cout << "Enter Your phone no. :: ";
    cin.getline(P_no, 25);
    
    cout << "Enter Your email :: ";
    cin.getline(email, 25);
    
    cout << "Enter initial amount :: ";
    cin >> amount;

    ofstream outFile("data.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file." << endl;
        return;
    }
    outFile << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << endl;
    outFile.close();

    cout << endl << accNo << " This is your account number. Please save it." << endl << endl;
}

void BankAccount::depositAmount() {
    int depositAmount;
    cout << "Enter amount to deposit :: ";
    cin >> depositAmount;
    if (depositAmount <= 0) {
        cout << "Invalid amount. Deposit amount should be greater than zero." << endl;
        return;
    }

    ifstream inFile("data.txt");
    if (!inFile) {
        cerr << "Error opening file." << endl;
        return;
    }
    ofstream outFile("data1.txt");
    if (!outFile) {
        cerr << "Error opening file." << endl;
        inFile.close();
        return;
    }

    bool found = false;
    while (inFile >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount) {
        if (accNo == search) {
            found = true;
            cout << "\nCurrent amount :: " << amount;
            amount += depositAmount;
            cout << "\nUpdated amount :: " << amount << endl;
        }
        outFile << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << endl;
    }

    inFile.close();
    outFile.close();

    if (!found) {
        cout << "Account number not found." << endl;
        remove("data1.txt");
    } else {
        remove("data.txt");
        rename("data1.txt", "data.txt");
    }
}

void BankAccount::withdrawAmount() {
    int withdrawAmount;
    cout << "Enter amount to withdraw :: ";
    cin >> withdrawAmount;
    if (withdrawAmount <= 0) {
        cout << "Invalid amount. Withdrawal amount should be greater than zero." << endl;
        return;
    }

    ifstream inFile("data.txt");
    if (!inFile) {
        cerr << "Error opening file." << endl;
        return;
    }
    ofstream outFile("data1.txt");
    if (!outFile) {
        cerr << "Error opening file." << endl;
        inFile.close();
        return;
    }

    bool found = false;
    while (inFile >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount) {
        if (accNo == search) {
            found = true;
            cout << "\nCurrent amount :: " << amount;
            if (withdrawAmount > amount) {
                cout << "\nInsufficient balance. Withdrawal amount exceeds current balance." << endl;
            } else {
                amount -= withdrawAmount;
                cout << "\nUpdated amount :: " << amount << endl;
            }
        }
        outFile << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << endl;
    }

    inFile.close();
    outFile.close();

    if (!found) {
        cout << "Account number not found." << endl;
        remove("data1.txt");
    } else {
        remove("data.txt");
        rename("data1.txt", "data.txt");
    }
}

void BankAccount::checkInfo() {
    ifstream inFile("data.txt");
    if (!inFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    bool found = false;
    while (inFile >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount) {
        if (accNo == search) {
            found = true;
            cout << "\n---------------------------\n";
            cout << "Account Number     :: " << accNo << endl;
            cout << "User Name          :: " << name << endl;
            cout << "Father Name        :: " << Fname << endl;
            cout << "CNIC               :: " << cnic << endl;
            cout << "Phone Number       :: " << P_no << endl;
            cout << "Email              :: " << email << endl;
            cout << "Current amount     :: " << amount << endl;
            cout << "---------------------------\n" << endl;
        }
    }

    inFile.close();

    if (!found) {
        cout << "Account number not found." << endl;
    }
}

int main() {
    char choice;
    int search;
    BankAccount obj;

    while (true) {
        cout << "\n\n\n\t\t......::: Shivam's Bank :::......";
        cout << "\n\t\t:: press 1 to Login  Account     :: ";
        cout << "\n\t\t:: press 2 to Create Account     ::";
        cout << "\n\t\t:: press 0 to Exit               ::";
        cout << "\n\t\t:: ............................. ::\n\t\t\t\t";
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "Enter your account no :: ";
            cin >> search;
            while (true) {
                cout << "\n\n\n\t\t.......::: Shivam's Bank :::.......";
                cout << "\n\t\t:: press 1 to Deposit  Amount    :: ";
                cout << "\n\t\t:: press 2 to Withdraw Amount    ::";
                cout << "\n\t\t:: press 3 to Check    Info      ::";
                cout << "\n\t\t:: press 0 to Exit     Menu      ::";
                cout << "\n\t\t:: ............................. ::\n\t\t\t\t";
                cin >> choice;

                switch (choice) {
                case '1':
                    obj.depositAmount();
                    break;
                case '2':
                    obj.withdrawAmount();
                    break;
                case '3':
                    obj.checkInfo();
                    break;
                case '0':
                    return 0;
                default:
                    cout << "Invalid Choice...!";
                    break;
                }
            }
            break;
        case '2':
            obj.createAccount();
            break;
        case '0':
            exit(0);
        default:
            cout << "\n Invalid choice...! ";
            break;
        }
    }

    return 0;
}
