/******************************************************************************/
/*                       Author and Date                                      */
/*

Author: Claudius Christian 
Date: 2/12/2013 

/******************************************************************************/
/*                       Summary                                              */
/*

1) class must allow for storage of rational numbers in a mixed number format. 
Remember that a mixed number consists of an integer part and a fraction part 
(like 3 1/2 -- "three and one-half"). The Mixed class must allow for both 
positive and negative mixed number values. A zero in the denominator of the 
fraction part constitutes an illegal number and should not be allowed. You 
should create appropriate member data in your class. All member data must be 
private.

There should be two constructors. One constructor should take in three 
parameters, representing the integer part, the numerator, and the denominator 
(in that order), used to initialize the object. If the mixed number is to be a 
negative number, the negative should be passed on the first non-zero parameter, 
but on no others. If the data passed in is invalid (negatives not fitting the 
rule, or 0 denominator), then simply set the object to represent the value 0. 
Examples of declarations of objects:

3. Mixed m1(3, 4, 5); // sets object to 3 4/5
4. Mixed m2(-4, 1, 2); // sets object to -4 1/2
5. Mixed m3(0, -3, 5); // sets object to -3/5 (integer part is 0).
6. Mixed m4(-1, -2, 4); // bad parameter combination. Set object to 0.


The other constructor should expect a single int parameter with a default value 
of 0 (so that it also acts as a default constructor). This constructor allows an 
integer to be passed in and represented as a Mixed object. This means that there 
is no fractional part. Example declarations:

Mixed m5(4); // sets object to 4 (i.e. 4 and no fractional part).
Mixed m6; // sets object to 0 (default)

Note that this last constructor will act as a "conversion constructor", allowing 
automatic type conversions from type int to type Mixed.


/******************************************************************************/
/*                       Input                                                */
/*

o The Evaluate function should return the decimal equivalent of the mixed 
   number.
o The Simplify function should simplify the mixed number representation to 
  lowest terms. This means that the fraction part should be reduced to lowest 
  terms, and the fraction part should not be an improper fraction (i.e. 
  disregarding any negative signs, the numerator is smaller than the denominator).
o The ToFraction function should convert the mixed number into fraction form. 
  (This means that the integer part is zero, and the fraction portion may be an 
  improper fraction).

8. Create an overload of the extraction operator >> for reading mixed numbers from 
   an input stream. The input format for a Mixed number object will be:
9. integer numerator/denominator

i.e. the integer part, a space, and the fraction part (in numerator/denominator 
     form), where the integer, numerator, and denominator parts are all of type 
	 int. You may assume that this will always be the format that is entered (i.e. 
	 your function does not have to handle entry of incorrect types that would 
	 violate this format). However, this function should check the values that 
	 come in. In the case of an incorrect entry, just set the Mixed object to 
	 represent the number 0, as a default. An incorrect entry occurs if a 
	 denominator value of 0 is entered, or if an improper placement of a negative 
	 sign is used. Valid entry of a negative number should follow this rule -- if 
	 the integer part is non-zero, the negative sign is entered on the integer 
	 part; if the integer part is 0, the negative sign is entered on the numerator 
	 part (and therefore the negative sign should never be in the denominator). 
	 Examples:

Valid inputs: 2 7/3 , -5 2/7 , 4 0/7 , 0 2/5 , 0 -8/3
Invalid inputs: 2 4/0 , -2 -4/5 , 3 -6/3 , 0 2/-3

/******************************************************************************/
/*                       Output                                               */
/*

output the date to the screen. There will be more than one possible format for 
this output, however, and your class will need to store a format setting. The 
Show function should use the format setting to determine the output. (There 
will be a member function that allows the setting to be changed). When a Date 
object is created, the format setting should start out at the "Default" 
setting. The possible formats are shown in the following table:

Default: M/D/Y -- 10/4/1998
Two-Digit: mm/dd/yy -- 10/04/98
Long month: D, Y -- Oct 4, 1998

/******************************************************************************/
/*                       Header Files                                         */

#include "Mixed.h"                          
#include <iostream>                      // for input and output
using namespace std;

/******************************************************************************/
/*                       Mixed Function                                       */
/*

Author: Claudius Christian
Date:  1/29/2013

Constructor for the Class Date
*/


Mixed::Mixed( const int integer, const int numerator, const int denominator ) 
{
	if( Set( integer, numerator, denominator)  )
	{
		number    = integer;
		numerat   = numerator;
		denominat = denominator;
	}
	
	else
	{
		cout << "Dude. Please enter in a correct number next time. \n";
		
		number    = DEFAULTVALUE;
		numerat   = DEFAULTVALUE;
		denominat = DEFAULTVALUE;
	}

} // end Date::Date ( const int m, const int d, const int y ) 

// default constructor. It sets the numerator and denominator to zer0
// in instances where they were not entered.
Mixed::Mixed( int i )
{
	number = i;
	numerat = DEFAULTVALUE;
	denominat = DEFAULTVALUE;
} // end Mixed::Mixed( int i = DEFAULTVALUE ) 	

/******************************************************************************/
/*                       Evaluate Function                                    */
/*

Author: Claudius Christian
Date:  2/15/2013

Description: turns a fraction into a decimal number.
*/
double Mixed::Evaluate()
{
	double decimalNumber= 0;
	bool negativeNumber = false;

	// checks to determine if the denominator is zero
	if( denominat == 0 )
	{
		// if the denominator is zero print error message
		cout << "\nCannot divide by zero.\n";
	}

	// if the denominator is greater than zero convert 
	// by multiplying the denominator to the whole number
	// and add that number to the numerator. Then divide
	else if ( (denominat > 0) )
	{
		decimalNumber = (number * denominat);
		decimalNumber = decimalNumber + numerat;
		decimalNumber = static_cast<double>(decimalNumber)/denominat;
	}

	return decimalNumber;

} // end evaluate



/******************************************************************************/
/*                       Simplify Function                                    */
/*

Author: Claudius Christian
Date:  2/15/2013

Description: Simplifies the mixed number representation to lowest terms. This 
             means that the fraction part should be reduced to lowest terms, and 
			 the fraction part should not be an improper fraction (i.e. 
			 disregarding any negative signs, the numerator is smaller than the 
			 denominator).
*/

void Mixed::Simplify()
{
	// holds temporary number
	int temp;

	// flag for negative numerators
	bool negativeNumber = false;

	// holds the result of Euclid algorithm
	temp = gcd( numerat, denominat );
	
	numerat = numerat / temp;
	denominat = denominat / temp;

	// if the numerator is negative transfer it to 
	// a positive number and make the integer negative
	if( (numerat < 0) && (number > 0) )
	{
		numerat = -1*(numerat);
		number = -1 * number;
	} // end if
} // end void Mixed::Simplify()

/******************************************************************************/
/*                       Euclid Algorithm Function                            */
/*

Author: Claudius Christian
Date:  2/15/2013

Description: Euclid's algorithm, is an efficient method for computing the 
             greatest common divisor (GCD) of two integers, also known as the 
			 greatest common factor (GCF) or highest common factor (HCF).

Citation: Euclids algorithm is open source circa ~300 BC
*/

int Mixed::gcd( int numerat, int denominat ) 
{
	int temp;

	if( ( number >= 0) && ( numerat > 0) )
	{
		while (denominat != 0) 
		{
			temp = denominat;
			denominat = numerat % denominat;
			numerat = temp;
		} // end while

		return numerat;
	} // end if	

	if( ( number >= 0) && ( numerat < 0) )
	{
		numerat = -1*(numerat);

		while (denominat != 0) 
		{
			temp = denominat;
			denominat = numerat % denominat;
			numerat = temp;
		} // end while

		return numerat;
	} // end if

	if( ( number < 0) && ( numerat > 0) )
	{
		//number = -1*(number);

		while (denominat != 0) 
		{
			temp = denominat;
			denominat = numerat % denominat;
			numerat = temp;
		} // end while
		
		return numerat;
	} // end if	
} // end int Mixed::gcd(int number, int numerat, int denominat) 


/******************************************************************************/
/*                       Set Function                                         */
/*

Author: Claudius Christian
Date:  1/29/2013

Description: This function should set the date to the specified values (the 
             first parameter represents the month, the second represents the 
			 day, and the third represents the year). If the resulting date is 
			 an invalid date, the operation should abort (i.e. the existing 
			 stored date should not be changed). This function should return 
			 true for success and false for failure (i.e. invalid date sent in).
*/

bool Mixed::Set( const int integer, const int numerator, const int denominator )
{
	
	bool validNumber = ( ((integer < 0) && (numerator >= 0) && (denominator > 0)) 
		               || ((integer >= 0) && (numerator < 0) && (denominator > 0))
					   || ((integer >= 0) && numerator >= 0)
					   && (denominator > 0) );

	if( validNumber )
	{
		number = integer;
		numerat = numerator;
		denominat = denominator;
	} // end of if

	return validNumber;
} // end of bool date::set

/******************************************************************************/
/*                       Input Function                                       */
/*

Author: Claudius Christian
Date:  1/29/2013

Description: This function should prompt the user to enter a date, and then 
             allow the user to input a date from the keyboard. User input 
			 is expected to be in the format month/day/year, where month, day, 
			 and year are integer values. Whenever the user attempts to enter 
			 an invalid date, the Input function should display an appropriate 
			 error message (like "Invalid date. Try again: ") and make the user
             re-enter the whole date. A few examples of some good and bad 
			 inputs:

             Legal:     1/4/2000 , 2/28/1996  , 12/31/1845
             Illegal: 13/12/1985 , 11/31/2002 , 8/30/-2000
*/

void Mixed::Input()
{
	int integer, numerator, denominator;

	char backspace;

	cout << "Please enter a mixed fraction: " << endl;
	cin >> integer >> numerator >> backspace >>  denominator;

	while ( !Set(integer, numerator, denominator) )
	{
		cout << "Please enter a mixed fraction: " << endl;
		cin >> integer >> numerator >> backspace >>  denominator;
	} // end while 



} // end void Date::Input

/******************************************************************************/
/*                       To Fraction Function                                 */
/*

Author: Claudius Christian
Date:  2/12/2013

Description: convert the mixed number into fraction form. (This means that the 
             integer part is zero, and the fraction portion may be an improper 
			 fraction).
*/
void Mixed::ToFraction()
{
	if( (number > 0) && (numerat > 0) )
	{
	numerat = (number * denominat) + numerat;
	number = 0;
	}

	else if( (number > 0) && (numerat < 0) )
	{
		numerat = -1*(numerat);
		number  = number * -1;
		numerat = (number * denominat) + numerat;
		number  = 0;
	}

	else if( (numerat == 0) )
	{
		numerat = number * 1;
		denominat = 1;
		number = 0;
	}

	else
	{
		numerat = (number * denominat) + numerat;
		number = 0;
	}
}

/******************************************************************************/
/*                       Overloaded Output Stream                             */
/*

Author: Claudius Christian
Date:  2/15/2013

*/

ostream& operator << (ostream& stream, Mixed& fraction)
{
	
	if( (fraction.numerat == 0) && (fraction.denominat == 0) )
	{
		stream << fraction.number;
	}

	else if( (fraction.number == 0) && (fraction.numerat != 0) && 
		     (fraction.denominat != 0 ) )
	{
		stream << fraction.numerat << "/" << fraction.denominat;
	}

	else if ( (fraction.number == 0) && (fraction.numerat == 0) )
	{
		stream << fraction.number;
	}
	else if( (fraction.number > 0) && (fraction.numerat < 0) )
	{
		fraction.number = fraction.number * -1;
		fraction.numerat = fraction.numerat *-1;

		stream << fraction.number << " " << fraction.numerat << "/" << fraction.denominat;
	}

	else
	{
		stream << fraction.number << " " << fraction.numerat << "/" << fraction.denominat; 
	}

	return stream;
}

/******************************************************************************/
/*                       Overloaded input Stream                              */
/*

Author: Claudius Christian
Date:  2/15/2013
*/

istream& operator >> (istream &stream, Mixed& fraction)
{
	int num1, num2, num3;
	stream>>num1>>num2>>num3;

	if( fraction.Set( num1, num2, num3)  )
	{
	}
	else
	{
		cout << "Dude. Please enter in a correct number next time. \n";	
		fraction.number    = DEFAULTVALUE;
		fraction.numerat   = DEFAULTVALUE;
		fraction.denominat = DEFAULTVALUE;
	}
	return stream;
}

Mixed Mixed::operator++()
{
	if( (number == 0) && (numerat != 0)  )
	{
	numerat = numerat + denominat;
	Simplify();
	return *this;
	}

	else if( (number == 0) && (numerat == 0) )
	{
		number++;
		Simplify();
		return *this;
	}
	else
	{
		number++;
		Simplify();
		return *this;
	}
	return *this;
}

/******************************************************************************/
/*                       Mixed Mixed::operator++()                            */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions subtracts one to a fraction. The function overloads
the prefix ++ operator
*/

Mixed Mixed::operator++()
{
	if( (number == 0) && (numerat != 0)  )
	{
	numerat = numerat + denominat;
	Simplify();
	return *this;
	}

	else if( (number == 0) && (numerat == 0) )
	{
		++number;
		Simplify();
		return *this;
	}
	else
	{
		++number;
		Simplify();
		return *this;
	}
	return *this;
}

/******************************************************************************/
/*                       Mixed Mixed::operator--()                        */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions subtracts one to a fraction. The function overloads
the prefix -- operator
*/

Mixed Mixed::operator--()
{
	if( (number == 0) && (numerat != 0)  )
	{

	numerat = numerat - denominat;
	return *this;

	}
	else if( (number == 0) && (numerat == 0) )
	{
		--number;
		return *this;
	}
	else
	{
		--number;
		return *this;
	}
	return *this;
}

/******************************************************************************/
/*                       Mixed Mixed::operator++ (int)                        */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions adds one to a fraction. The function overloads
the postfix ++ operator
*/

Mixed Mixed::operator++ (int)
{
	Mixed temp;
	temp.number    = number;
	temp.numerat   = numerat;
	temp.denominat = denominat;
	
	if( (number == 0) && (numerat != 0)  )
	{
	numerat = numerat + denominat;
	Simplify();
	return temp;
	}

	else if( (number == 0) && (numerat == 0) )
	{
		number++;
		Simplify();
		return temp;
	}
	
	else
	{
		number++;
		Simplify();
		return temp;
	}
	return temp;
}

/******************************************************************************/
/*                       Mixed Mixed::operator-- (int)                        */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions subtracts a fraction by one. The function overloads
the postfix -- operator
*/

Mixed Mixed::operator-- (int)
{
	Mixed temp;

	temp.number    = number;
	temp.numerat   = numerat;
	temp.denominat = denominat;
	
	if( (number == 0) && (numerat != 0)  )
	{
	numerat = numerat - denominat;
	return temp;
	}

	else if( (number == 0) && (numerat == 0) )
	{
		number--;
		return temp;
	}

	else
	{
		number--;
		return temp;
	}
	return temp;
}

/******************************************************************************/
/*                       Mixed operator+( Mixed& m1, Mixed& m2 )              */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions add m1 and m2 together.
*/

Mixed operator+( Mixed& m1,  Mixed& m2 )
{
	Mixed Answer1( m1.number,m1.numerat,m1.denominat );
	Mixed Answer2( m2.number,m2.numerat,m2.denominat );
	Mixed Answer3;

	Answer1.ToFraction();
	Answer2.ToFraction();

	int Denom1 = Answer1.denominat;
	int Numer1 = Answer1.numerat;
	int Denom2 = Answer2.denominat;
	int Numer2 = Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat = Numer1 * Denom2;
	Answer2.denominat = Denom1 * Denom2;
	Answer2.numerat = Numer2*Denom1;

	Answer3.numerat = Answer1.numerat + Answer2.numerat;
	Answer3.denominat = Answer1.denominat;

	Answer3.Simplify();

	return Answer3;
}

/******************************************************************************/
/*                       Mixed operator+( Mixed& m1, int x )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions add m1 and an integer together.
*/

Mixed operator+( Mixed& m1, int x )
{
	Mixed Answer1( m1.number, m1.numerat, m1.denominat );
	Answer1.ToFraction();

	Mixed Answer2( 0, x * Answer1.denominat, Answer1.denominat );
	Mixed Answer3( 0, 0, Answer1.denominat );

	Answer3.numerat = Answer1.numerat + Answer2.numerat;

	Answer3.Simplify();

	return Answer3;
}

/******************************************************************************/
/*                       Mixed operator+( int x, Mixed& m1)                   */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions add an integer and m1 together.
*/

Mixed operator+( int x, Mixed& m1)
{
	Mixed Answer1( m1.number, m1.numerat, m1.denominat );

	Answer1.ToFraction();

	Mixed Answer2( 0, x * Answer1.denominat, Answer1.denominat );
	Mixed Answer3( 0, 0, Answer1.denominat );

	Answer3.numerat = Answer1.numerat + Answer2.numerat;

	Answer3.Simplify();

	return Answer3;
}

/******************************************************************************/
/*                       Mixed operator-( Mixed& m1,  Mixed& m2 )             */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions subtract m1 from m2.
*/

Mixed operator-( Mixed& m1,  Mixed& m2 )
{
	Mixed Answer1(m1.number,m1.numerat,m1.denominat);
	Mixed Answer2(m2.number,m2.numerat,m2.denominat);
	Mixed Answer3;

	Answer1.ToFraction();
	Answer2.ToFraction();
	
	int Denom1 = Answer1.denominat;
	int Numer1 = Answer1.numerat;
	int Denom2 = Answer2.denominat;
	int Numer2 = Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat = Numer1 * Denom2;
	Answer2.denominat = Denom1 * Denom2;
	Answer2.numerat = Numer2  *Denom1;
	
	Answer3.numerat = Answer1.numerat - Answer2.numerat;
	Answer3.denominat = Answer1.denominat;

	Answer3.Simplify();

	return Answer3;
}

/******************************************************************************/
/*                       Mixed operator-( Mixed& m1, int x )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions subtract m1 from an integer.
*/

Mixed operator-( Mixed& m1, int x )
{
	Mixed Answer1( m1.number, m1.numerat, m1.denominat );
	
	Answer1.ToFraction();

	Mixed Answer2( 0, x * Answer1.denominat, Answer1.denominat );
	Mixed Answer3( 0, 0, Answer1.denominat );
	Answer3.numerat = Answer1.numerat - Answer2.numerat;
	
	Answer3.Simplify();
	
	return Answer3;
}

/******************************************************************************/
/*                       Mixed operator-( int x, Mixed& m1 )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions subtract an integer from m1.
*/

Mixed operator-( int x, Mixed& m1 )
{
	Mixed Answer1( m1.number, m1.numerat, m1.denominat );
	
	Answer1.ToFraction();

	Mixed Answer2( 0, x * Answer1.denominat, Answer1.denominat );
	Mixed Answer3(0, 0, Answer1.denominat);

	Answer3.numerat = Answer2.numerat - Answer1.numerat;
	
	Answer3.Simplify();
	
	return Answer3;
}

/******************************************************************************/
/*                       Mixed operator/( Mixed& m1,  Mixed& m2 )             */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions divide m1 from m2.
*/
	
Mixed operator/( Mixed& m1,  Mixed& m2 )
{
	Mixed answer1(m1.number, m1.numerat,m1.denominat);
	Mixed answer2(m2.number, m2.numerat,m2.denominat);
	Mixed answer3;
	
	answer1.ToFraction();
	answer2.ToFraction();

	int temp=answer2.numerat;
	answer2.numerat = answer2.denominat;
	answer2.denominat = temp;

	answer3.numerat = answer1.numerat * answer2.numerat;
	answer3.denominat=answer1.denominat*answer2.denominat;
	answer3.Simplify();
	
	return answer3;
}

/******************************************************************************/
/*                       Mixed operator/( int x, Mixed& m2 )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions divide an integer from m1.
*/

Mixed operator/( int x, Mixed& m2 )
{
	Mixed answer1( 0, x, 1 );
	Mixed answer2( m2.number, m2.numerat,m2.denominat );
	Mixed answer3;
	
	answer1.ToFraction();
	answer2.ToFraction();

	int temp = answer2.numerat;
	
	answer2.numerat = answer2.denominat;
	answer2.denominat = temp;

	answer3.numerat = answer1.numerat * answer2.numerat;
	answer3.denominat = answer1.denominat * answer2.denominat;
	
	answer3.Simplify();
	
	return answer3;
}

/******************************************************************************/
/*                       Mixed operator/( Mixed& m2, int x )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions divide m1 from an integer.
*/

Mixed operator/( Mixed& m2, int x )
{
	Mixed answer1(0, x, 1);
	Mixed answer2(m2.number, m2.numerat,m2.denominat);
	Mixed answer3;
	
	answer1.ToFraction();
	answer2.ToFraction();

	int temp=answer1.numerat;
	answer1.numerat=answer1.denominat;
	answer1.denominat=temp;

	answer3.numerat=answer1.numerat*answer2.numerat;
	answer3.denominat=answer1.denominat*answer2.denominat;
	answer3.Simplify();
	
	return answer3;



}

/******************************************************************************/
/*                       Mixed operator*( Mixed& m1, Mixed& m2 )              */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions multiplies m1 to m2.
*/

Mixed operator*( Mixed& m1, Mixed& m2 )
{
	Mixed answer1(m1.number, m1.numerat, m1.denominat);
	Mixed answer2(m2.number, m2.numerat,m2.denominat);
	Mixed answer3;

	answer1.ToFraction();
	answer2.ToFraction();

	answer3.numerat   = answer1.numerat * answer2.numerat;
	answer3.denominat = answer2.denominat * answer2.denominat;

	answer3.Simplify();

	return answer3;
}

/******************************************************************************/
/*                       Mixed operator*( int x, Mixed& m2 )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions multiplies an integer to m1.
*/

Mixed operator*( int x, Mixed& m2 )
{
	Mixed answer1(0, x, 1);
	Mixed answer2(m2.number, m2.numerat,m2.denominat);
	Mixed answer3;

	answer1.ToFraction();
	answer2.ToFraction();

	answer3.numerat   = answer1.numerat * answer2.numerat;
	answer3.denominat = answer2.denominat * answer2.denominat;

	answer3.Simplify();

	return answer3;
}

/******************************************************************************/
/*                       Mixed operator*( Mixed& m1, int x                    */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions multiplies m1 to an integer.
*/

Mixed operator*( Mixed& m1, int x )
{
	Mixed answer1(m1.number, m1.numerat, m1.denominat);
	Mixed answer2(0, x, 1);
	Mixed answer3;

	answer1.ToFraction();
	answer2.ToFraction();

	answer3.numerat   = answer1.numerat * answer2.numerat;
	answer3.denominat = answer2.denominat * answer2.denominat;

	answer3.Simplify();

	return answer3;
}

/******************************************************************************/
/*                       bool operator==( Mixed& m1, Mixed& m2 )              */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 and m2 are equal.
*/

bool operator==( Mixed& m1, Mixed& m2 )
{
	Mixed Answer1(m1.number, m1.numerat, m1.denominat);
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( Answer1.numerat == Answer2.numerat )
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

/******************************************************************************/
/*                       bool operator==( int x, Mixed& m2 )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if an integer and m1 are equal.
*/

bool operator==( int x, Mixed& m2 )
{
	Mixed Answer1(0, x, 1);
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( Answer1.numerat == Answer2.numerat )
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

/******************************************************************************/
/*                       bool operator==( Mixed& m1, int x )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 and an integer are equal.
*/

bool operator==( Mixed& m1, int x )
{
	Mixed Answer1(m1.number, m1.numerat, m1.denominat);
	Mixed Answer2( 0, x, 1 );

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( Answer1.numerat == Answer2.numerat )
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

/******************************************************************************/
/*                       bool operator!=( Mixed& m1, Mixed& m2 )              */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 and m2 aren't equal.
*/


bool operator!=( Mixed& m1, Mixed& m2 )
{

	Mixed Answer1(m1.number, m1.numerat, m1.denominat);
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat != Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return true;
}

/******************************************************************************/
/*                       bool operator!=( int x, Mixed& m2 )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if an integer and m1 aren't equal.
*/

bool operator!=( int x, Mixed& m2 )
{
	Mixed Answer1( 0, x , 1 );
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat != Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return false;
}

/******************************************************************************/
/*                       bool operator!=( Mixed& m1, int x )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 and an integer aren't equal.
*/

bool operator!=( Mixed& m1, int x )
{
	Mixed Answer1( m1.number, m1.numerat, m1.denominat );
	Mixed Answer2( 0, x , 1 );

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat != Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return true;
}

/******************************************************************************/
/*                       bool operator<( Mixed& m1, Mixed& m2 )               */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 is less than m2.
*/

bool operator<( Mixed& m1, Mixed& m2 )
{

	Mixed Answer1(m1.number, m1.numerat, m1.denominat);
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat > Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return 0;
}

/******************************************************************************/
/*                       bool operator<( int x, Mixed& m2 )                   */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if an integer is less than m2.
*/

bool operator<( int x, Mixed& m2 )
{

	Mixed Answer1( 0, x, 1 );
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat > Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return 0;
}

/******************************************************************************/
/*                       bool operator<( Mixed& m1, int x )                   */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 is less than an integer.
*/

bool operator<( Mixed& m1, int x )
{

	Mixed Answer1( m1.number, m1.numerat, m1.denominat ); 
	Mixed Answer2( 0, x, 1 );

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat > Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return 0;
}

/******************************************************************************/
/*                       bool operator<=( Mixed& m1, Mixed& m2 )              */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 is less than or equal to m2.
*/

bool operator<=( Mixed& m1, Mixed& m2 )
{

	Mixed Answer1(m1.number, m1.numerat, m1.denominat);
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat >= Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return false;
}

/******************************************************************************/
/*                       bool operator<=( int x, Mixed& m2 )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if an integer is less than or equal to m2.
*/

bool operator<=( int x, Mixed& m2 )
{

	Mixed Answer1( 0, x, 1 );
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat >= Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return false;
}

/******************************************************************************/
/*                       bool operator<=( Mixed& m1, int x )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 is less than or equal to an integer.
*/

bool operator<=( Mixed& m1, int x )
{

	Mixed Answer1( m1.number, m1.numerat, m1.denominat ); 
	Mixed Answer2( 0, x, 1 );

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat >= Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return false;
}

/******************************************************************************/
/*                       bool operator>( Mixed& m1, Mixed& m2 )               */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 is greater than m2.
*/

bool operator>( Mixed& m1, Mixed& m2 )
{

	Mixed Answer1(m1.number, m1.numerat, m1.denominat);
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat < Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return false;
}

/******************************************************************************/
/*                       bool operator>( int x, Mixed& m2 )                   */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if an integer is greater than m2.
*/

bool operator>( int x, Mixed& m2 )
{

	Mixed Answer1( 0, x, 1 );
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat < Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return 0;
}

/******************************************************************************/
/*                       bool operator>( Mixed& m1, int x )                   */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 is greater than an integer.
*/

bool operator>( Mixed& m1, int x )
{

	Mixed Answer1( m1.number, m1.numerat, m1.denominat ); 
	Mixed Answer2( 0, x, 1 );

	Answer1.ToFraction();
	Answer2.ToFraction();

	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat < Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return 0;
}

/******************************************************************************/
/*                       Overloaded input Stream                              */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 is greater than or equal to m2.
*/

bool operator>=( Mixed& m1, Mixed& m2 )
{

	Mixed Answer1(m1.number, m1.numerat, m1.denominat);
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat <= Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return 0;
}

/******************************************************************************/
/*                       bool operator>=( int x, Mixed& m2 )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if an ingeter m1 is greater than an m2.
*/

bool operator>=( int x, Mixed& m2 )
{

	Mixed Answer1( 0, x, 1 );
	Mixed Answer2(m2.number, m2.numerat, m2.denominat);

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat <= Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return 0;
}

/******************************************************************************/
/*                       bool operator>=( Mixed& m1, int x )                  */
/*

Author: Claudius Christian
Date:  2/15/2013

The following functions determines if m1 is greater than or equal to an integer.
*/

bool operator>=( Mixed& m1, int x )
	{

	Mixed Answer1( m1.number, m1.numerat, m1.denominat ); 
	Mixed Answer2( 0, x, 1 );

	Answer1.ToFraction();

	Answer2.ToFraction();


	int Denom1=Answer1.denominat;
	int Numer1=Answer1.numerat;
	int Denom2=Answer2.denominat;
	int Numer2=Answer2.numerat;

	Answer1.denominat = Denom1  * Denom2;
	Answer1.numerat=Numer1*Denom2;
	Answer2.denominat= Denom1 * Denom2;
	Answer2.numerat=Numer2*Denom1;

	if( (Answer1.numerat <= Answer2.numerat) )
	{
		return true;
	}

	else
	{
		return false;
	}
	return 0;
}