// unordered_map::rehash
#include <iostream>
#include <string>
#include "unordered_map.h"
#include "functional.h"

struct my_hash {
	size_t operator ()(const std::string &str)
	{
		return hash_c_str(str.c_str());
	}
};


int main ()
{
  typedef Hx::unordered_map<std::string,std::string,my_hash> mymap_t;
  mymap_t mymap;

  mymap.rehash(20);

  mymap["house"] = "maison";
  mymap["apple"] = "pomme";
  mymap["tree"] = "arbre";
  mymap["book"] = "livre";
  mymap["door"] = "porte";
  mymap["grapefruit"] = "pamplemousse";

  std::cout << "current bucket_count: " << mymap.bucket_count() << std::endl;

  unsigned n = mymap.bucket_count();

  for (unsigned i=0; i<n; ++i) {
    std::cout << "bucket #" << i << " contains: ";
    for (mymap_t::local_iterator it = mymap.begin(i); it!=mymap.end(i); ++it)
      std::cout << "[" << it->first << ":" << it->second << "] ";
    std::cout << "\n";
  }

  return 0;
}
 

/*
Possible output:


current bucket_count: 23
*/ 


