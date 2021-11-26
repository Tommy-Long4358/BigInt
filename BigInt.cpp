#include "BigInt.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

BigInt::BigInt()
{
    storage.push_back(0 + '0');
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
    storage.clear();

    for (int i = 0; i < b1.storage.size(); i++)
    {
        storage.push_back(b1.storage[i]);
    }
}

BigInt BigInt::operator=(const BigInt& b1)
{
    storage = b1.storage;

    return *this;
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

BigInt BigInt::operator+(const BigInt& b1)
{
    BigInt b3;
    vector<char> ans;

    vector<char> min;
    vector<char> max;

    int i = 0;
    int carry = 0;
    int sum = 0;

    b3.storage = storage;

    if (b3.storage.size() < b1.storage.size())
    {
        min = b3.storage;
        max = b1.storage;
    }
    else
    {
        max = b3.storage;
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

    b3.storage = ans;

    return b3;
}

BigInt BigInt::operator-(const BigInt& b2)
{
    BigInt b3;

    vector<char> ans;

    vector<char> min;
    vector<char> max;

    int sum = 0;
    int index = 0;
    b3.storage = storage;

    if (b3.storage.size() > b2.storage.size())
    {
        max = b3.storage;
        min = b2.storage;
    }
    else if (b3.storage.size() < b2.storage.size())
    {
        max = b2.storage;
        min = b3.storage;
    }
    else
    {
        max = b3.storage;
        min = b2.storage;
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







        


