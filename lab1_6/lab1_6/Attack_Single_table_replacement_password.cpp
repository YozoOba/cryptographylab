#include<iostream>
using namespace std;
char Alpha[26] = { 'N','H','G','D','C','F','E','I','J','K','K','A','Q','B','M','X','K','P','R','S','Z','T','V','K','Y','O' };
void encryption(string str)
{
	char plaintext[1000];
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (str[i] < 65 || str[i]>122 || str[i] > 90 && str[i] < 97)
		{
			plaintext[i] = str[i];
		}//其他字符不变
		else if (str[i] < 91)
		{
			int j = 0;
			for (; j < 26; j++)
			{
				if (str[i] == Alpha[j])
					break;
			}
			char temp = 'A' + j;
			plaintext[i] = temp;//当输入为大写字母时
		}
		else if (str[i] > 96)
		{
			int j = 0;
			for (; j < 26; j++)
			{
				if (str[i] + 'A' - 'a' == Alpha[j])
					break;
			}
			char temp = 'A' + j;
			plaintext[i] = temp;//当A为小写字母时
		}
	}
	plaintext[len] = '\0';//防止过烫
	printf("%s\n", plaintext);//输出
}
int main() {
	string ciphertext = "SIC GCBSPNA XPMHACQ JB GPYXSMEPNXIY JR SINS MF SPNBRQJSSJBE JBFMPQNSJMB FPMQ N XMJBS N SM N XMJBS H HY QCNBR MF N XMRRJHAY JBRCGZPC GINBBCA JB RZGI N VNY SINS SIC MPJEJBNA QCRRNEC GNB MBAY HC PCGMTCPCD HY SIC PJEISFZA PCGJXJCBSR SIC XNPSJGJXNBSR JB SIC SPNBRNGSJMB NPC NAJGC SIC MPJEJBNSMP MF SIC QCRRNEC HMH SIC PCGCJTCP NBD MRGNP N XMRRJHAC MXXMBCBS VIM VJRICR SM ENJB ZBNZSIMPJOCD GMBSPMA MF SIC QCRRNEC";
	encryption(ciphertext);//转换
	system("pause");
}
