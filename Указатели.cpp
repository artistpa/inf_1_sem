#include <iostream>
#include <cmath>
using namespace std;
int main()
{unsigned long long n;
 cin >> n;
 n = n * 1024* 1024;
 int c = log2(n);
 c = (c - 1)/ 8 + 1;
 cout << c;
}
