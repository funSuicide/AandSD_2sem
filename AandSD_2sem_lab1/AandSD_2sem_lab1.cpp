#include <iostream>
#include <conio.h>
#include "Map.h"
#include <chrono>
#include <fstream>

using namespace std;

void TestTime(Map& m) {
    ofstream fout;
    fout.open("data.txt", ios_base::app);
    for (int j = 0; j < 10; ++j) {
        auto begin = std::chrono::steady_clock::now();
        for (int i = 0; i < 1000000; ++i) {
            m.Insert(j * 1000000 + i, "-");
        }
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        fout << duration.count() << endl;
    }
    fout.close();
}

int GetKey()
{
    int Key = _getch();
    if ((Key == 0) || (Key == 224)) Key = _getch();
    return Key;
}

void menu(Map& m) {

    int key;
    string data;
    int Repeat = 1;
    cout << "[0]: Insert element\n[1]: Erase element\n[2]: Find element\n[3]: Exit\n" << "\n";
    cout << "Your map: " << "\n";
    m.Print();
    while (Repeat != 0)
    {
        int k = GetKey();
        switch (k)
        {
        case 48:
            system("cls");
            {
                cout << "Enter the key:";
                cin >> key;
                cout << "Enter the data:";
                cin >> data;
                try {
                    m.Insert(key, data);
                }
                catch (const char* err)
                {
                    cerr << err;
                }
                menu(m);
            }
            break;
        case 49:
            system("cls");
            cout << "Enter the key:";
            cin >> key;
            try {
                m.Erase(key);
            }
            catch (const char* err)
            {
                cout << err;
                break;
            }
            menu(m);
            break;
        case 50:
            system("cls");
            cout << "Enter the key:";
            cin >> key;
            try {
                cout << "Data with this key:" << m.FindElement(key) << "\n";
            }
            catch (const char* err)
            {
                std::cout << err;
                break;
            }
            menu(m);
            break;
        case 51:
            system("cls");
            m.~Map();
            cout << "Thank you! ^_^" << "\n";
            exit(0);
            break;
        default: cout << "Select [0-4]" << "\n";
        }
    }
}

int main(){
    Map m;
    cout << "Hello, user!^_^" << "\n";
    //menu(m);
    TestTime(m);
    cout << "Vse";
    return 0;
}

