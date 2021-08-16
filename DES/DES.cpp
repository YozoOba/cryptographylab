#include<iostream>
#include<string.h>
#include<Windows.h>
using namespace std;
//IP置换矩阵
int IP[64] = {
	58,50,42,34,26,18,10,2, 60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6, 64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9, 1, 59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5, 63,55,47,39,31,23,15,7
};
//扩展矩阵E
int E[48] = {
	32, 1, 2, 3, 4, 5,  4, 5, 6, 7, 8, 9,
	 8, 9,10,11,12,13, 12,13,14,15,16,17,
	16,17,18,19,20,21, 20,21,22,23,24,25,
	24,25,26,27,28,29, 28,29,30,31,32, 1
};
//变换P
int P[32] = {
	16, 7,20,21,29,12,28,17,  1,15,23,26, 5,18,31,10,
	 2, 8,24,14,32,27, 3, 9, 19,13,30, 6,22,11, 4,25
};
//逆IP
int IPr[64] = {
	40, 8,48,16,56,24,64,32,  39, 7,47,15,55,23,63,31,
	38, 6,46,14,54,22,62,30,  37, 5,45,13,53,21,61,29,
	36, 4,44,12,52,20,60,28,  35, 3,43,11,51,19,59,27,
	34, 2,42,10,50,18,58,26,  33, 1,41, 9,49,17,57,25
};
//第一次置换矩阵
int PC1[56] = {
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};
//第二次置换矩阵
int PC2[48] = {
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};
//8个S盒
int S[8][4][16] = {
	//S1
	14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
	//S2
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
	//S3
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
	 // S4
	  7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	 13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	 10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	  3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
	  // S5
	   2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	  14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	   4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	  11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
	  // S6
	  12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	  10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	   9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	   4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
	   // S7
		4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	   13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
		1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
		6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
		// S8
		13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
		 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
		 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
		 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};
//Char 与 Int 的转换
static void charToBit(const char in[], int out[], int bits)
{
	int i, j;
	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 8; i++)
		{
			out[8 * j + 7 - i] = (in[j] >> i) & 1;
		}
	}
};
static void bitToChar(const int in[], char out[], int bits)
{
	int i, j;
	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 8; i++)
		{
			out[j] = out[j] * 2 + in[i + 8 * j];
		}
	}
};
//10 进制 与 2进制 转换
//try 0xA5 = 1010(5) 0101(a)--- False
//try 0xA5 = 1010(a) 0101(5)--- True
//try 0xA5 = 0101(a) 1010(5)--- False
//try 0xA5 = 0101(5) 1010(a)--- False

static void decToBin(const int in[8], int out[64])
{
	//0xA5 = 1010(a) 0101(5)

	for (int i = 0; i < 8; i++)
	{
		//高位和低位
		int high = in[i] / 16;
		int low = in[i] % 16;
		for (int j = 0; j < 4; j++)
		{
			out[8 * i + 7 - j] = low % 2;
			out[8 * i + 3 - j] = high % 2;
			low /= 2;
			high /= 2;
		}
	}

}
static void binToDec(const int in[64], int out[8])
{
	//0xA5 = 1010(a) 0101(5)

	for (int i = 0; i < 8; i++)
	{
		out[i] = 16 * (in[8 * i] * 8 + in[8 * i + 1] * 4 + in[8 * i + 2] * 2 + in[8 * i + 3] * 1) + (in[8 * i + 4] * 8 + in[8 * i + 5] * 4 + in[8 * i + 6] * 2 + in[8 * i + 7] * 1);
	}
}

static void Xor(int *a, int *b, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		a[i] = (a[i] + b[i]) % 2;
	}
};

//填充 0 
static void zeroFill(const int in[], int out[64], int inlen)
{
	int i;
	for (i = 0; i < 64; i++)
	{
		if (i < inlen)
		{
			out[i] = in[i];
		}
		if (i >= inlen)
		{
			out[i] = 0;
		}
	}
}
// IP置换
static void ipChange(const int in[64], int out[64], int table[64])
{
	int i;
	for (i = 0; i < 64; i++)
	{
		out[i] = in[table[i] - 1];
	}
};//
// E置换
static void eChange(const int in[32], int out[48], int table[48])
{
	int i;
	for (i = 0; i < 48; i++)
	{
		out[i] = in[table[i] - 1];
	}
}//
// P置换
static int *pChange(const int in[32], int table[32]) {
	int i;
	static int out[32];
	for (i = 0; i < 32; i++)
	{
		out[i] = in[table[i] - 1];
	}
	return out;
};//
// 逆IP置换
static void iprChange(const int in[64], int out[64], int table[64])
{
	int i;
	for (i = 0; i < 64; i++)
	{
		out[i] = in[table[i] - 1];
	}
};
// PC1置换
static void pc1Change(const int in[64], int out[56], int table[56])
{
	int i;
	for (i = 0; i < 56; i++)
	{
		out[i] = in[table[i] - 1];
	}
};
// PC2置换
static void pc2Change(const int in[56], int out[48], int table[48])
{
	int i;
	for (i = 0; i < 48; i++)
	{
		out[i] = in[table[i] - 1];
	}
};
// S盒置换
static int *sChange(const int in[48], int table[8][4][16])
{
	int i, j;
	int temp[8];
	static int out[32];
	for (i = 0, j = 0; i < 48; i += 6)
	{
		temp[j] = table[j][(in[i]) * 2 + (in[i + 5])][(in[i + 1] * 8) + (in[i + 2] * 4) + (in[i + 3] * 2) + (in[i + 4])];
		j++;

	}
	for (j = 0; j < 8; j++)
	{
		int temp2 = temp[j];
		for (i = 0; i < 4; i++)
		{
			out[4 * j + 3 - i] = temp2 % 2;
			temp2 /= 2;
		}


	}
	return out;
}
// f(ri-1,keyi)
static void func(int in[32], int out[32], int key[48])
{
	int len = 48;
	int temp1[48] = { 0 };

	eChange(in, temp1, E);
	Xor(temp1, key, len);
	int *temp3 = sChange(temp1, S);
	int temp2[32];
	for (int i = 0; i < 32; i++)
	{
		temp2[i] = temp3[i];
	}
	int *p = pChange(temp2, P);
	for (int i = 0; i < 32; i++)
	{
		out[i] = p[i];
	}
}
// 左移位
static void leftMove(const int in[28], int out[28], int leftCount)
{
	int i;
	int len = 28;
	for (i = 0; i < len; i++)
	{
		out[i] = in[(i + leftCount) % len];
	}
}
// 生成16个子密钥
static void getKey(const int in[64], int key[16][48])
{
	int loop1 = 1, loop2 = 2;
	int i, j;
	int c[28], d[28];
	int pc1[56] = { 0 };
	int pc2[16][56] = { 0 };
	int cLeft[16][28] = { 0 };
	int dLeft[16][28] = { 0 };
	pc1Change(in, pc1, PC1);
	for (i = 0; i < 28; i++)
	{
		c[i] = pc1[i];
		d[i] = pc1[i + 28];
	}
	int leftCount = 0;
	for (i = 0; i < 16; i++)
	{
		if (i == 0 || i == 1 || i == 8 || i == 15)
		{
			leftCount += loop1;
			leftMove(c, cLeft[i], leftCount);
			leftMove(d, dLeft[i], leftCount);
		}
		else
		{
			leftCount += loop2;
			leftMove(c, cLeft[i], leftCount);
			leftMove(d, dLeft[i], leftCount);
		}
	}
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 28; j++)
		{
			pc2[i][j] = cLeft[i][j];
			pc2[i][j + 28] = dLeft[i][j];
		}
	}
	for (i = 0; i < 16; i++)
	{
		pc2Change(pc2[i], key[i], PC2);
	}
}

//实现
static void encodeDES(int in[8], int key[8], int out[8])
{
	int ip[64] = { 0 };//用于储存ip置换后的数据	
	int out1[64] = { 0 };
	int out2[64] = { 0 };
	int subkey[16][48];//用于储存16个子密钥
	int bit[64] = { 0 };//用于储存转换为二进制的数据	
	int bitKey[64];//用于储存转换为二进制的密钥
	int left[17][32] = { 0 }, right[17][32] = { 0 };
	decToBin(in, bit);
	ipChange(bit, ip, IP);
	decToBin(key, bitKey);
	getKey(bitKey, subkey);
	//初始ip置换后的数据分成left0和right0
	for (int i = 0; i < 32; i++)
	{
		left[0][i] = ip[i];
		right[0][i] = ip[i + 32];
	}
	//十六轮加密
	for (int j = 1; j < 17; j++)
	{
		for (int k = 0; k < 32; k++)
		{
			left[j][k] = right[j - 1][k];
		}

		func(right[j - 1], right[j], subkey[j - 1]);

		Xor(right[j], left[j - 1], 32);
	}
	// 将left16 和right16 链接在一起
	for (int t = 0; t < 32; t++)
	{
		out1[t] = right[16][t];
		out1[t + 32] = left[16][t];
	}
	iprChange(out1, out2, IPr);
	binToDec(out2, out);
}
static void decodeDES(int in[8], int key[8], int out[8])
{
	int ip[64] = { 0 };//用于储存ip置换后的数据	
	int bit[64] = { 0 };//用于储存转换为二进制的数据	
	int out1[64] = { 0 };
	int out2[64] = { 0 };
	int subkey[16][48];//用于储存16个子密钥
	int bitKey[64];//用于储存转换为二进制的密钥
	int left[17][32] = { 0 }, right[17][32] = { 0 };
	decToBin(in, bit);
	ipChange(bit, ip, IP);
	decToBin(key, bitKey);
	getKey(bitKey, subkey);
	//初始ip置换后的数据分成left0和right0
	for (int i = 0; i < 32; i++)
	{
		left[0][i] = ip[i];
		right[0][i] = ip[i + 32];
	}
	//十六轮解密
	for (int j = 1; j < 16; j++)
	{
		for (int k = 0; k < 32; k++)
		{
			left[j][k] = right[j - 1][k];
		}
		func(right[j - 1], right[j], subkey[16 - j]);
		Xor(right[j], left[j - 1], 32);
	}
	//将 right15 拷贝到 r16
	for (int t = 0; t < 32; t++)
	{
		right[16][t] = right[15][t];

	}
	func(right[15], left[16], subkey[0]);
	Xor(left[16], left[15], 32);
	// 将left16 和right16 链接在一起
	for (int t = 0; t < 32; t++)
	{
		out1[t] = left[16][t];
		out1[t + 32] = right[16][t];
	}
	iprChange(out1, out2, IPr);
	binToDec(out2, out);
}


int main()
{
	int type;
	cout  << "请输入1来进行DES加密，输入2来进行DES解密，输入其他数字退出程序 "<<endl;

	while (true)
	{
		cin >> type;
		if (type == 1)
		{
			int txt[8], key[8], cip[8];
			cout << "当前正在进行加密" << endl << "请输入明文: ";
			for (int i = 0; i < 8; i++)
			{
				cin >> (hex) >> txt[i];
			}
			cout << "请输入你的密钥: ";
			for (int i = 0; i < 8; i++)
			{
				cin >> (hex) >> key[i];
			}
			encodeDES(txt, key, cip);
			cout << "以下是加密后的密文: ";
			for (int i = 0; i < 8; i++)
			{
				cout << "0x";
				if (cip[i] <= 15)
				{
					cout << '0';
				}
				cout << (hex) << cip[i] << " ";
			}
			cout << endl << endl << "请输入1来进行DES加密，输入2来进行DES解密，输入其他数字退出程序 "<<endl;
			continue;
		}

		if (type == 2)
		{
			int txt[8], key[8], cip[8];
			cout << "当前正在进行解密" << endl << "请输入密文: ";
			for (int i = 0; i < 8; i++)
			{
				cin >> (hex) >> txt[i];
			}
			cout << "请输入你的密钥: ";
			for (int i = 0; i < 8; i++)
			{
				cin >> (hex) >> key[i];
			}
			decodeDES(txt, key, cip);
			cout << "以下是解密后的明文: ";
			for (int i = 0; i < 8; i++)
			{
				cout << "0x";
				if (cip[i] <= 15)
				{
					cout << '0';
				}
				cout << (hex) << cip[i] << " ";
			}
			cout << endl << endl << "请输入1来进行DES加密，输入2来进行DES解密，输入其他数字退出程序 ";
			continue;
		}
		if (type >2||type<1)
		{
			cout << endl << "即将在3秒后退出程序";
			Sleep(3000);
			break;
		}
	}
	system("pause");


}
