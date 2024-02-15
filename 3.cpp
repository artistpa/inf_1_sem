#include <iostream>
using namespace std;

struct Matrix
{
    int** data;
    int n, m;
};

void init(Matrix *matrix){
    int **a = new int*[matrix->n];
    for (int i = 0; i < matrix->n; i++)
        a[i] = new int[matrix->m];
    matrix->data = a;
}
void clean(Matrix *matrix){
    for (int i = 0; i < matrix->n; i++)
        delete[] matrix->data[i];
    delete[] matrix->data;
}
void expand(Matrix* matrix, int n_minus, int n_plus, int m_minus, int m_plus){
    int k = matrix->n + n_minus + n_plus, l = matrix->m + m_minus + m_plus;
    int **a = new int*[k];
    for (int i = 0; i < k; i++)
        a[i] = new int[l];
    for (int i = 0; i < k; i++){
        for (int j = 0; j < l; j++){
            if (i >= n_minus and i < k - n_plus and j >= m_minus and j < l - m_plus){
                a[i][j] = matrix->data[i-2][j-2];
            } else{a[i][j] = 0;}
        }
    }
    for (int i = 0; i < matrix->n; i++)
        delete[] matrix->data[i];
    delete[] matrix->data;
    matrix->data = a;
    matrix->n = k;
    matrix->m = l;
}

int main()
{
    Matrix matrix;
    cin >> matrix.n >> matrix.m;
    init(&matrix);
    for (int i = 0; i < matrix.n; i++)
        for (int j = 0; j < matrix.m; j++)
            cin >> matrix.data[i][j];

    int n_minus, n_plus, m_minus, m_plus;
    cin >> n_minus >> n_plus >> m_minus >> m_plus;

    expand(&matrix, n_minus, n_plus, m_minus, m_plus);

    for (int i = 0; i < matrix.n; i++)
    {
        for (int j = 0; j < matrix.m; j++)
            cout << matrix.data[i][j];
        cout << endl;
    }

    clean(&matrix);
    return 0;
}
