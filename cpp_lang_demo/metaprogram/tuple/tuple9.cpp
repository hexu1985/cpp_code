#include <stdint.h>
#include <tuple>
#include <map>
#include <string>
#include <iostream>

int main()
{
	typedef std::tuple<int32_t, int64_t, int32_t> key_type;
	typedef std::map<key_type, std::string> map_type;

	map_type mymap;
	key_type key;

   	key = std::make_tuple((int32_t) 1, (int64_t) 2, (int32_t) 3);
	mymap[key] = "hello";

	key = std::make_tuple((int32_t) 4, (int64_t) 5, (int32_t) 6);
	mymap[key] = "world";

   	key = std::make_tuple((int32_t) 1, (int64_t) 2, (int32_t) 3);
	auto it = mymap.find(key);
	if (it != mymap.end())
		std::cout << "found key with value: " << it->second << std::endl;
	else
		std::cout << "not found key " << std::endl;

   	key = std::make_tuple((int32_t) 2, (int64_t) 3, (int32_t) 4);
	it = mymap.find(key);
	if (it != mymap.end())
		std::cout << "found key with value: " << it->second << std::endl;
	else
		std::cout << "not found key " << std::endl;

	return 0;
}
