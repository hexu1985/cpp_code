// list::sort
#include <iostream>
#include "list.h"
#include <string>
#include <cctype>

// comparison, not case sensitive.
bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

int main ()
{
  Dlist<std::string> mylist;
  Dlist<std::string>::node_type *it;
  mylist.insert_tail (new Dlist<std::string>::node_type("one"));
  mylist.insert_tail (new Dlist<std::string>::node_type("two"));
  mylist.insert_tail (new Dlist<std::string>::node_type("Three"));

  mylist.sort();

  std::cout << "mylist contains:";
  for (it=mylist.head(); it!=mylist.nil(); it = dlist_next(it))
    std::cout << ' ' << it->key;
  std::cout << '\n';

  mylist.sort(compare_nocase);

  std::cout << "mylist contains:";
  for (it=mylist.head(); it!=mylist.nil(); it = dlist_next(it))
    std::cout << ' ' << it->key;
  std::cout << '\n';

  return 0;
}
