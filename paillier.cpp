#include <iostream>
#include <algorithm>
#include <cmath>
#include <time.h>

using namespace std;

//Use the Wikipedia page to help in making-out variables
//https://en.wikipedia.org/wiki/Paillier_cryptosystem

unsigned long long int invMod(unsigned long long int, unsigned long long int);//Modular Multiplicative Inverse
unsigned long long int gcd(unsigned long long int, unsigned long long int);//GCD function
unsigned long long int lcm(unsigned long long int, unsigned long long int);//LCM function
unsigned long long int coprime(unsigned long long int);//Random Co-Prime Generator
bool const prime(int const);
unsigned long long int pow_mod(unsigned long long int,
	unsigned long long int, unsigned long long int);
unsigned long long int mul_mod(unsigned long long int,
	unsigned long long int, unsigned long long int);

//Encryption Scheme for Paillier
class Paillier {
public:
	Paillier() {
		key(p, q, prKey, pubKey);
	}

	void const getKey();//Get keys (Not needed but used to check for correctness)
	unsigned long long int encrypt(unsigned long long int);//Encryption Algo
	unsigned long long int decrypt(unsigned long long int);//Decryption Algo
	unsigned long long int pubKey[2];//pubKey = (n,g)
private:
	unsigned long long int p, q;
	unsigned long long int prKey[2];//prKey = (lambda,mu)
	void key(unsigned long long int&, unsigned long long int&, unsigned long long int*, unsigned long long int*);
	unsigned long long int const L(unsigned long long int const, 
		unsigned long long int const);
};

void main() {
	srand(time(NULL));
	Paillier pal;

	pal.getKey();
	cout << pal.encrypt(5) << endl;//To verify Encryption works
	cout << pal.decrypt(pal.encrypt(5));//To verify Decryption works
}

//The definitions for the prototyped functions
unsigned long long int invMod(unsigned long long int a, 
	unsigned long long int m) {
	a = a % m;
	for (unsigned long long int x = 1; x < m; x++) {
		if ((a*x) % m == 1)
			return x;
	}
}
unsigned long long int gcd(unsigned long long int a, unsigned long long int b) {
	if (a == 0)
		return b;
	return gcd(b % a, a);
}

unsigned long long int lcm(unsigned long long int a, unsigned long long int b) {
	return (a*b) / gcd(a, b);
}

unsigned long long int coprime(unsigned long long int n) {
	unsigned long long int g;
	do {
		g = rand() % (n);
	} while (gcd(g, n) != 1);
	return g;
}

bool const prime(int const n) {
	if (n <= 1) return false;
	if (n <= 3) return true;

	if (n % 2 == 0 || n % 3 == 0) return false;

	int i = 5;
	while (i * i <= n) {
		if (n % i == 0 || n % (i + 2) == 0) { return false; };
			i = i + 6;
	}
	return true;
}

unsigned long long int const Paillier::L(unsigned long long int const g, 
	unsigned long long int const xi) {
	return (unsigned long long int)(pow_mod(g, xi, pubKey[0]*pubKey[0]) - 1) / pubKey[0];
}

unsigned long long int pow_mod(unsigned long long int x,
	unsigned long long int y, unsigned long long int p) {
	unsigned long long int res = 1;
	x = x % p;

	while (y > 0) {
		if (y & 1)
			res = (res * x) % p;

		y = y >> 1;
		x = (x * x) % p;
	}
	return res;
}

unsigned long long int mul_mod(unsigned long long int a,
	unsigned long long int b, unsigned long long int m) {
	long long res = 0;
	a %= m;

	while (b)
	{
		if (b & 1)
			res = (res + a) % m;
		a = (2 * a) % m;

		b >>= 1;
	}
	return res;
}

void Paillier::key(unsigned long long int& p, unsigned long long int& q, 
	unsigned long long int* prKey, unsigned long long int* pubKey) {
	//We need a random p and q with a strong definition of being prime
	do {
		p = rand() % (unsigned long long int)(pow(2, 3)); //Wish it was 64 bits instead of 3
		q = rand() % (unsigned long long int)(pow(2, 3));
	} while (prime(p) == false || prime(q) == false || p == q);

	cout << "p =" << p << " q = " << q << endl;

	unsigned long long int n = p * q;
	pubKey[0] = n;
	unsigned long long int xi = lcm(p - 1, q - 1);//xi is same as lambda

	unsigned long long int g = coprime(n*n);
	do {
		g = coprime(n*n);
	} while (gcd(L(g, xi), n) != 1);
	
	cout << L(g, xi) << endl;
	prKey[1] = invMod(L(g,xi),n);
	//Assignments of values to public/private keys
	pubKey[1] = g;
	prKey[0] = xi;
}

unsigned long long int Paillier::encrypt(unsigned long long int m) {
	unsigned long long int r = coprime(pubKey[0]);

	unsigned long long int c1 = pow(pubKey[1], m);
	unsigned long long int c2 = pow(r, pubKey[0]);

	return mul_mod(c1,c2, pubKey[0]*pubKey[0]);
	//Problem when g^m,r^n > 2^64 which happens frequently
}

unsigned long long int Paillier::decrypt(unsigned long long int c) {
	unsigned long long int l = L(c, prKey[0]);
	return mul_mod(l,prKey[1], pubKey[0]);
}

void const Paillier::getKey() {
	cout << "n = " << pubKey[0] << endl << "g = " << pubKey[1] << endl;
	cout << "lamb = " << prKey[0] << endl << "mu = " << prKey[1] << endl;
}