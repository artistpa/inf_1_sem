#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>

double get_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::steady_clock::now().time_since_epoch()).count()/1e3;
};

using namespace std;


//ряд Лейбница
void rad1 () {
    ofstream f("1-1.csv", ios::out);
    const double PI = 3.14159265359;
    int l = 1;
    float pi=0, t=1, time_0 = get_time();
    for (int i=1; i < 300000; i+=1) {
        int k = -1;
        for (int j = 0; j < i; j++) {
            k = k * (-1);
        }
        pi += k / t;
        for (int j = l; j < 11; j++) {
            if (round(4*pi*pow(10, j))/pow(10, j) == round(PI*pow(10, j))/pow(10, j)) {
                cout << i << " " << j << " " << abs(get_time()-time_0) << " ms" << '\n';
                f << abs(get_time()-time_0) << endl;
                l ++;
                break;
            }
        }
        t += 2;
    }
    cout << '\n';
};

//формула Эйлера
void rad2 () {
    ofstream f("1-2.csv", ios::out);
    const double PI = 3.14159265359;
    int l = 1;
    float pi = 0, sum = 0, time_0 = get_time();
    for (int i=1; i< 100000; i++) {
        sum += 6 / pow (i, 2);
        pi = sqrt(sum);
        for (int j = l; j < 11; j++) {
            if (round(pi*pow(10, j))/pow(10, j) == round(PI*pow(10, j))/pow(10, j)) {
                cout << i << " " << j << " " << abs(get_time()-time_0) << " ms" << '\n';
                f << abs(get_time()-time_0) << endl;
                l ++;
                break;
            }
        }
    }
      cout << '\n';
};

void rad3 () {
    ofstream f("1-3.csv", ios::out);
    const double PI = 3.14159265359;
    int l = 1;
    double sum = 0, pi, time_0 = get_time();
    for (int i = 0; i < 100000; i++) {
        sum += (12 * (-(pow(-1,i)))) / pow(i,2);
        pi = sqrt(sum);
        cout << pi;
        for (int j = l; j < 11; j++) {
            if (round(pi*pow(10, j))/pow(10, j) == round(PI*pow(10, j))/pow(10, j)) {
                cout << i << " " << j << " " << abs(get_time()-time_0) << " ms" << '\n';
                f << abs(get_time()-time_0) << endl;
                l ++;
                break;
            }
        }
    }
      cout << '\n';
};
//Преобразование Мадхава
void rad4 () {
    ofstream f("1-4.csv", ios::out);
    const double PI = 3.14159265359;
    int l = 1;
    float pi  = 0, time_0 = get_time();
    for (int i = 0; i < 100000; i++) {
        pi += pow(-1, i)/(pow(3, i)*(2*i+1));
        for (int j = l; j < 11; j++) {
            if (round(2*sqrt(3)*pi*pow(10, j))/pow(10, j) == round(PI*pow(10, j))/pow(10, j)) {
                cout << i << " " << j << " " << abs(get_time()-time_0) << " ms" << '\n';
                f << abs(get_time()-time_0) << endl;
                l ++;
                break;
            }
        }
    }
      cout << '\n';
};

int main() {
    rad1();
    rad2();
    rad3();
    rad4();
}
