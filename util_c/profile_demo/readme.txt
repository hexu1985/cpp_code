手动命令
1)gcc -pg test.c -o test
2)test
3)gprof test > test.out

Makefile方式
make and make test	生成可执行程序
make clear			清除所有生成目标文件和时间分析输出
make execute		运行生成的可执行程序
make profile		建立时间分析输出
