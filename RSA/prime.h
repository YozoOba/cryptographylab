#pragma once
#include<fstream>
#include"bigint.h"
using namespace std;

bool isPrime(bi a)
{
	bi temp = a;
	bi n = a;
	n.make(0, 0);//n=n-1
	ifstream infile("prime10w.txt");
	int prime;
	const bi ONE(1);
	int mark = 511;
	for (int i = 0; i < 5; i++)
	{
		int find = (int(rand()) % 9592);
		infile.seekg(find, ios::beg);
		infile >> prime;
		bi pNum(prime);
		bi d(1);
		for (int j = mark; j > -1; j--)
		{
			bi x;
			x = d;
			d = (d*d) % temp;
			if ((d == ONE) && (x != ONE) && (x != n))
				return false;
			if (n[j] == true)
				d = (d * pNum) % temp;
		}
		if (d != ONE)
			return false;
	}
	infile.close();
	return true;
}