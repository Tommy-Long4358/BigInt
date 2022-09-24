#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include <vector>
using namespace std;

class BigInt
{
	private:
		vector<char> storage;
		vector<char>::iterator it;
		vector<char>::reverse_iterator rit;
		
	public:
		BigInt();
		BigInt(string);
		BigInt(int);
		BigInt operator=(BigInt);
		friend ostream& operator<<(ostream&, const BigInt&);
		BigInt operator+(BigInt);
		BigInt operator-(BigInt);
		bool operator<=(BigInt);
		bool operator==(BigInt);
		friend bool operator<(BigInt, BigInt);
		BigInt operator++(int);
		void print() const;
};
#endif
