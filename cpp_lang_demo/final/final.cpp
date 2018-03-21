#include <iostream>

using namespace std;

class Base {
public:
    virtual void print() final {
        cout << "hello Base!\n";
    }
};

class Derived: public Base {
public:
    void print() {
        cout << "hello Derived!\n";
    }
};

int main() {
    Base b;
    Derived d;
    b.print();
    d.print();

    return 0;
}
