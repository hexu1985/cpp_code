#include <iostream>

template <typename Ret, typename ...Args>
Ret decorator(Ret (*func)(Args ...args), Args ...args)
{
    try {
        Ret ret = func(args...);
        std::cout << "exec ok" << std::endl;
        return ret;
    } catch (...) {
        std::cout << "catch exception" << std::endl;
        return Ret();
    }
}

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

int main()
{
    std::cout << "decorator(&no_throw_func, 1, 2): " << decorator(&no_throw_func, 1, 2) << std::endl;
    std::cout << "decorator(&throw_func, 1, 2): " << decorator(&throw_func, 1, 2) << std::endl;
    std::cout << "decorator(&no_args_func): " << decorator(&no_args_func) << std::endl;
    
    return 0;
}
