#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class BigInt
{
private:
	string num;
public:
	BigInt() : num("0") {}
	BigInt(const string& str) : num(str) {}
	BigInt(long long n) {num = to_string(n);}
	BigInt operator+(const BigInt& other) const
	{
		string result;
		int carry = 0;
		int i = num.size() - 1, j = other.num.size() - 1;
		while (i >= 0 || j >= 0 || carry)
		{
			int sum = carry;
			if (i >= 0) sum += num[i--] - '0';
			if (j >= 0) sum += other.num[j--] - '0';
			result.push_back(sum % 10 + '0');
			carry = sum / 10;
		}

		reverse(result.begin(), result.end());
		return BigInt(result);
	}
	BigInt operator-(const BigInt& other) const
	{
		string result;
		int borrow = 0;
		int i = num.size() - 1, j = other.num.size() - 1;

		while (i >= 0 || j >= 0)
		{
			int diff = borrow;
			if (i >= 0) diff += num[i--] - '0';
			if (j >= 0) diff -= other.num[j--] - '0';
			if (diff < 0)
			{
				diff += 10;
				borrow = -1;
			}
			else
			{
				borrow = 0;
			}
			result.push_back(diff + '0');
		}

		while (result.size() > 1 && result.back() == '0') result.pop_back();
		reverse(result.begin(), result.end());
		return BigInt(result);
	}
	BigInt operator*(const BigInt& other) const
	{
		int n = num.size(), m = other.num.size();
		string result(n + m, '0');

		for (int i = n - 1; i >= 0; --i)
		{
			for (int j = m - 1; j >= 0; --j)
			{
				int mul = (num[i] - '0') * (other.num[j] - '0');
				int p1 = i + j, p2 = i + j + 1;
				int sum = mul + (result[p2] - '0');

				result[p2] = sum % 10 + '0';
				result[p1] += sum / 10;
			}
		}

		while (result.size() > 1 && result.front() == '0') result.erase(result.begin());
		return BigInt(result);
	}
	BigInt operator/(const BigInt& other) const
	{
		if (other == BigInt("0"))
		{
			cerr<<":< WHY DIVIDE BY ZERO?"<<endl;
			exit(114514);
		}
		BigInt dividend = *this;
		BigInt divisor = other;
		BigInt quotient("0");
		BigInt remainder("0");
		for (int i = 0; i < dividend.num.size(); ++i)
		{
			remainder = remainder * BigInt("10") + BigInt(std::string(1, dividend.num[i]));
			int count = 0;
			while (remainder >= divisor)
			{
				remainder = remainder - divisor;
				++count;
			}
			quotient = quotient * BigInt("10") + BigInt(std::to_string(count));
		}
		return quotient;
	}
	BigInt operator/(int divisor) const
	{
		if (divisor == 0)
		{
			cerr<<":< WHY DIVIDE BY ZERO?"<<endl;
			exit(114514);
		}
		BigInt quotient("0");
		long long remainder = 0;
		for (int i = 0; i < num.size(); ++i)
		{
			remainder = remainder * 10 + (num[i] - '0');
			quotient.num.push_back(remainder / divisor + '0');
			remainder %= divisor;
		}
		while (quotient.num.size() > 1 && quotient.num.front() == '0')
		{
			quotient.num.erase(quotient.num.begin());
		}
	
		return quotient;
	}
	friend ostream& operator<<(ostream& os, const BigInt& bi)
	{
		os << bi.num;
		return os;
	}
	bool operator<(const BigInt& other) const
	{
		if (num.size() != other.num.size()) return num.size() < other.num.size();
		return num < other.num;
	}
	bool operator<=(const BigInt& other) const{return *this < other || *this == other;}
	bool operator==(const BigInt& other) const{return num == other.num;}
	bool operator>=(const BigInt& other) const {return !(*this < other);}
	bool operator>(const BigInt& other) const {return !(*this <= other);}
	BigInt modPow10(int pow) const
	{
	    if (pow < 0) {
	        cerr<<":< WHAT DO YOU DO WITH NEGATIVE POWER?"<<endl;
			exit(114514);
	    }
	    if (pow == 0) {
	        return BigInt("0");
	    }
	    int len = num.size();
	    if (pow >= len) {
	        return BigInt("0");
	    }
	    return BigInt(num.substr(len - pow));
	}
	friend istream& operator>>(istream& is, BigInt& bi)
	{
	    string str;
	    is >> str;
	    bi = BigInt(str);
	    return is;
	}
};