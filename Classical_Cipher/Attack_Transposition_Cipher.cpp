#include<iostream>
#include<vector>
using namespace std;
void encryption(char *str)
{
	char plaintext[1000];
	int len = strlen(str);
	for (int j = 1; j < 26; j++) {
		for (int i = 0; i < len; i++)
		{
			if (str[i] < 65 || str[i]>122 ||str[i]>90&&str[i]<97 )
			{
				plaintext[i] = str[i];
			}
			else if (str[i] < 91)
			{
				char temp = 'A' + (str[i] - 'A' - j+26) % 26;
				plaintext[i] = temp;//������Ϊ��д��ĸʱ
			}
			else if (str[i] > 96)
			{
				char temp = 'a' + (str[i] - 'a' -j+26) % 26;
				plaintext[i] = temp;//��AΪСд��ĸʱ
			}
		}
		plaintext[len] = '\0';//��ֹ����
		printf("%d: %s\n",j, plaintext);//���
	}
}
int main() {
	char ciphertext[1000];//��������
	cout << "������Ҫ���ܵ�����" << endl;
	cin.getline(ciphertext, 1000);//��������
	encryption(ciphertext);//ת��
	system("pause");
}