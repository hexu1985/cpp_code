// custom error_category example
#include <iostream>       // std::cout, std::endl
#include <string>         // std::string
#include "system_error.h"   // std::is_error_condition_enum, std::error_category,
                          // std::error_condition, std::error_code

// custom error conditions enum type:
#if __cplusplus >= 201103L
enum class custom_errc { success=0, client_error, server_error, other };
#else
namespace custom_errc {
enum custom_errc_t { success=0, client_error, server_error, other };
}	// namespace custom_errc
#endif

#if __cplusplus >= 201103L
namespace Hx {
template<> struct is_error_condition_enum<custom_errc>: public std::true_type {};
}	// namespace Hx
#else
namespace Hx {
template<> struct is_error_condition_enum<custom_errc::custom_errc_t>
{ static const bool value = true; };
}	// namespace Hx
#endif

// custom category:
class custom_category_t : public Hx::error_category {
public:
  virtual const char* name() const throw() { return "custom"; }
  virtual Hx::error_condition default_error_condition (int ev) const throw() 
  {
    if ((ev>=200)&&(ev<300)) return Hx::error_condition(custom_errc::success);
    else if ((ev>=400)&&(ev<500)) return Hx::error_condition(custom_errc::client_error);
    else if ((ev>=500)&&(ev<600)) return Hx::error_condition(custom_errc::server_error);
    else return Hx::error_condition(custom_errc::other);
  }
  virtual bool equivalent (const Hx::error_code& code, int condition) const throw() 
  {
    return *this==code.category() &&
           static_cast<int>(default_error_condition(code.value()).value())==condition;
  }
  virtual std::string message(int ev) const {
    switch (ev) {
      case 200: return "OK";
      case 403: return "403 Forbidden";
      case 404: return "404 Not Found";
      case 500: return "500 Internal Server Error";
      case 503: return "503 Service Unavailable";
      default: return "Unknown error";
    }
  }
} custom_category;

// make_error_code overload to generate custom conditions:
#if __cplusplus >= 201103L
Hx::error_condition make_error_condition (custom_errc e) {
    return Hx::error_condition(static_cast<int>(e), custom_category);
}
#else
namespace custom_errc {
Hx::error_condition make_error_condition (custom_errc_t e) {
    return Hx::error_condition(static_cast<int>(e), custom_category);
}
}	// namespace custom_errc
#endif

int main()
{
  // let's generate a 404:
  Hx::error_code e (404, custom_category);

  if (e == custom_errc::success) std::cout << "Success: " << e.message();
  else if (e == custom_errc::client_error) std::cout << "Client Error: " << e.message();
  else if (e == custom_errc::server_error) std::cout << "Server Error: " << e.message();
  else std::cout << "Unknown";
  std::cout << std::endl;

  return 0;
}


/*
Output:

Client Error: 404 Not Found
*/
