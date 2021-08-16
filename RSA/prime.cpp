//#include <iostream>
//#include<fstream>
//#include <string>
//#include<stdlib.h>
//#include"bigint.h"
//#include"prime.h"
//int main()
//{
//	int primeNum[303];
//	ifstream infile("prime2k.txt");
//	int k = 0;
//	while (infile >> primeNum[k])
//		k++;
//	bi temp;
//	int count = 0;
//	bool re = true;
//	bi TWO("2");
//	while (true) {
//		if (re) {
//			temp.random(512);
//			re = false;
//		}
//		temp = temp + TWO;
//		//temp.out();
//		int cur;
//		for (cur = 0; cur < 303; cur++)
//		{
//			if (cur == 301)
//				if ((temp%primeNum[cur]) == 0)
//					break;
//		}
//		if (cur == 303 && isPrime(temp)) {
//			temp.out();
//			//cout << "ÊÇËØÊý£¡" << endl;
//			count++;
//			re = true;
//		}
//		if (count == 2)
//			break;
//	}
//	return 0;
//}
