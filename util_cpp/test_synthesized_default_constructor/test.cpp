
struct Simple_class {
	int m_val;
};

int main()
{
	Simple_class a;
	a.m_val = 2;
	Simple_class b(a);
	return 0;
}
