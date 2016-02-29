thread1.cpp在g++ 5.2.0上编译报错(但在clang++ 3.7)
In file included from /usr/include/c++/5.2.0/thread:39:0,
                 from thread1.cpp:4:
/usr/include/c++/5.2.0/functional: In instantiation of ‘struct std::_Bind_simple<std::_Mem_fn<void (C::*)(int)>(std::reference_wrapper<C>, int)>’:
/usr/include/c++/5.2.0/thread:137:59:   required from ‘std::thread::thread(_Callable&&, _Args&& ...) [with _Callable = void (C::*)(int); _Args = {std::reference_wrapper<C>, int}]’
thread1.cpp:34:73:   required from here
/usr/include/c++/5.2.0/functional:1505:61: 错误：no type named ‘type’ in ‘class std::result_of<std::_Mem_fn<void (C::*)(int)>(std::reference_wrapper<C>, int)>’
       typedef typename result_of<_Callable(_Args...)>::type result_type;
                                                             ^
/usr/include/c++/5.2.0/functional:1526:9: 错误：no type named ‘type’ in ‘class std::result_of<std::_Mem_fn<void (C::*)(int)>(std::reference_wrapper<C>, int)’
         _M_invoke(_Index_tuple<_Indices...>)
         ^
Makefile:19: recipe for target 'thread1' failed
