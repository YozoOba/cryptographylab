#include <iostream>
#include<fstream>
#include <string>
#include<stdlib.h>
#include"bigint.h"
#include"prime.h"
using namespace std;
class RSA
{
private:
	bi p, q, d, pi;
public:
	bi e, n; 
	bi m, c;
	RSA(bi a, bi b)
	{
		bi one("1");
		p = a;
		q = b;
		n = p * q;
		pi = (p - one)*(q - one);
		bi curr("10001");
		e = curr;
		d = e.inv(pi);
	}
	void encode(bi m1)
	{
		m = m1;
		c = m.exp(e, n);
	}
	void decode(bi c1)
	{
		c = c1;
		m = c.exp(d, n);
	}
	void show(int i)
	{
		if (i == 1) {
			cout << "公钥n：" << endl;
			n.out();
			cout << "私钥d：" << endl;
			d.out();
			cout << "公钥e：" << endl;
			e.out();
			cout << "明文：" << endl;
			m.out();
		}
		else {
			cout << "公钥n：" << endl;
			n.out();
			cout << "私钥d：" << endl;
			d.out();
			cout << "公钥e：" << endl;
			e.out();
			cout << "密文：" << endl;
			c.out();
		}
	}
};
int main()
{
	cout << "Input 0-2: 0 for exit,1 for encode ,2 for decode  ";
	int i; cin >> i;
	while (i != 0)
	{
		cin.get();
		if (i == 1) {
			string p;
			string q;
			p = "C9ED9379CE1D0B7C61B0546E710E263438843F527A00D2445EA3AD013AC5D8196D7A80AC2FB174C17ED07EFA0F55227608170E83E4E888BDD1CAEF174B944EE7";
			q = "920377EB5CF41784399C520DFFBAB3101337FE0818CCE444D4B356525400909AF0A0C15F7F305E062480CF7C73AF0C6C41EC4C3E0F0DA600C5E5FB93CC257D71";
			cout << "请输入明文：" << endl;
			string m;
			getline(cin, m);
			RSA rsa(p, q);
			rsa.encode(m);
			rsa.show(2);
		}
		if (i == 2) {
			string p;
			string q;
			p = "C9ED9379CE1D0B7C61B0546E710E263438843F527A00D2445EA3AD013AC5D8196D7A80AC2FB174C17ED07EFA0F55227608170E83E4E888BDD1CAEF174B944EE7";
			q = "920377EB5CF41784399C520DFFBAB3101337FE0818CCE444D4B356525400909AF0A0C15F7F305E062480CF7C73AF0C6C41EC4C3E0F0DA600C5E5FB93CC257D71";
			cout << "请输入密文(hex)：" << endl;
			string c;
			getline(cin, c);
			RSA rsa(p, q);
			rsa.decode(c);
			rsa.show(1);
		}

		cout << "请输入0-2：" << endl;
		cin >> i;
	}
	system("pause");
	return 0;
}