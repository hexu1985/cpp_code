#include <iostream>
#include <boost/functional/hash.hpp>
#include <boost/lexical_cast.hpp>

class point
{
    int x;
    int y;
public:
    point() : x(0), y(0) {}
    point(int x, int y) : x(x), y(y) {}

    bool operator==(point const& other) const
    {
        return x == other.x && y == other.y;
    }

    friend std::size_t hash_value(point const& p)
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, p.x);
        boost::hash_combine(seed, p.y);

        return seed;
    }
};

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "usage: a.out x y\n";
		return 1;
	}
	
	int x = boost::lexical_cast<int>(argv[1]);
	int y = boost::lexical_cast<int>(argv[2]);

	point p(x, y);
	std::cout << hash_value(p) << std::endl;
	return 0;
}


