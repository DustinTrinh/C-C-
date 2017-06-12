// compilation safegaurds
#ifndef H_ERROR_H
#define H_ERROR_H
#include <string.h>
#include <iostream>
namespace ict {
   class Error {
      char* m_message;
   public:
   // constructors
	   Error();
	   Error(const char* errorMessage);
   // destructor

   // deleted constructor and operator=
	   Error(const Error& em) = delete;
	   Error& operator=(const Error& em) = delete;
   // operator= for c-style strings
	   void operator=(const char* errorMessage);
   // methods
	   virtual ~Error();
	   void clear();
	   bool isClear()const;
	   void message(const char* value);
   // cast overloads
	   operator const char*() const;
	   operator bool()const;
	   
   };
   // operator << overload prototype for cout
   std::ostream & operator<<(std::ostream & os, const Error & error);
}
#endif

