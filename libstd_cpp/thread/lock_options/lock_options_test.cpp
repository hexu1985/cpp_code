#include <iostream>
#include "mutex.h"
#include "thread.h"
 
struct bank_account {
    explicit bank_account(int balance) : balance(balance) {}
    int balance;
    Hx::mutex m;
};
 
void transfer(bank_account &from, bank_account &to, int amount)
{
    // attempt to lock both mutexes without deadlock
    Hx::lock(from.m, to.m);
 
    // make sure both already-locked mutexes are unlocked when 
    // we're done; if we just used the lock_guard without std::lock
    // and std::adopt_lock, we might deadlock with other calls to transfer
    Hx::lock_guard<Hx::mutex> lock1(from.m, Hx::adopt_lock);
    Hx::lock_guard<Hx::mutex> lock2(to.m, Hx::adopt_lock);
 
    from.balance -= amount;
    to.balance += amount;
}
 
int main()
{
    bank_account my_account(100);
    bank_account your_account(50);

#if __cplusplus >= 201103L
    Hx::thread t1(transfer, std::ref(my_account), std::ref(your_account), 10);
    Hx::thread t2(transfer, std::ref(your_account), std::ref(my_account), 5);
#else
    Hx::thread t1(transfer, std::tr1::ref(my_account), std::tr1::ref(your_account), 10);
    Hx::thread t2(transfer, std::tr1::ref(your_account), std::tr1::ref(my_account), 5);
#endif
 
    t1.join();
    t2.join();

    std::cout << "my_account: " << my_account.balance << "\n";
    std::cout << "your_account: " << your_account.balance << "\n";
 
    return 0;
}

/*
Output:
my_account: 95
your_account: 55
*/ 


