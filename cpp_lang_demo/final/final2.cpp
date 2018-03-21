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
    void print(const char *name) {
        cout << "hello " << name << "!\n";
    }
};

int main() {
    Base b;
    Derived d;
    b.print();
    d.print("test");

    return 0;
}
