#include <iostream>
#include <omp.h>
using namespace std;

double F(double x) {
    double p1, p2, p4, p8, p16, p32;

    // Potencias
    p1 = x;
    p2 = p1 * p1;
    p4 = p2 * p2;
    p8 = p4 * p4;
    p16 = p8 * p8;
    p32 = p16 * p16;

    //sumas en paralelo
    double s1, s2, s3;
    #pragma omp parallel sections
    {
        #pragma omp section
        { s1 = p32 + p16; }

        #pragma omp section
        { s2 = p8 + p4; }

        #pragma omp section
        { s3 = p2 + p1; }
    }

    // reducción final
    double t1, result;
    #pragma omp parallel sections
    {
        #pragma omp section
        { t1 = s1 + s2; }

        #pragma omp section
        { result = t1 + s3; }
    }

    return result;
}

int main() {
    double x;
    cout << "Introduce el valor de x: ";
    cin >> x;

    double result = F(x);
    cout << "F(x) = " << result << endl;

    return 0;
}