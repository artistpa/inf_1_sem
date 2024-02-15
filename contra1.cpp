#include <iostream>
using std::cout;
using std::cin;
using std::endl;
int** create(unsigned int n, unsigned int m)
{
    int **a = new int*[n];
    for (unsigned int i = 0; i < n; i++)
        a[i] = new int[m];
    return a;
}
void destroy(int** a, unsigned int n)
{
    for (unsigned int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
}
void print(int **a, unsigned int n, unsigned int m)
{
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
}
int** create_compact(int **a, unsigned int n, unsigned int m){
    if (n % 2 != 0) {
        int **c = create(n+1, m+1);
        for (unsigned int i = 0; i < n; i++){
            for (unsigned int j = 0; j < m; j++){
                c[i][j] = a[i][j];
            }
        }
         for (unsigned int i = 0; i < n; i++){
            c[i][m] = 0;
            c[n][i] = 0;
         }
        int **b = new int*[(n + 1) / 2];
        for (unsigned int i = 0; i < ((n + 1) / 2); i++)
            b[i] = new int[(m + 1) / 2];
        int k = 0, l = 0;
        for (unsigned int i = 0; i < ((n + 1) / 2); i++){
            for (unsigned int j = 0; j < ((m + 1) / 2); j++){
                b[i][j] = c[k][l] + c[k][l + 1] + c[k + 1][l] + c[k + 1][l + 1];
                l += 2;
            }
            k += 2;
            l = 0;
    }
    destroy (c, n + 1);
    return b;
    }
    else{
    int **b = new int*[n / 2 + n % 2];
    for (unsigned int i = 0; i < (n / 2 + n % 2); i++)
        b[i] = new int[m / 2 + m % 2];
    int k = 0, l = 0;
    for (unsigned int i = 0; i < (n / 2 + n % 2); i++){
        for (unsigned int j = 0; j < (m / 2 + m % 2); j++){
            b[i][j] = a[k][l] + a[k][l + 1] + a[k + 1][l] + a[k+1][l+1];
            l += 2;
    }
            k += 2;
            l = 0;
    }
    return b;
    }
}
void print_compact(int **compact, unsigned int n, unsigned int m){
    print(compact,(n / 2 + n % 2), (m / 2 + m % 2));
}
void destroy_compact(int** compact, unsigned int n){
    for (unsigned int i = 0; i < (n / 2 + n % 2); i++)
        delete[] compact[i];
    delete[] compact;
}

int main()
{
    unsigned int n, m;
    cin >> n >> m;
    int **a = create(n, m);
    for (unsigned int i = 0; i < n; i++)
        for (unsigned int j = 0; j < m; j++)
            cin >> a[i][j];
    int** b = create_compact(a, n, m);
    print(a, n, m);
    print_compact(b, n, m);
    destroy(a, n);
    destroy_compact(b, n);
    return 0;
}
