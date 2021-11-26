// This is the demo program you will run
#include <climits>
#include <map>
#include <iostream>
#include <string>
#include "BigInt.h" // header file for BigInt
using namespace std;

// include this file so that the demo program has access to the GoldRabbits function.
// You must write 2 versions of goldRabbits - here are the prototypes

int goldRabbits(int); // you must implement this 
BigInt goldRabbits(BigInt); // you must implement this

//#include "GoldRabbits.tools"

void pause() { cout << "Press Enter to continue..."; getchar(); } // utility function

int main()
{
	BigInt B1("123456789123456789123456789123456789");
	BigInt B2(B1);
	BigInt MAX(INT_MAX);
	BigInt B3(51);
	BigInt B4(51);

	cout << "B1:" << B1 << "\nB2:" << B2 << "\nMAX:" << MAX << endl;
	pause();

	B3 = B3 + BigInt(1);

	cout << B3 << endl;
	
	pause();
	for (BigInt i = 0; i <= BigInt(50); i++)
	{
		
		cout << "\ngoldRabbits(" << i << ") = " << goldRabbits(i);
	}
	

	
	

	/*
	cout << "\n\nThis is the long value of goldRabbits(3000)\n\n";

	BigInt gR3000 = goldRabbits(BigInt(3000));
	gR3000.print();

	cout << "\n\nThis is the short value of goldRabbits(3000):" << gR3000 << endl;

	pause();

	int n = 500;

	try 
	{
		cout << "\nThe value of goldRabbits(" << n << ") is: ";
		cout << goldRabbits(n) << endl;
	}
	catch (const string& error)
	{
		cout << error << endl;
		cout << "Transitioning to BigInt\n";
		cout << goldRabbits(BigInt(n)) << endl;
	}
	pause();
	*/
	

	return 0;

	
}

int goldRabbits(int n)
{
	static map<int, int> intRabbits;

	if (n == 0 || n == 1)
	{
		return 1;
	}
	else
	{
		int sum = goldRabbits(n - 1) + goldRabbits(n - 2);
		
		if (sum < 0)
		{
			string overflowError = "Overflow Error - goldRabbits overflowed using " + to_string(n);
			throw overflowError;
		}
		
		return sum;
	}	
}


BigInt goldRabbits(BigInt n)
{
	static map<BigInt, BigInt> bigIntRabbits;
	

	BigInt sum;

	/*
	if (n == BigInt(1) || n == BigInt(1))
	{
		return BigInt(1);
	}
	else
	{
		return goldRabbits(n - BigInt(1)) + goldRabbits(n - BigInt(2));
	}
	*/
	

	
	// if map has n as the key, then return the value
	if (bigIntRabbits.find(n) != bigIntRabbits.end())
	{
		return bigIntRabbits[n];
	}
	// else calculate n and store in rabbit map
	else
	{
		if (n == BigInt(0) || n == BigInt(1))
		{
			return BigInt(1);
		}

		sum = goldRabbits(n - BigInt(1)) + goldRabbits(n - BigInt(2));
		
		bigIntRabbits.insert(make_pair(n, sum));

		return sum;

		
	}
}






