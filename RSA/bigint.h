#pragma once
#include<iostream>
#include<math.h>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
const int max = 1025;
class bi
{
private:
	bool num[max];
public:
	bool flag;
	bi()
	{
		int i;
		for (i = 0; i < max; i++)
		{
			num[i] = 0;
		}
		flag = 0;
	}
	bi(int in)
	{
		if (in >= 0)flag = 0;
		else flag = 1;
		int i = 0;
		while (in)
		{
			num[i] = in % 2;
			in = in / 2;
			i++;
		}
		for (; i < max; i++)
		{
			num[i] = 0;
		}
	}
	bi(string in)
	{
		int i, j = 0;
		int temp;
		for (i = 0; i < max; i++) {
			num[i] = 0;
		}
		for (i = in.length() - 1; i >= 0; i--) {
			if (in[i] >= 'a'&&in[i] <= 'f') {
				temp = in[i] - 'a' + 10;
			}
			else {
				if (in[i] >= 'A'&&in[i] <= 'F') {
					temp = in[i] - 'A' + 10;
				}
				else {
					temp = in[i] - '0';
				}
			}
			if (temp / 8) {
				num[4 * j + 3] = 1;
			}
			if ((temp % 8) / 4) {
				num[4 * j + 2] = 1;
			}
			if ((temp % 4) / 2) {
				num[4 * j + 1] = 1;
			}
			if (temp % 2) {
				num[4 * j] = 1;
			}
			j++;
		}
		flag = 0;
	}
	void random(int n)
	{
		bi temp;
		srand((int)time(0));
		for (int i = 0; i < n; i++)
		{
			int x = rand() % 2;
			if (x == 1)
				num[i] = true;
			else
				num[i] = false;
		}
		for (int i = max - 1; i >= n; i--)
		{
			num[i] = false;
		}
		num[n - 1] = true;
		num[0] = true;
	}
	friend bi operator+(bi a, bi b)
	{
		bi result;
		int i;
		bool temp = 0;
		if (a.flag == b.flag) {
			for (i = 0; i < max; i++) {
				if (a[i] == 0 && b[i] == 0 && temp == 0) {
					result.make(i, 0);
					temp = 0;
				}
				else {
					if (a[i] == 1 && b[i] == 0 && temp == 0 ||
						a[i] == 0 && b[i] == 1 && temp == 0 ||
						a[i] == 0 && b[i] == 0 && temp == 1) {
						temp = 0;
						result.make(i, 1);
					}
					else {
						if (a[i] == 1 && b[i] == 1 && temp == 0 ||
							a[i] == 0 && b[i] == 1 && temp == 1 ||
							a[i] == 1 && b[i] == 0 && temp == 1) {
							temp = 1;
							result.make(i, 0);
						}
						else {
							if (a[i] == 1 && b[i] == 1 && temp == 1) {
								temp = 1;
								result.make(i, 1);
							}
						}
					}
				}
			}
			result.flag = a.flag;
		}
		if (a.flag == 0 && b.flag == 1) {
			b.Num_Not();
			return a - b;
		}
		if (a.flag == 1 && b.flag == 0) {
			a.Num_Not();
			return b - a;
		}
		if (temp) {
			cout << "Overflow" << endl;
		}
		return result;
	}
	friend bi operator-(bi a, bi b)
	{
		bi result;
		int i;
		bool temp = 0;
		if (a.flag == b.flag) {
			if (!(b.abs() > a.abs())) {
				for (i = 0; i < max; i++) {
					if (a[i] == 0 && b[i] == 0 && temp == 0 ||
						a[i] == 1 && b[i] == 0 && temp == 1 ||
						a[i] == 1 && b[i] == 1 && temp == 0) {
						result.make(i, 0);
						temp = 0;
					}
					else {
						if (a[i] == 0 && b[i] == 0 && temp == 1 ||
							a[i] == 0 && b[i] == 1 && temp == 0 ||
							a[i] == 1 && b[i] == 1 && temp == 1) {
							temp = 1;
							result.make(i, 1);
						}
						else {
							if (a[i] == 0 && b[i] == 1 && temp == 1) {
								temp = 1;
								result.make(i, 0);
							}
							else {
								if (a[i] == 1 && b[i] == 0 && temp == 0) {
									temp = 0;
									result.make(i, 1);
								}
							}
						}
					}
				}
				result.flag = a.flag;
			}
			else {
				result = (b - a);
				result.flag = !a.flag;
			}
		}
		if (a.flag == 0 && b.flag == 1) {
			b.Num_Not();
			return a + b;
		}
		if (a.flag == 1 && b.flag == 0) {
			b.Num_Not();
			return a + b;
		}
		if (temp) {
			cout << "Overflow" << endl;
		}
		return result;
	}
	friend bi operator*(bi a, bi b)
	{
		bi result;
		int i;
		bool first = true;
		for (i = 0; i < max; i++) {
			if (b[i] == 1) {
				result = result + a;
			}
			a.leftMove(1);
		}
		if (a.flag == b.flag) {
			result.flag = 0;
		}
		else {
			result.flag = 1;
		}
		return result;
	}
	friend bi operator/(bi a, bi b)
	{
		bi count("0");
		if (a.flag == b.flag) {
			count.flag = 0;
		}
		else {
			count.flag = 1;
		}
		int i, j;
		bi tempA = a, tempB = b, ZERO("0");
		if (ZERO > tempA) {
			tempA.Num_Not();
		}
		if (ZERO > tempB) {
			tempB.Num_Not();
		}
		for (j = max - 1; j >= 0; j--) {
			if (b[j]) {
				break;
			}
		}
		bi tempBB = tempB;
		for (i = max - j - 1; i >= 0; i--) {
			tempBB = tempB;
			tempBB.leftMove(i);
			if (!(tempBB > tempA)) {
				count.make(i, 1);
				tempA = tempA - tempBB;
			}
		}
		return count;
	}
	friend bi operator%(bi a, bi b)
	{
		bi result;
		result = a - (a / b)*b;
		return result;
	}
	friend bool operator>(bi a, bi b)
	{
		bool Bigger = 0;
		int i;
		if (a.flag == 0 && b.flag == 1) {
			Bigger = true;
			bool allZERO = true;
			for (i = 0; i < max; i++) {
				if (a[i] != 0 || b[i] != 0) {
					allZERO = false;
				}
			}
			if (allZERO) {
				Bigger = false;
			}
		}
		else {
			if (a.flag == 1 && b.flag == 0) {
				Bigger = false;
				bool allZERO = true;
				for (i = 0; i < max; i++) {
					if (a[i] != 0 || b[i] != 0) {
						allZERO = false;
					}
				}
				if (allZERO) {
					Bigger = false;
				}
			}
			else {
				if (a.flag == 0 && b.flag == 0) {
					for (i = max - 1; i >= 0; i--) {
						if (a[i] == 1 && b[i] == 0) {
							Bigger = true;
							break;
						}
						if (a[i] == 0 && b[i] == 1) {
							Bigger = false;
							break;
						}
					}
				}
				else {
					for (i = max - 1; i >= 0; i--) {
						if (a[i] == 1 && b[i] == 0) {
							Bigger = false;
							break;
						}
						if (a[i] == 0 && b[i] == 1) {
							Bigger = true;
							break;
						}
					}
				}
			}
		}
		return Bigger;
	}
	friend bool operator==(bi a, bi b)
	{
		int i;
		bool same = true;
		if (a.flag != b.flag) {
			same = false;
		}
		for (i = 0; i < max; i++) {
			if (a[i] != b[i]) {
				same = false;
				break;
			}
		}
		return same;
	}
	friend bool operator!=(bi a, bi b)
	{
		int i;
		if (a.flag != b.flag) {
			return true;
		}
		for (i = 0; i < max; i++) {
			if (a[i] != b[i]) {
				return true;
			}
		}
		return false;
	}
	bi modMult(bi a, bi b, bi c)
	{
		bi result;
		int i;
		bool first = true;
		for (i = 0; i < max; i++) {
			if (b[i] == 1) {
				result = result + a;
				while (result > c)
					result = result - c;
			}
			a.leftMove(1);
			while (a > c)
				a = a - c;
		}
		if (a.flag == b.flag) {
			result.flag = 0;
		}
		else {
			result.flag = 1;
		}
		return result;
	}
	bi exp(bi x, bi y)
	{
		bi d("1");
		int i = max - 1;
		while (!x[i]) {
			i--;
		}
		int j;
		for (j = i; j >= 0; j--) {
			d = modMult(d, d, y);
			if (x[j]) {
				d = modMult(d, (*this), y);
			}
		}
		return d;
	}
	bi inv(bi x)
	{
		bi ZERO("0"), ONE("1");
		bi x1 = ONE, x2 = ZERO, x3 = x;
		bi y1 = ZERO, y2 = ONE, y3 = (*this);
		bi t1, t2, t3;
		if (y3 == ONE) {
			return ONE;
		}
		bi q;
		bi g;
		do {
			q = x3 / y3;
			t1 = x1 - q * y1;
			t2 = x2 - q * y2;
			t3 = x3 - q * y3;
			x1 = y1;
			x2 = y2;
			x3 = y3;
			y1 = t1;
			y2 = t2;
			y3 = t3;
		} while (!(y3 == ONE));
		g = y2;
		if (!(g > ZERO))
			g = x + g;
		return g;
	}
	void leftMove(int i)
	{
		int k;
		for (k = max - 1; k > i - 1; k--) {
			num[k] = num[k - i];
		}
		for (k = 0; k < i; k++) {
			num[k] = 0;
		}
	}
	bool operator[](int i)
	{
		return num[i];
	}
	void make(int i, bool a)
	{
		num[i] = a;
	}
	void out()
	{
		if (this->flag == 1) {
			cout << '-';
		}
		char result[max];
		int i;
		for (i = max - 1; i >= 0; i--) {
			if ((*this)[i] == 1) {
				break;
			}
		}
		i++;
		int k;
		int length = 0;
		switch (i % 4) {
		case 1:
			length = i + 3;
			break;
		case 2:
			length = i + 2;
			break;
		case 3:
			length = i + 1;
			break;
		case 0:
			length = i;
			break;
		}
		for (k = 0; k < length; k = k + 4) {
			if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
				result[k / 4] = '0';
			}
			if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
				result[k / 4] = '1';
			}
			if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
				result[k / 4] = '2';
			}
			if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
				result[k / 4] = '3';
			}
			if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
				result[k / 4] = '4';
			}
			if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
				result[k / 4] = '5';
			}
			if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
				result[k / 4] = '6';
			}
			if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
				result[k / 4] = '7';
			}
			if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
				result[k / 4] = '8';
			}
			if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
				result[k / 4] = '9';
			}
			if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
				result[k / 4] = 'A';
			}
			if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
				result[k / 4] = 'B';
			}
			if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
				result[k / 4] = 'C';
			}
			if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
				result[k / 4] = 'D';
			}
			if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
				result[k / 4] = 'E';
			}
			if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
				result[k / 4] = 'F';
			}
		}
		if (i == 0) {
			cout << '0' << endl;
		}
		else {
			for (i = (k / 4) - 1; i >= 0; i--) {
				cout << result[i];
			}
			cout << endl;
		}
	}
	void Num_Not()
	{
		this->flag = !(this->flag);
	}
	bi abs()
	{
		bi temp = (*this);
		if (temp.flag == 0) {
			return temp;
		}
		else {
			temp.Num_Not();
			return temp;
		}
	}
};