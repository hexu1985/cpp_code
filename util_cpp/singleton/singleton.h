#ifndef	SINGLETON_H
#define	SINGLETON_H

class Singleton
{
public:
	static Singleton &GetInstance();

	void Sleep();

private:
	Singleton();
	~Singleton();
	Singleton(const Singleton &) = delete;
	const Singleton &operator =(const Singleton &) = delete;
};

#endif
