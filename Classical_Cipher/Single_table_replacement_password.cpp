#include<iostream>
using namespace std;
char Alpha[26] = {'H','K','W','T','X','Y','S','G','B','P','Q','E','J','A','Z','M','L','N','O','F','C','I','D','V','U','R' };
void encryption(char *str)
{
	char ciphertext[1000];
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] < 65 || str[i]>122 || str[i] > 90 && str[i] < 97)
		{
			ciphertext[i] = str[i];
		}//�����ַ�����
		else if (str[i] < 91)
		{
			int temp = (str[i] - 'A' ) % 26;
			ciphertext[i] = Alpha[temp];//������Ϊ��д��ĸʱ
		}
		else if (str[i] > 96)
		{
			int temp = (str[i] - 'a') % 26;
			ciphertext[i] = Alpha[temp];//��AΪСд��ĸʱ
		}
	}
	ciphertext[len] = '\0';//��ֹ����
	printf("%s\n", ciphertext);//���
}
int main() {
	char plaintext[1000];//��������
	cout << "������Ҫ���ܵ�����" << endl;
	cin.getline(plaintext, 1000);//��������
	encryption(plaintext);//ת��
	system("pause");
}