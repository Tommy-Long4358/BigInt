#include "BigInt.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

// Empty constructor that has BigInt 0.
BigInt::BigInt()
{
    storage.push_back(0);
}
 
// Constructor that converts a string to BigInt.
BigInt::BigInt(string n)
{
    for (int i = 0; i < n.length(); i++)
    {
        storage.push_back(n[i] - 48);
    }
}

// Constructor that converts an int to BigInt.
BigInt::BigInt(int n)
{
    string s = to_string(n);

    for (int i = 0; i < s.length(); i++)
    {
        storage.push_back(s[i] - 48);
    }
}

// operator function that assigns a BigInt as another BigInt object.
BigInt BigInt::operator=(BigInt b1)
{
    storage = b1.storage;
    return *this;
}

// print function to print out every number in BigInt.
void BigInt::print() const
{
    for (auto i : storage)
    {
        cout << int(i);
    }
}

// ostream operator to print out BigInt numbers in scientific notation.
ostream& operator<<(ostream& out, const BigInt& b1)
{
    int count = 0;

    // Make it in scientific notation if there is more than 12 digits.
    if (b1.storage.size() > 12)
    {
        cout << int(b1.storage[0]) << ".";

   
        for (int i = 1; i < b1.storage.size(); i++)
        {
            cout << int(b1.storage[i]);
            count++;

            if (count == 12)
            {
                break;
            }
        }

       
        cout << "e" << b1.storage.size() - 1;

        return out;

    }
    else
    {
        // print out BigInt regularly if it has less than 12 numbers.
        b1.print();
        return out;
    }
}

// + operator that adds two BigInts together.
BigInt BigInt::operator+(BigInt b2)
{
    vector<char> min;
    vector<char> max;
    BigInt b3;
    vector<char> ans;
    int carry = 0;

    

    // if statements to determine a min and max.
    if (storage.size() > b2.storage.size())
    {
        int diff = storage.size() - b2.storage.size();

        max = storage;

        // add leading zeroes to make the two vectors equal in size.
        for (int i = 0; i < diff; i++)
        {
            min.push_back(0);
        }

        // push the numbers in the BigInt object after the leading zeroes are added
        for (int i = 0; i < b2.storage.size(); i++)
        {
            min.push_back(b2.storage[i]);
        }
    }
    else if (b2.storage.size() > storage.size())
    {
        int diff = b2.storage.size() - storage.size();

        max = b2.storage;

        for (int i = 0; i < diff; i++)
        {
            min.push_back(0);
        }

        for (int i = 0; i < storage.size(); i++)
        {
            min.push_back(storage[i]);
        }
    }
    else
    {
        max = storage;
        min = b2.storage;
    }

    for (int i = 0; i < max.size(); i++)
    {
        // Regular addition with a carry.
        int sum = int(max[max.size() - 1 - i]) + int(min[min.size() - 1 - i]) + carry;

        // If the sum of two numbers are greater or equal to 10, we push the remainder of the sum % 10 and add a carry.
        if (sum >= 10)
        {
            ans.push_back(sum % 10);
            carry = 1;
        }
        else
        {
            // If the sum is less than 10, add the sum normally into the vector.
            ans.push_back(sum);
            carry = 0;
        }
    }

    // if a carry is left over after the loop has finished, we push it into the vector.
    if (carry == 1)
    {
        ans.push_back(carry);
    }

    // Reverse the number so that it displays the correct number.
    reverse(ans.begin(), ans.end());

    // storage copy
    b3.storage = ans;

    return b3;  
}

// - operator that subtracts 2 BigInts.
BigInt BigInt::operator-(BigInt b2)
{
    vector<char> ans;
    vector<char> mini;
    vector<char> maxi;
    
    int diff = 0;

    maxi = storage;
    if (storage.size() > b2.storage.size())
    {
        diff = storage.size() - b2.storage.size();

        maxi = storage;
        
        for (int i = 0; i < diff; i++)
        {
            mini.push_back(0);
        }

        for (int i = 0; i < b2.storage.size(); i++)
        {
            mini.push_back(b2.storage[i]);
        }
    }
    else if (b2.storage.size() > storage.size())
    {
        diff = b2.storage.size() - storage.size();

        maxi = b2.storage;
        
        for (int i = 0; i < diff; i++)
        {
            mini.push_back(0);
        }

        for (int i = 0; i < storage.size(); i++)
        {
            mini.push_back(storage[i]);
        }
    }
    else
    {
        mini = b2.storage;
    }

    int carry = 0;
    int borrow = 10;
    for (int i = 0; i < maxi.size(); i++)
    {
        int sum = int(maxi[maxi.size() - 1 - i]) - int(mini[mini.size() - 1 - i]) + carry;

        // if the sum is less than 0, we do a borrow on it and make the carry -1 so that we do the borrow on other numbers.
        if (sum < 0)
        {
            ans.push_back(borrow + sum);
            carry = -1;
        }
        else
        {
            ans.push_back(sum);
            carry = 0;
        }
    }

    BigInt b3;

    reverse(ans.begin(), ans.end());
    b3.storage = ans;

    // Delete the leading zeroes
    if (ans.size() > 1 && int(ans[0]) == 0)
    {
        for (int j = 0; j < ans.size(); j++)
        {
            // If the first number found is not a zero, we break from the loop
            if (int(ans[j]) != 0)
            {
                break;
            }
            else
            {
                // Delete the leading zeroes
                b3.storage.erase(b3.storage.begin());
            }
        }
    }

    return b3;
    
}

// ++ operator that adds 1 to BigInt number.
BigInt BigInt::operator++(int num)
{
    // adds 1 to the BigInt object.
    // Uses the operator+ to achieve this.
    *this = *this + BigInt(1);

    return *this;
}

// == operator that determines whether a BigInt object is equal to another BigInt.
bool BigInt::operator==(BigInt b2)
{
    if (storage == b2.storage)
    {
        return true;
    }

    return false;
}

// <= operator that determines whether a BigInt object is less than or equal to another BigInt.
bool BigInt::operator<=(BigInt b2)
{
    if (storage.size() < b2.storage.size())
    {
        return true;
    }
    else if (storage.size() > b2.storage.size())
    {
        return false;
    }

    if (storage == b2.storage)
    {
        return true;
    }
    
    for (int i = 0; i < storage.size(); i++)
    {
        if (int(storage[i]) < int(b2.storage[i]))
        {
            return true;
        }
        else if (int(storage[i]) > int(b2.storage[i]))
        {
            return false;
        }
    }

    return false;
  
}

// < operator that determines whether a BigInt is less than another BigInt.
bool operator<(BigInt b1, BigInt b2)
{

    if (b1.storage.size() < b2.storage.size())
    {
        return true;
    }
    else if (b1.storage.size() > b2.storage.size())
    {
        return false;
    }

    if (b1.storage == b2.storage)
    {
        return false;
    }

    for (int i = 0; i < b1.storage.size(); i++)
    {
        if (int(b1.storage[i]) < int(b2.storage[i]))
        {
            return true;
        }
        else if (int(b1.storage[i]) > int(b2.storage[i]))
        {
            return false;
        }
    }
    return false;
}
