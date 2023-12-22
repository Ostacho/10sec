#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <ctime>
#include <Windows.h>

using namespace std;
const double y = 0.47 * 15;
const double z = 1.32 * 15;
double euler_num = 2.71828;
const int N = 6;
int ch[N], f_chi[N], new_ch[N] = { 0 };
double V_chi[N];
string chz[N], new_chz[N];

int calculateF(int x) {
    return pow(3 * x + pow(sin(pow(abs(x + z), 1.0 / 3) / (2 * x + 1.34)), 2), 2) - y * pow(pow(euler_num, x), 2 - z);
}

string ConvToBin(int a, int size) {
    string binary = "";
    int mask = 1;
    for (int i = 0; i < size; i++) {
        binary = ((mask & a) >= 1 ? "1" : "0") + binary;
        mask <<= 1;
    }
    return binary;
}

int ConvToDecimal(string binaryString) {
    int dec = 0, idx = 0;
    for (int i = binaryString.length() - 1; i >= 0; i--) {
        dec += (binaryString[i] == '1' ? pow(2, idx) : 0);
        idx++;
    }
    return dec;
}

void Selection(int n) {
    int S1 = 0;
    cout << "Поточна популяція: ";
    for (int i = 0; i < n; i++)
        cout << ch[i] << " ";
    cout << "\nДвійкове представлення поточної популяції: ";
    for (int i = 0; i < n; i++)
        cout << chz[i] << " ";

    for (int i = 0; i < n; i++)
        new_ch[i] = 0;
    int ch_rand;
    cout << "\nПристосованість особин поточної популяції: ";
    for (int i = 0; i < n; i++) {
        cout << f_chi[i] << " ";
        S1 += f_chi[i];
    }
    cout << "\n Ймовірність пристосованості= ";

    for (int i = 0; i < n; i++) {
        V_chi[i] = (double)f_chi[i] * 100.0 / S1;
        cout << V_chi[i] << " ";
    }
    cout << "\n SNew= " << S1;
    cout << "\n" << "Відібрані особи (Метод Монте-Карло): ";

    for (int i = 0; i < n; i++) {
        ch_rand = rand() * 100 / RAND_MAX;
        cout << ch_rand << " ";

        if (ch_rand < V_chi[0]) new_ch[i] = ch[0];
        else if (ch_rand < V_chi[0] + V_chi[1]) new_ch[i] = ch[1];
        else if (ch_rand < V_chi[0] + V_chi[1] + V_chi[2]) new_ch[i] = ch[2];
        else if (ch_rand < V_chi[0] + V_chi[1] + V_chi[2] + V_chi[3]) new_ch[i] = ch[3];
        else if (ch_rand < V_chi[0] + V_chi[1] + V_chi[2] + V_chi[3] + V_chi[4]) new_ch[i] = ch[4];
        else if (ch_rand < V_chi[0] + V_chi[1] + V_chi[2] + V_chi[3] + V_chi[4] + V_chi[5]) new_ch[i] = ch[5];
    }

    cout << "\nВідібрана популяція: ";
    for (int i = 0; i < n; i++) {
        cout << " " << new_ch[i] << " ";
        chz[i] = ConvToBin(new_ch[i], 10);
    }

    cout << " \nДвійкове представлення: ";
    for (int i = 0; i < n; i++)
        cout << " " << chz[i] << " ";
    cout << "\n";
}

void new_children(string f1, string f2, int pntCross, int childr1, int childr2) {
    string p11, p12, p21, p22;
    cout << f1 << " " << f2 << " точка схрещування: " << pntCross << endl;
    p11 = f1.substr(0, pntCross);
    p12 = f1.substr(pntCross);
    p21 = f2.substr(0, pntCross);
    p22 = f2.substr(pntCross);
    cout << " p11 = " << p11 << " p12 = " << p22 << "\n";
    cout << " p21 = " << p21 << " p22 = " << p22 << "\n";
    new_chz[childr1] = p11 + p22;
    new_chz[childr2] = p21 + p12;
}

void Crossing(int n) {
    int childr1, childr2;
    int npair[N]{ 0 }, point_cross[3];
    int kp = 1;
    cout << "Розподіл за парами: ";
    vector<int> v1;
    for (unsigned int iter = 0; iter < N; ++iter)
        v1.push_back(iter);
    random_shuffle(v1.begin(), v1.end());

    int p = 0;

    for (vector<int>::iterator iter = v1.begin(); iter < v1.end(); ++iter) {
        npair[p] = *iter;
        p++;
    }
    for (int p = 0; p < n; p++)
        cout << npair[p] << " ";
    cout << "\n";
    cout << "точки схещування за парами: ";
    for (int i = 0; i < 3; i++) {
        point_cross[i] = (int)(rand() % 9) + 1;
        cout << point_cross[i] << " ";
    }
    cout << "перша пара: ";
    childr1 = 0;
    childr2 = 1;
    new_children(chz[npair[0]], chz[npair[1]], point_cross[0], 0, 1);
    cout << "потомки: " << new_chz[childr1] << " " << new_chz[childr2];

    cout << "\nдруга пара";
    childr1 = 2;
    childr2 = 3;
    new_children(chz[npair[2]], chz[npair[3]], point_cross[1], 2, 3);
    cout << "потомки: " << new_chz[childr1] << " " << new_chz[childr2];

    cout << "\nтретя пара";
    childr1 = 4;
    childr2 = 5;
    new_children(chz[npair[4]], chz[npair[5]], point_cross[2], 4, 5);
    cout << "потомки: " << new_chz[childr1] << " " << new_chz[childr2];

    cout << "\nнова популяція: ";
    for (int i = 0; i < N; i++)
        chz[i] + new_chz[i];

    for (int i = 0; i < N; i++) {
        ch[i] = ConvToDecimal(chz[i]);
        cout << ch[i] << " ";
    }
    cout << "\n\n";
}

int main() {
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    int MKI = 100;
    int max = 1024;
    int S = 0, SNew = 0;
    bool found = false;
    int i = 1;

    cout << "Стартова популяція: ";
    for (int i = 0; i < N; i++) {
        ch[i] = rand() * max / RAND_MAX;
        chz[i] = ConvToBin(ch[i], 10);
    }

    for (int i = 0; i < N; i++)
        cout << ch[i] << " ";
    cout << "\n\n";

    for (int i = 0; i < N; i++) {
        f_chi[i] = calculateF(ch[i]);
        SNew += f_chi[i];
    }

    while (!found) {
        cout << "* Крок " << i << " *\n";
        if ((i > MKI) || (S == SNew)) {
            cout << "* Кінець *" << "\n\n";
            found = true;
            break;
        }

        Selection(N);
        Crossing(N);

        S = SNew;
        SNew = 0;
        for (int i = 0; i < N; i++) {
            f_chi[i] = calculateF(ch[i]);
            SNew += f_chi[i];
        }
        i++;
    }

    return 0;
}
