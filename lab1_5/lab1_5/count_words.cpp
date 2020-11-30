#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
int main()
{
	float frequency[26] = { 0 };//存放字符以及出现次数,按照字母顺序排列
	string ciphertext;//存放输入的密文
	ciphertext = { "SIC GCBSPNA XPMHACQ JB GPYXSMEPNXIY JR SINS MF SPNBRQJSSJBE JBFMPQNSJMB FPMQ N XMJBS N SM N XMJBS H HY QCNBR MF N XMRRJHAY JBRCGZPC GINBBCA JB RZGI N VNY SINS SIC MPJEJBNA QCRRNEC GNB MBAY HC PCGMTCPCD HY SIC PJEISFZA PCGJXJCBSR SIC XNPSJGJXNBSR JB SIC SPNBRNGSJMB NPC NAJGC SIC MPJEJBNSMP MF SIC QCRRNEC HMH SIC PCGCJTCP NBD MRGNP N XMRRJHAC MXXMBCBS VIM VJRICR SM ENJB ZBNZSIMPJOCD GMBSPMA MF SIC QCRRNEC" };
	//初始化存放的字符
	int len = ciphertext.length();//获取总长度
	int spacenum = 0;
	for (int i=0; i < len; i++)
	{
		if (ciphertext[i] < 65 || ciphertext[i]>122 || ciphertext[i] > 90 && ciphertext[i] < 97)
		{
			spacenum++;
			continue;
		}
		else if(ciphertext[i]>96)
		{
			ciphertext[i] = ciphertext[i] - 'a' + 'A';
		}
		int temp = ciphertext[i] - 'A';
		frequency[temp] +=1;
	}
	for (int j = 0; j < 26; j++)
	{
		char temp = 'A' + j;
		double number = (100 * frequency[j]) / (len - spacenum);
		cout << temp<< ": " << setprecision(2) << fixed <<number<<"%"<< setw(2);
	}
	cout << endl;
	system("pause");
}