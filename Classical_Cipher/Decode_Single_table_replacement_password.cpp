#include<iostream>
using namespace std;
char Alpha[26] = { 'H','K','W','T','X','Y','S','G','B','P','Q','E','J','A','Z','M','L','N','O','F','C','I','D','V','U','R' };
void encryption(char *str)
{
	char plaintext[1000];
	int len = strlen(str);
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
	char ciphertext[1000];//��������
	cout << "������Ҫ���ܵ�����" << endl;
	cin.getline(ciphertext, 1000);//��������
	encryption(ciphertext);//ת��
	system("pause");
}
