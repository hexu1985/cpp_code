
// 一个类哪怕只定义了一个构造函数，编译器也不会再生成默认构造函数。
struct Simple_class {
	int m_val;
	Simple_class(int val): m_val(val) {}
};

int main()
{
	Simple_class a;
	a.m_val = 2;
	Simple_class b(a);
	return 0;
}
