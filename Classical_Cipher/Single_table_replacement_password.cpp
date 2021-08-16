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
		}//其他字符不变
		else if (str[i] < 91)
		{
			int temp = (str[i] - 'A' ) % 26;
			ciphertext[i] = Alpha[temp];//当输入为大写字母时
		}
		else if (str[i] > 96)
		{
			int temp = (str[i] - 'a') % 26;
			ciphertext[i] = Alpha[temp];//当A为小写字母时
		}
	}
	ciphertext[len] = '\0';//防止过烫
	printf("%s\n", ciphertext);//输出
}
int main() {
	char plaintext[1000];//明文数组
	cout << "请输入要加密的明文" << endl;
	cin.getline(plaintext, 1000);//输入明文
	encryption(plaintext);//转换
	system("pause");
}