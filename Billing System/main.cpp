#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class head {
    char lname[50][50];

public:
    int totalitems;
    float Qty[3];
    float price[3];
    int vatprice[3];
    int tprice[3];

    void input();
    void output();
};

class vat : public head {
    float vats;

public:
    void vatcal();
    void outputs(); // Corrected function name
    void sum();
};

void head::input() {
    system("CLS");
    cout << "\nEnter number of items = ";
    cin >> totalitems;
    for (int i = 0; i < totalitems; i++) {
        cout << "\nEnter name of item " << i + 1 << ":";
        cin >> lname[i];
        cout << "Enter quantity here: ";
        cin >> Qty[i];
        cout << "Enter price of item " << i + 1 << ":";
        cin >> price[i];
        tprice[i] = Qty[i] * price[i];
    }
}

void head::output() {
    int a;
    ifstream infile("COUNT.TXT");
    infile >> a;
    infile.close(); // Close file before reopening
    ofstream outfile("COUNT.TXT");
    a += 1;
    outfile << a;
    outfile.close();
    {
        ofstream outfile("HIS.TXT", ios::app);
        outfile << endl
                << "Bill No.:" << a << endl;
        outfile << "-------------------------------------------" << endl;
        cout << "\n";
        cout << "Name of item\t Quantity Price Total Price \n";
        for (int i = 0; i < totalitems; i++) {
            outfile << "Name: " << lname[i] << " Qty: " << Qty[i] << " Price:" << tprice[i] << endl;
            cout << lname[i] << "\t\t" << Qty[i] << "\t" << price[i] << "\t" << tprice[i] << '\n';
        }
        outfile << "--------------------------------------------------------" << endl;
        outfile.close();
    }
}

void vat::vatcal() {
    input();
    for (int i = 0; i < totalitems; i++) {
        if (price[i] <= 100.00) {
            vatprice[i] = tprice[i] + (0.03 * tprice[i]);
        } else {
            vatprice[i] = tprice[i] + (0.1 * tprice[i]);
        }
    }
}

void vat::outputs() { // Corrected function name
    output();

    float cash = 0, sum = 0, qty = 0, sumt = 0;

    for (int i = 0; i < totalitems; i++) {
        sumt += tprice[i];
        sum += vatprice[i];
        qty += Qty[i];
    }
    cout << "\nTotal : ";
    cout << "\n---------------------------------------------";
    cout << "\n\tQuantity = " << qty << "\t\tSum = " << sumt << "\tWith Vat : " << sum;
    cout << "\n------------------------------------------------------------------------------ ";

pay:
    cout << "\n\n\t\t\t**** PAYMENT SUMMARY ****\n";
    cout << "\t\t\tTotal cash given : ";
    cin >> cash;

    if (cash >= sum)
        cout << "\t\t\tTotal cash repaid : " << cash - sum << '\n';
    else {
        cout << "\t\t\tCash given is less than the total amount!!!";

        goto pay;
    }
}

int passwords() {
    char p1, p2, p3, p4;

    cout << "\n\n\n\n\n\n\t\t\tENTER THE PASSWORD : ";
    cin >> p1;
    cout << "*";
    cin >> p2;
    cout << "*";
    cin >> p3;
    cout << "*";
    cin >> p4;
    cout << "*";

    if ((p1 == 'j' || p1 == 'J') && (p2 == 'o' || p2 == 'O') && (p3 == 'h' || p3 == 'H') && (p4 == 'n' || p4 == 'N'))
        return 1;
    else
        return 0;
}

int main() {
    vat obj;
    char opt, ch;
    int a = 1;
    ifstream fin;

    a = passwords();
    if (!a) {
        for (int i = 0; i < 2; i++) {
            cout << "\nWrong password, try once more\n";
            if (passwords()) {
                goto last;
            } else {
                cout << "\n\n\t\t\tall attempts failed .....";
                cout << "\n\n\t\t\tsee you ..................";
                exit(0);
            }
        }
        cout << "\t\t\tSorry, all attempts failed.............\n\t\t\tInactive";
    } else {
    last:;
        do {
        start:
            system("PAUSE");
            system("CLS");
            cout << "\n\n\t\t\t------------------------------";
            cout << "\n\t\t\tBilling Management System";
            cout << "\n\t\t\t------------------------------";
            cout << "\n\n\t\t\tWhat you want to do?";
            cout << "\n\t\t\t1.\tTo enter a new entry\n\t\t\t2.\tTo view previous entries\n\t\t\t3.\tExit\n";
            cout << "\n\nEnter your option: ";
            cin >> opt;
            switch (opt) {
            case '1':
                obj.vatcal();
                obj.outputs();
                goto start;
            case '2':
                fin.open("HIS.TXT", ios::in);
                while (fin.get(ch)) {
                    cout << ch;
                }
                fin.close();
                goto start;
            case '3':
                exit(0);
            default:
                cout << "\a";
            }
        } while (opt != '3');
    }
    return 0;
}
