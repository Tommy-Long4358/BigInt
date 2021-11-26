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
		BigInt(const BigInt&);
		BigInt operator=(const BigInt&);
		friend ostream& operator<<(ostream&, const BigInt&);
		BigInt operator+(const BigInt&);
		BigInt operator-(const BigInt&);
		bool operator<=(const BigInt&);
		bool operator==(const BigInt&);
		friend bool operator<(BigInt, BigInt);
		friend BigInt operator++(BigInt&, int);
		void print() const;
};

