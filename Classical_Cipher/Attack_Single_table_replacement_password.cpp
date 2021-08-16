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
		}//�����ַ�����
		else if (str[i] < 91)
		{
			int j = 0;
			for (; j < 26; j++)
			{
				if (str[i] == Alpha[j])
					break;
			}
			char temp = 'A' + j;
			plaintext[i] = temp;//������Ϊ��д��ĸʱ
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
			plaintext[i] = temp;//��AΪСд��ĸʱ
		}
	}
	plaintext[len] = '\0';//��ֹ����
	printf("%s\n", plaintext);//���
}
int main() {
	string ciphertext = "SIC GCBSPNA XPMHACQ JB GPYXSMEPNXIY JR SINS MF SPNBRQJSSJBE JBFMPQNSJMB FPMQ N XMJBS N SM N XMJBS H HY QCNBR MF N XMRRJHAY JBRCGZPC GINBBCA JB RZGI N VNY SINS SIC MPJEJBNA QCRRNEC GNB MBAY HC PCGMTCPCD HY SIC PJEISFZA PCGJXJCBSR SIC XNPSJGJXNBSR JB SIC SPNBRNGSJMB NPC NAJGC SIC MPJEJBNSMP MF SIC QCRRNEC HMH SIC PCGCJTCP NBD MRGNP N XMRRJHAC MXXMBCBS VIM VJRICR SM ENJB ZBNZSIMPJOCD GMBSPMA MF SIC QCRRNEC";
	encryption(ciphertext);//ת��
	system("pause");
}
