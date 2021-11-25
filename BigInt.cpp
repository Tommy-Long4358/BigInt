#include "BigInt.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

BigInt::BigInt()
{
    storage.push_back(0);
}
  
BigInt::BigInt(string n)
{
    for (int i = 0; i < n.length(); i++)
    {
        
        storage.push_back(n[i] - 48);
    }
}

BigInt::BigInt(int n)
{
    string s = to_string(n);

    for (int i = 0; i < s.length(); i++)
    {
        storage.push_back(s[i] - 48);
    }
}

BigInt::BigInt(const BigInt& b1)
{
    storage = b1.storage;
}

BigInt BigInt::operator=(const BigInt &b1)
{
    BigInt b3;

    b3.storage = b1.storage;
   
    return b3;
}

void BigInt::print() const
{
    for (auto i : storage)
    {

        cout << int(i);
    }
}

ostream& operator<<(ostream& out, const BigInt& b1)
{
    int count = 0;
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
        b1.print();
        return out;
    }
}

/*
BigInt BigInt::operator+(int num)
{
    vector<char> ans;

    vector<char> b1;
    vector<char> min;
    vector<char> max;

    int i = 0;
    int carry = 0;
    int sum = 0;

    

    while (num != 0)
    {
        sum = num % 10;

        b1.push_back(sum);

        num = num / 10;
    }

    reverse(b1.begin(), b1.end());

    if (storage.size() < b1.size())
    {
        min = storage;
        max = b1;
    }
    else
    {
        max = storage;
        min = b1;
    }

    for (rit = max.rbegin(); rit != max.rend(); rit++)
    {

        if (i < min.size())
        {
            sum = int(*rit) + int(min[min.size() - 1 - i]) + carry;
        }
        else
        {
            sum = int(*rit) + carry;
        }

        if (sum >= 10)
        {
            ans.push_back(sum % 10);
            carry = sum / 10;
        }
        else
        {
            ans.push_back(sum);
            carry = 0;
        }

        i++;
    }

    if (carry > 0)
    {
        ans.push_back(carry);
    }

    reverse(ans.begin(), ans.end());

    storage = ans;

    return *this;
}
*/


BigInt BigInt::operator+(const BigInt& b1)
{
    
    vector<char> ans;

    vector<char> min;
    vector<char> max;

    int i = 0;
    int carry = 0;
    int sum = 0;

    if (storage.size() < b1.storage.size())
    {
        min = storage;
        max = b1.storage;
    }
    else
    {
        max = storage;
        min = b1.storage;
    }

    for (rit = max.rbegin(); rit != max.rend(); rit++)
    {

        if (i < min.size())
        {
            sum = int(*rit) + int(min[min.size() - 1 - i]) + carry;
        }
        else
        {
            sum = int(*rit) + carry;
        }

        if (sum >= 10)
        {
            ans.push_back(sum % 10);
            carry = sum / 10;
        }
        else
        {
            ans.push_back(sum);
            carry = 0;
        }

        i++;
    }

    if (carry > 0)
    {
        ans.push_back(carry);
    }

    reverse(ans.begin(), ans.end());

    storage = ans;

    return *this;
}

BigInt BigInt::operator-(const BigInt& b2)
{
    BigInt b3;
    
    vector<char> ans;
   
    vector<char> min;
    vector<char> max;

    int sum = 0;
    int index = 0;

    if (storage.size() > b2.storage.size())
    {
        max = storage;
        min = b2.storage;
    }
    else if (storage.size() < b2.storage.size())
    {
        max = b2.storage;
        min = storage;
    }
    else
    {
        if (*this == b2)
        {
            max = storage;
            min = b2.storage;
        }

        for (int i = 0; i < storage.size(); i++)
        {
            if (int(storage[i]) < int(b2.storage[i]))
            {
                max = b2.storage;
                min = storage;
                break;
            }
            else if (int(storage[i]) > int(b2.storage[i]))
            {
                max = storage;
                min = b2.storage;
                break;
            }
        }
    }

    for (rit = max.rbegin(); rit != max.rend(); rit++)
    {
        if (index < min.size())
        {
            sum = int(*rit) - int(min[min.size() - 1 - index]);
        }
        else
        {
            sum = *rit;
        }

        if (sum < 0)
        {
            for (int j = index; j < max.size(); j++)
            {
                if (j != index && j < min.size())
                {
                    if (max[max.size() - 1 - j] > min[min.size() - 1 - j])
                    {
                        max[max.size() - 1 - j] -= 1;
                        break;
                    }
                    else 
                    {
                        max[max.size() - 1 - j] = (max[max.size() - 1 - j] + 10) - 1;
                    }
                }
                else if (j >= min.size())
                {
                    if (int(max[max.size() - 1 - j]) == 0)
                    {
                        max[max.size() - 1 - j] = (max[max.size() - 1 - j] + 10) - 1;
                    }
                    else
                    {
                        max[max.size() - 1 - j] -= 1;
                        break;
                    }
          
                }
            }

            sum = (int(*rit) + 10) - int(min[min.size() - 1 - index]);
            ans.push_back(sum);
        }
        else
        { 
           ans.push_back(sum);
        }

        index++;
    }
   
    reverse(ans.begin(), ans.end());
    b3.storage = ans;
    
    if (b3.storage.size() > 1)
    {
        for (int j = 0; j < ans.size(); j++)
        {
            if (int(ans[j]) != 0)
            {
                break;
            }
            else
            {
                b3.storage.erase(b3.storage.begin());
            }
        }
    }


   
    return b3;
}


BigInt operator++(BigInt& b1, int num)
{
    
    // it'll recognize to use operator+
    b1 = b1 + BigInt(1);

    return b1;
}

bool BigInt::operator==(const BigInt& b2)
{
    /*
    if (storage.size() < b2.storage.size())
    {
        return false;
    }
    else if (storage.size() > b2.storage.size())
    {
        return false;
    }
    
      
    for (int i = 0; i < storage.size(); i++)
    {
        if (int(storage[i]) != int(b2.storage[i]))
        {
            return false;
        }
    }

    return true;
    
    */

    if (storage == b2.storage)
    {
        return true;
    }

    return false;


}

bool BigInt::operator<=(const BigInt& b2)
{
    if (storage.size() < b2.storage.size())
    {
        return true;
    }
    else if (storage.size() > b2.storage.size())
    {
        return false;
    }

    if (*this == b2)
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

bool BigInt::operator<(const BigInt& b2)
{
    if (storage.size() < b2.storage.size())
    {
        return true;
    }
    else if (storage.size() > b2.storage.size())
    {
        return false;
    }

    if (*this == b2)
    {
        return false;
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








        

