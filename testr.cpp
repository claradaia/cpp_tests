#include <iostream>

using namespace std;

int main() {
    int a = 5;
    int& b = a;
    cout << "a " << a << endl;
    cout << "b " << b << endl;
    a++;
    cout << "b " << b << endl;
    b++;
    cout << "a " << a << endl;

    && int c = 3;
    cout << "c " << a << endl;
    c++;
    cout << "c " << a << endl;

}
