#include <iostream>

template <typename Ret, typename = typename std::enable_if<!std::is_void<Ret>::value>::type,
    typename Class, typename ...Args>
Ret decorator(Ret (Class::*func)(Args ...args), Class *pobj, Args ...args)
{
    try {
        Ret ret = (pobj->*func)(args...);
        std::cout << "exec ok" << std::endl;
        return ret;
    } catch (...) {
        std::cout << "catch exception" << std::endl;
        return Ret();
    }
}

template <typename ...Args>
void decorator(void (Class::*func)(Args ...args), Class *pobj, Args ...args)
{
    try {
        (pobj->*func)(args...);
        std::cout << "exec ok" << std::endl;
    } catch (...) {
        std::cout << "catch exception" << std::endl;
    }
}

class Test {
public:
    int no_throw_func(int a, int b)
    {
        std::cout << __func__ << ", a: " << a << ", b: " << b << std::endl;
        return -1;
    }
    
    int throw_func(int a, int b)
    {
        std::cout << __func__ << ", a: " << a << ", b: " << b << std::endl;
        throw std::runtime_error(__func__);
        return 0;
    }
    
    int no_args_func()
    {
        std::cout << __func__ << std::endl;
        return 1;
    }

    void void_ret_func(int a, int b)
    {
        std::cout << __func__ << "a: " << a << ", b: " << b << std::endl;
    }
};

int main()
{
    Test test;
    std::cout << "decorator(&no_throw_func, 1, 2): " << decorator(&Test::no_throw_func, &test, 1, 2) << std::endl;
    std::cout << "decorator(&throw_func, 1, 2): " << decorator(&Test::throw_func, &test, 1, 2) << std::endl;
    std::cout << "decorator(&no_args_func): " << decorator(&Test::no_args_func, &test) << std::endl;
    decorator(&Test::void_ret_func, &test, 1, 2);
    
    return 0;
}
