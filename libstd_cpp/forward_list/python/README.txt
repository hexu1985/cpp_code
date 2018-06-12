1) 编译demo.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用demo.Num
$ python
>>> import demo
>>> slist = demo.slist()
>>> slist.push_front(1.0)
>>> slist.push_front(2.0)
>>> slist.push_front(3.0)
>>> slist.push_front(4.0)
>>> for x in slist:
...     print(x)
...
4.0
3.0
2.0
1.0

3) 通过脚本调用demo.Num
$ python test_demo.py
