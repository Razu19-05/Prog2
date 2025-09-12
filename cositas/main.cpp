#include <iostream>

using namespace std;

int main() {
    long long *numero;
    long long buffer[3];
    for (int i = 0; i < 3; i++) {
        cout << "Digite el numero "<<i+1<<": ";
        cin >> buffer[i];
        cout << endl;
    }
    numero = new long long[3]{};
    for (int i = 0; i < 3; i++) {
        numero[i] = buffer[i];
    }
    for (int i = 0; i < 3; i++) {
        cout << numero[i] << endl;
    }
    return 0;
}