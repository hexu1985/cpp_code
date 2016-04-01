#include <unordered_map>
#include <iostream>

enum class Color {
	red,
	yellow,
	blue,
	green,
	white,
	black,
};

#define ADD_QUOTATION(x)  #x
#define	MAKE_PAIR(x)	{x, ADD_QUOTATION(x)}

int main(int argc, char *argv[])
{
	auto hash_func = [](Color c) -> size_t {
		return std::hash<int>()(static_cast<int>(c));
	};

	typedef std::unordered_map<Color, const char *, decltype(hash_func)> Color2NameMap;
	static const Color2NameMap color2name_map({{Color::red, "red"}, {Color::green, "green"}}, 100, hash_func);
	for (auto &i : color2name_map) {
		std::cout << static_cast<int>(i.first) << ": " << i.second << std::endl;
	}

	Color2NameMap color2name_map2({{Color::red, ADD_QUOTATION(red)}, {Color::green, ADD_QUOTATION(green)}}, 100, hash_func);
	for (auto &i : color2name_map2) {
		std::cout << static_cast<int>(i.first) << ": " << i.second << std::endl;
	}

	Color2NameMap color2name_map3({MAKE_PAIR(Color::red), MAKE_PAIR(Color::green)}, 100, hash_func);
	for (auto &i : color2name_map3) {
		std::cout << static_cast<int>(i.first) << ": " << i.second << std::endl;
	}
}
