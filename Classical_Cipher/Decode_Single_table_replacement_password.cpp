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
	char ciphertext[1000];//密文数组
	cout << "请输入要解密的密文" << endl;
	cin.getline(ciphertext, 1000);//输入密文
	encryption(ciphertext);//转换
	system("pause");
}
