#include <iostream>
#include <memory>

using namespace std;

struct hello {
    void operator ()(void *) {
        cout << "Hello world!\n";
    }
};

int main(int argc, char *argv[])
{
    shared_ptr<int> a(0, hello());
    return 0;
}

