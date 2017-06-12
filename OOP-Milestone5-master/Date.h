// compilation safegaurds
#ifndef H_DATE_H
#define H_DATE_H

#include <iostream>

#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define	MON_ERROR 3
#define DAY_ERROR 4
#define HOUR_ERROR 5
#define MIN_ERROR 6




// ict namespace 
namespace ict {
   // Date defined Error values
	




   class Date {
   private:
      // member variables
	   int m_year;
	   int m_mon;
	   int m_day;
	   int m_hour;
	   int m_min;
	   int m_readErrorCode;
	   bool m_dateOnly;

     // private methods
      int value()const;


   public:
      // constructors
	   Date();
	   Date(int, int, int);
	   Date(int year, int mon, int day, int hour , int min = 0);

      void set();
      // operator ovrloads
	  bool operator==(const Date& D)const;
	  bool operator!=(const Date& D)const;
	  bool operator<(const Date& D)const;
	  bool operator>(const Date& D)const;
	  bool operator<=(const Date& D)const;
	  bool operator>=(const Date& D)const;
	  
      // methods

	  int errCode()const;
	  bool bad()const;
	  bool dateOnly()const;
	  void dateOnly(bool value);
      int mdays()const;
	 
	  void errCode(int errorCode);
	  void set(int year, int mon, int day, int hour, int min = 0);
      // istream  and ostream read and write methods
	  std::istream& read(std::istream& is );
	  std::ostream& write(std::ostream& ostr)const;

   };
   // operator<< and >> overload prototypes for cout and cin
   std::ostream& operator<<(std::ostream& os, const Date& s);
   std::istream& operator>>(std::istream& is, Date& s);
}

#endif