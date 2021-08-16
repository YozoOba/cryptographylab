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
				plaintext[i] = temp;//当输入为大写字母时
			}
			else if (str[i] > 96)
			{
				char temp = 'a' + (str[i] - 'a' -j+26) % 26;
				plaintext[i] = temp;//当A为小写字母时
			}
		}
		plaintext[len] = '\0';//防止过烫
		printf("%d: %s\n",j, plaintext);//输出
	}
}
int main() {
	char ciphertext[1000];//密文数组
	cout << "输入你要解密的内容" << endl;
	cin.getline(ciphertext, 1000);//输入密文
	encryption(ciphertext);//转换
	system("pause");
}