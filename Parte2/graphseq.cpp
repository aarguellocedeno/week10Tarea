#include <iostream>
using namespace std;

double F(double x) {
    //calcular potencias 
    double p1 = x;    
    double p2 = p1 * p1;  
    double p4 = p2 * p2;       
    double p8 = p4 * p4;       
    double p16 = p8 * p8;      
    double p32 = p16 * p16;   

    // suma en árbol
    double s1 = p32 + p16;    
    double s2 = p8 + p4;
    double s3 = p2 + p1;

    double t1 = s1 + s2;
    double result = t1 + s3;

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
