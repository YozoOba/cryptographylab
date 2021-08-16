#include<iostream>
#include<vector>
using namespace std;
void encryption(char *str,int Key)
{
	char ciphertext[1000];
	int len = strlen(str);
	for (int i = 0; i <len; i++)
	{
		if (str[i] < 65 || str[i]>122 || str[i] > 90 && str[i] < 97)
		{
			ciphertext[i] = str[i];
		}//�����ַ�����
		else if (str[i] < 91)
		{
			char temp = 'A' + (str[i] - 'A'+Key) % 26;
			ciphertext[i] = temp;//������Ϊ��д��ĸʱ
		}
		else if (str[i] > 96)
		{
			char temp = 'a' + (str[i] - 'a'+Key) % 26;
			ciphertext[i] = temp;//��AΪСд��ĸʱ
		}
	}
	ciphertext[len] = '\0';//��ֹ����
	printf("%s\n", ciphertext);//���
}
void encryption2(char *str, int Key)
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
			char temp = 'A' + (str[i] - 'A' - Key+26) % 26;
			plaintext[i] = temp;//������Ϊ��д��ĸʱ
		}
		else if (str[i] > 96)
		{
			char temp = 'a' + (str[i] - 'a' - Key+26) % 26;
			plaintext[i] = temp;//��AΪСд��ĸʱ
		}
	}
	plaintext[len] = '\0';//��ֹ����
	printf("%s\n", plaintext);//���
}
	
int main() {
	int mode;
	cout << "������0����1��0Ϊ���ܣ�1Ϊ����" << endl;
	cin >> mode;
	cin.ignore();
	if (mode == 0)
	{
		char plaintext[1000];//��������
		cout << "������Ҫ���ܵ�����" << endl;
		cin.getline(plaintext, 1000);//��������
		int Key;
		cout << "�����������Կ" << endl;
		cin >> Key;
		Key = Key % 26;
		encryption(plaintext, Key);//ת��
	}
	else
		if (mode == 1)
		{
			char ciphertext[1000];//��������
			cout << "������Ҫ���ܵ�����" << endl;
			cin.getline(ciphertext, 1000);//��������
			int Key;
			cout << "�����������Կ" << endl;
			cin >> Key;
			Key = Key % 26;
			encryption2(ciphertext, Key);//ת��
		}
	system("pause");
	return 0;
}