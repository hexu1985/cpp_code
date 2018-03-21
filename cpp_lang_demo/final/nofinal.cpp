#include <iostream>

using namespace std;

class Base {
public:
    void print() {
        cout << "hello Base!\n";
    }
};

class Derived: public Base {
public:
    void print() {
        cout << "hello Derived!\n";
    }

    void print(const char *name) {
        cout << "hello " << name << "!\n";
    }
};

int main() {
    Base b;
    Derived d;
    b.print();
    d.print();
    d.print("test");

    return 0;
}
