#include <iostream>
#include<string>
#include<string.h>
using namespace std;


typedef unsigned char byte;
typedef unsigned int bit;
const bit s[4][4] = { 7,12,17,22,5,9,14,20,4,11,16,23,6,10,15,21 };
char fileinput[42960];


class MD5 {
public:
	MD5(const string& message);
	const byte* getDigest();

	string toStr();

private:
	void init(const byte* input, size_t len);


	void transform(const byte block[64]);

	void encode(const bit* input, byte* output, size_t length);

	void getX(const byte* input, bit* output, size_t length);


private:
	bool finished;

	bit state[4];

	bit count[2];

	byte buffer[64];

	byte digest[16];

	static const byte PADDING[64];

	static const char HEX_NUMBERS[16];
};

const byte MD5::PADDING[64] = { 0x80 };
const char MD5::HEX_NUMBERS[16] = {
  '0', '1', '2', '3',
  '4', '5', '6', '7',
  '8', '9', 'a', 'b',
  'c', 'd', 'e', 'f'
};
bit F(bit& x, bit& y, bit& z)
{
	return (x & y) | (~x & z);
}
bit G(bit& x, bit& y, bit& z)
{
	return (x & z) | (y & ~z);
}
bit H(bit& x, bit& y, bit& z)
{
	return x ^ y ^ z;
}
bit I(bit& x, bit& y, bit& z)
{
	return y ^ (x | ~z);
}
bit ROTATELEFT(bit& num, bit& n)
{
	return (num << n) | (num >> (32 - n));
}
void FF(bit& a, bit& b, bit& c, bit& d, bit& x, bit s, bit ac)
{
	a += F(b, c, d) + x + ac;
	a = ROTATELEFT(a, s);
	a += b;
}
void GG(bit& a, bit& b, bit& c, bit& d, bit& x, bit s, bit ac)
{
	a += G(b, c, d) + x + ac;
	a = ROTATELEFT(a, s);
	a += b;
}
void HH(bit& a, bit& b, bit& c, bit& d, bit& x, bit s, bit ac)
{
	a += H(b, c, d) + x + ac;
	a = ROTATELEFT(a, s);
	a += b;
}
void II(bit& a, bit& b, bit& c, bit& d, bit& x, bit s, bit ac)
{
	a += I(b, c, d) + x + ac;
	a = ROTATELEFT(a, s);
	a += b;
}

MD5::MD5(const string& message) {
	finished = false;

	count[0] = count[1] = 0;

	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;

	init((const byte*)message.c_str(), message.length());
}


const byte* MD5::getDigest() {
	if (!finished) {
		finished = true;

		byte bits[8];
		bit oldState[4];
		bit oldCount[2];
		bit index, padLen;

		memcpy(oldState, state, 16);
		memcpy(oldCount, count, 8);

		encode(count, bits, 8);

		index = (bit)((count[0] >> 3) & 0x3f);
		padLen = (index < 56) ? (56 - index) : (120 - index);
		init(PADDING, padLen);

		init(bits, 8);

		encode(state, digest, 16);
		memcpy(state, oldState, 16);
		memcpy(count, oldCount, 8);
	}
	return digest;
}

void MD5::init(const byte* input, size_t len) {

	bit i, index, partLen;

	finished = false;

	index = (bit)((count[0] >> 3) & 0x3f);

	if ((count[0] += ((bit)len << 3)) < ((bit)len << 3)) {
		++count[1];
	}
	count[1] += ((bit)len >> 29);

	partLen = 64 - index;
	if (len >= partLen) {
		memcpy(&buffer[index], input, partLen);
		transform(buffer);
		for (i = partLen; size_t(i) + 63 < len; i += 64) {
			transform(&input[i]);
		}
		index = 0;
	}
	else {
		i = 0;
	}
	memcpy(&buffer[index], &input[i], len - i);
}




void MD5::transform(const byte block[64]) {

	bit a = state[0], b = state[1], c = state[2], d = state[3], x[16];
	getX(block, x, 64);
	/* Round 1 */
	FF(a, b, c, d, x[0], s[0][0], 0xd76aa478);
	FF(d, a, b, c, x[1], s[0][1], 0xe8c7b756);
	FF(c, d, a, b, x[2], s[0][2], 0x242070db);
	FF(b, c, d, a, x[3], s[0][3], 0xc1bdceee);
	FF(a, b, c, d, x[4], s[0][0], 0xf57c0faf);
	FF(d, a, b, c, x[5], s[0][1], 0x4787c62a);
	FF(c, d, a, b, x[6], s[0][2], 0xa8304613);
	FF(b, c, d, a, x[7], s[0][3], 0xfd469501);
	FF(a, b, c, d, x[8], s[0][0], 0x698098d8);
	FF(d, a, b, c, x[9], s[0][1], 0x8b44f7af);
	FF(c, d, a, b, x[10], s[0][2], 0xffff5bb1);
	FF(b, c, d, a, x[11], s[0][3], 0x895cd7be);
	FF(a, b, c, d, x[12], s[0][0], 0x6b901122);
	FF(d, a, b, c, x[13], s[0][1], 0xfd987193);
	FF(c, d, a, b, x[14], s[0][2], 0xa679438e);
	FF(b, c, d, a, x[15], s[0][3], 0x49b40821);

	/* Round 2 */
	GG(a, b, c, d, x[1], s[1][0], 0xf61e2562);
	GG(d, a, b, c, x[6], s[1][1], 0xc040b340);
	GG(c, d, a, b, x[11], s[1][2], 0x265e5a51);
	GG(b, c, d, a, x[0], s[1][3], 0xe9b6c7aa);
	GG(a, b, c, d, x[5], s[1][0], 0xd62f105d);
	GG(d, a, b, c, x[10], s[1][1], 0x2441453);
	GG(c, d, a, b, x[15], s[1][2], 0xd8a1e681);
	GG(b, c, d, a, x[4], s[1][3], 0xe7d3fbc8);
	GG(a, b, c, d, x[9], s[1][0], 0x21e1cde6);
	GG(d, a, b, c, x[14], s[1][1], 0xc33707d6);
	GG(c, d, a, b, x[3], s[1][2], 0xf4d50d87);
	GG(b, c, d, a, x[8], s[1][3], 0x455a14ed);
	GG(a, b, c, d, x[13], s[1][0], 0xa9e3e905);
	GG(d, a, b, c, x[2], s[1][1], 0xfcefa3f8);
	GG(c, d, a, b, x[7], s[1][2], 0x676f02d9);
	GG(b, c, d, a, x[12], s[1][3], 0x8d2a4c8a);

	/* Round 3 */
	HH(a, b, c, d, x[5], s[2][0], 0xfffa3942);
	HH(d, a, b, c, x[8], s[2][1], 0x8771f681);
	HH(c, d, a, b, x[11], s[2][2], 0x6d9d6122);
	HH(b, c, d, a, x[14], s[2][3], 0xfde5380c);
	HH(a, b, c, d, x[1], s[2][0], 0xa4beea44);
	HH(d, a, b, c, x[4], s[2][1], 0x4bdecfa9);
	HH(c, d, a, b, x[7], s[2][2], 0xf6bb4b60);
	HH(b, c, d, a, x[10], s[2][3], 0xbebfbc70);
	HH(a, b, c, d, x[13], s[2][0], 0x289b7ec6);
	HH(d, a, b, c, x[0], s[2][1], 0xeaa127fa);
	HH(c, d, a, b, x[3], s[2][2], 0xd4ef3085);
	HH(b, c, d, a, x[6], s[2][3], 0x4881d05);
	HH(a, b, c, d, x[9], s[2][0], 0xd9d4d039);
	HH(d, a, b, c, x[12], s[2][1], 0xe6db99e5);
	HH(c, d, a, b, x[15], s[2][2], 0x1fa27cf8);
	HH(b, c, d, a, x[2], s[2][3], 0xc4ac5665);

	/* Round 4 */
	II(a, b, c, d, x[0], s[3][0], 0xf4292244);
	II(d, a, b, c, x[7], s[3][1], 0x432aff97);
	II(c, d, a, b, x[14], s[3][2], 0xab9423a7);
	II(b, c, d, a, x[5], s[3][3], 0xfc93a039);
	II(a, b, c, d, x[12], s[3][0], 0x655b59c3);
	II(d, a, b, c, x[3], s[3][1], 0x8f0ccc92);
	II(c, d, a, b, x[10], s[3][2], 0xffeff47d);
	II(b, c, d, a, x[1], s[3][3], 0x85845dd1);
	II(a, b, c, d, x[8], s[3][0], 0x6fa87e4f);
	II(d, a, b, c, x[15], s[3][1], 0xfe2ce6e0);
	II(c, d, a, b, x[6], s[3][2], 0xa3014314);
	II(b, c, d, a, x[13], s[3][3], 0x4e0811a1);
	II(a, b, c, d, x[4], s[3][0], 0xf7537e82);
	II(d, a, b, c, x[11], s[3][1], 0xbd3af235);
	II(c, d, a, b, x[2], s[3][2], 0x2ad7d2bb);
	II(b, c, d, a, x[9], s[3][3], 0xeb86d391);

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}


void MD5::encode(const bit* input, byte* output, size_t length) {

	for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
		output[j] = (byte)(input[i] & 0xff);
		output[j + 1] = (byte)((input[i] >> 8) & 0xff);
		output[j + 2] = (byte)((input[i] >> 16) & 0xff);
		output[j + 3] = (byte)((input[i] >> 24) & 0xff);
	}
}

void MD5::getX(const byte* input, bit* output, size_t length) {
	for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
		output[i] = ((bit)input[j]) | (((bit)input[j + 1]) << 8) |
			(((bit)input[j + 2]) << 16) | (((bit)input[j + 3]) << 24);
	}
}

string MD5::toStr() {
	const byte* digest_ = getDigest();
	string str;
	str.reserve(16 << 1);
	for (size_t i = 0; i < 16; ++i) {
		int t = digest_[i];
		int a = t / 16;
		int b = t % 16;
		str.append(1, HEX_NUMBERS[a]);
		str.append(1, HEX_NUMBERS[b]);
	}
	return str;
}

void printMD5(string& message) {
	string ans32 = MD5(message).toStr();
	cout << "MD5结果为" << endl;
	for (int i = 0; i < 32; i += 2) {
		cout << "0x" << ans32[i] << ans32[i + 1] << " ";
	}
	cout << endl;
}



int main() {
	int choice = 0;
	cout << "MD5加密输入1,输入其他字符退出" << endl;
	cin >> choice;
	cin.ignore();
	while (1) {
		if (choice == 1)
		{
			string str;
			cout << "请输入要加密的字符串：" << endl;
			getline(cin, str);
			printMD5(str);
			cin.ignore();
		}
		else {
			break;
		}
	}
	return 0;
}