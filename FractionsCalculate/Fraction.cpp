#include "Fraction.h"

using namespace std;

namespace sict{
	Fraction::Fraction() {
		denom = -1;              // safe empty state
	}

	Fraction::Fraction(int n, int d) // n: numerator, d: denominator
	{
		if (n >= 0 && d > 0) {
			num = n;
			denom = d;
			reduce();
		}
		else
			denom = -1;              // set to safe empty state
	}
	
	

    int Fraction::gcd()                                        // returns the greatest common divisor of num and denom 
    {
        int mn = min();                                        // min of num and denom
        int mx = max();                                        // mX of num and denom

        for (int x=mn ; x > 0 ; x--)                           // find the greatest common divisor
            if( mx % x == 0 &&  mn % x == 0)
                return x;
        return 1;

    } 

    void Fraction::reduce()                                         // simplify the Fraction number  
    {
        int tmp = gcd();
        num /= tmp;
        denom /= tmp;
    }

    int Fraction::max ()
    {
        return (num >= denom) ? num : denom; 
    }

    int Fraction::min()
    {
        return (num >= denom) ? denom : num; 
    }
  
    // TODO: Copy-paste the implementation of member isEmpty function from the in_lab part answer HERE
	bool Fraction::isEmpty() const
	{
		if (denom < 0 || num < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

    // TODO: Copy-paste the implementation of member display function from the in_ab part answer HERE
	void Fraction::display() const
	{

		if (isEmpty() == true)
		{

			cout << "Invalid Fraction Object!";

		}

		else
		{
			if (denom == 1)
			{
				cout << num;
			}
			else
			{
				cout << num << "/" << denom;
			}
		}
	}

    // TODO: Copy-paste the implementation of member operator+= function from the in_lab part answer HERE
	Fraction& Fraction::operator+=(Fraction &input)
	{


		int totaltop = 1;
		int totalbottom = 1;

		totaltop = num*input.denom + denom*input.num;
		totalbottom = denom * input.denom;

		num = totaltop;
		denom = totalbottom;
		reduce();
		return *this;
	}
    // TODO: Copy-paste the implementation of member operator+ function from the in_ab part answer HERE
	Fraction Fraction::operator+(Fraction &input)
	{
		Fraction fraction;
		int totaltop = 1;
		int totalbottom = 1;

		totaltop = num*input.denom + denom*input.num;
		totalbottom = denom*input.denom;

		fraction.num = totaltop;
		fraction.denom = totalbottom;
		return fraction;
	}
    // TODO: Copy-paste the implementation of member operator* function from the in_lab part answer HERE
	Fraction Fraction::operator*( Fraction input)
	{
		Fraction fraction;

		int totaltop = 1;
		int totalbottom = 1;

		totaltop = num * input.num;
		totalbottom = denom * input.denom;

		fraction.num = totaltop;
		fraction.denom = totalbottom;
		return fraction;

	}

    // TODO: write the implementation of member operator== function HERE
	bool Fraction::operator==(Fraction &input)
	{
		if (num / denom == input.num / input.denom && input.isEmpty() == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}

    // TODO: write the implementation of member operator!= function HERE
	bool Fraction::operator!=(Fraction input)
	{
		if (num == input.num && denom == input.denom)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
    // TODO: write the implementation of member operator double () function HERE
	Fraction::operator double()
	{
		float result = 0.0f;
		if (isEmpty() == false)
		{
			result = (float)num / (float)denom;
			
		}
		else
		{
			result = -1.0;
		}
		return result;
	}
    // TODO: write the implementation of member operator int () function HERE
	Fraction::operator int()
	{
		int result = 0;
		if (isEmpty() == false)
		{
			result = num / denom;
		}
		else
		{
			result = -1;
		}
		return result;
	}

}