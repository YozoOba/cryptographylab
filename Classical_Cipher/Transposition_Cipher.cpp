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
		}//其他字符不变
		else if (str[i] < 91)
		{
			char temp = 'A' + (str[i] - 'A'+Key) % 26;
			ciphertext[i] = temp;//当输入为大写字母时
		}
		else if (str[i] > 96)
		{
			char temp = 'a' + (str[i] - 'a'+Key) % 26;
			ciphertext[i] = temp;//当A为小写字母时
		}
	}
	ciphertext[len] = '\0';//防止过烫
	printf("%s\n", ciphertext);//输出
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
		}//其他字符不变
		else if (str[i] < 91)
		{
			char temp = 'A' + (str[i] - 'A' - Key+26) % 26;
			plaintext[i] = temp;//当输入为大写字母时
		}
		else if (str[i] > 96)
		{
			char temp = 'a' + (str[i] - 'a' - Key+26) % 26;
			plaintext[i] = temp;//当A为小写字母时
		}
	}
	plaintext[len] = '\0';//防止过烫
	printf("%s\n", plaintext);//输出
}
	
int main() {
	int mode;
	cout << "请输入0或者1，0为加密，1为解密" << endl;
	cin >> mode;
	cin.ignore();
	if (mode == 0)
	{
		char plaintext[1000];//明文数组
		cout << "输入你要加密的内容" << endl;
		cin.getline(plaintext, 1000);//输入明文
		int Key;
		cout << "请输入你的密钥" << endl;
		cin >> Key;
		Key = Key % 26;
		encryption(plaintext, Key);//转换
	}
	else
		if (mode == 1)
		{
			char ciphertext[1000];//密文数组
			cout << "输入你要解密的内容" << endl;
			cin.getline(ciphertext, 1000);//输入密文
			int Key;
			cout << "请输入你的密钥" << endl;
			cin >> Key;
			Key = Key % 26;
			encryption2(ciphertext, Key);//转换
		}
	system("pause");
	return 0;
}