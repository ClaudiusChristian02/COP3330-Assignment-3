/******************************************************************************/
/*                       Mixed Class                                          */

/******************************************************************************/
/*                       Author and Date                                      */
/*

Author: Claudius Christian 
Date: 2/12/2013 
*/

/******************************************************************************/
/*                       Description                                          */
/*

Description: Description: Objects of type Mixed will store and manage rational 
                          numbers in a mixed number format (integer part and a 
						  fraction part).
*/

/******************************************************************************/
/*                       Header Files                                         */

#include <iostream>          // for input and output
using namespace std;

/******************************************************************************/
/*                       Constants                                            */

const int DEFAULTVALUE = 0;


/******************************************************************************/
/*                       Class Mixed                                          */

class Mixed
{


// **********************************************************
// * Public member functions.                               *
// **********************************************************

public:
	Mixed( const int integer, const int numerator, const int denominator );
	Mixed( int i = DEFAULTVALUE );
	double Evaluate();
	int gcd( int numerat, int denominat );
	void Input();
	void ToFraction();
	void Simplify();
	bool Set( const int integer, const int numerator, const int denominator );

	friend ostream& operator << (ostream& stream, Mixed& fraction);
	friend istream& operator >> (istream& stream, Mixed& fraction);

	Mixed operator++ ();
	Mixed operator-- ();
	Mixed operator++ (int);
	Mixed operator-- (int);
	friend Mixed operator+( Mixed& m1, int x );
	friend Mixed operator+( int x, Mixed& m1 );
	friend Mixed operator+( Mixed& m1, Mixed& m2 );
	friend Mixed operator-( Mixed& m1, int x );
	friend Mixed operator-( int x, Mixed& m1 );
	friend Mixed operator-( Mixed& m1, Mixed& m2 );
	friend Mixed operator/( Mixed& m1, Mixed& m2 );
	friend Mixed operator/( int x, Mixed& m2 );
	friend Mixed operator/( Mixed& m2, int x );
	friend Mixed operator*( Mixed& m1, Mixed& m2);
	friend bool operator==(Mixed& m1, Mixed& m2);
	friend bool operator!=(Mixed& m1, Mixed& m2);
	friend bool operator<(Mixed& m1, Mixed& m2);
	friend bool operator<=(Mixed& m1, Mixed& m2);
	friend bool operator>(Mixed& m1, Mixed& m2);
	friend bool operator>=(Mixed& m1, Mixed& m2);


	//Mixed operator* (const Mixed& m1, const Mixed& m2);
		//, *, -, +();
// **********************************************************
// * Private member functions.                              *
// **********************************************************	

private:
	int number;
	int numerat;
	int denominat;

}; // end of class date
