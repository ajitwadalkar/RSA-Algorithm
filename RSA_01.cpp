//============================================================================
//Team Members : Ajit Wadalkar
//			   : Sachin Antony
//			   : Shridhish Sundaran
//			   : Likhita Srinivas
//============================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <ctime>
using namespace std;

unsigned long long stringtobearcatii(string stringtoencode)
{
	int strlen = stringtoencode.length();
	for(int i=0;i<strlen;i++)
		{
			if(isalpha(stringtoencode[i]) == 0)
			{
			cout<<"\n"<<stringtoencode<<" contains a non char value, so it will be omitted.\n";
			return 0;
			}
		}

	int bearcatii;
	unsigned long long multiplier;
	multiplier=1;
	unsigned long long encmsg;
	encmsg=0;
	for(int i=(strlen-1); i>=0;i--){
	int ascii_value = stringtoencode[i];

	if(ascii_value>96)
		bearcatii=ascii_value-96;
	else
		bearcatii=ascii_value-64;

	if(i<(strlen-1))
		multiplier=multiplier*27;

	encmsg = encmsg + (bearcatii * multiplier);
	}
	return encmsg;
}

string bearcatiitostring(unsigned long long encmsg)
{
	string decodedmsg;
	while(encmsg>0)
	{
		int bearcatii = encmsg%27;
		encmsg = encmsg/27;
		int asciival = bearcatii + 64;
		decodedmsg = char(asciival) + decodedmsg;
	}
	return decodedmsg;
}

unsigned long long powandmod(unsigned long long x,unsigned long long y,unsigned long long p){
	unsigned long long res = 1;
		x = x % p;
		while (y > 0)
		{
			if (y & 1)
				res = (res*x) % p;
			y = y>>1;
			x = (x*x) % p;
		}
		return res;
}


bool MRprimalitytest(unsigned long long d, unsigned long long n)
{
	unsigned long long a = 2 + rand() % (n - 4);
	unsigned long long x = powandmod(a, d, n);
	if (x == 1 || x == n-1) return true;
	while (d != n-1)
	{
		x = (x * x) % n;
		d = d * 2;
		if (x == 1)	 return false;
		if (x == n-1) return true;
	}

	return false;
}

bool isPrime(unsigned long long n)
{
	int k = 100;
	unsigned long long d = n - 1;
	while (d % 2 == 0){
		d = d/2;}

		for (int i = 0; i < k; i++)
		if (MRprimalitytest(d, n) == false)
			return false;

	return true;
}


unsigned long long EncryptRSA(unsigned long long msg,unsigned long long e,unsigned long long n)
{
	unsigned long long encrmsg = powandmod(msg,e,n);
	return encrmsg;
}

unsigned long long DecryptRSA(unsigned long long msg,unsigned long long d,unsigned long long n)
{
	unsigned long long decmsg = powandmod(msg,d,n);
	return decmsg;
}
unsigned long long getprimenum(long int t)
{

	srand(t);
	int i=0;
	while(i<1)
	{
	unsigned long long num = rand() % 89999 + 10000;
	if (isPrime(num))
	{
		i=1;
		return num;
	}
	}
	return 0;
}
pair<unsigned long long, pair<unsigned long long, unsigned long long> > extendedEuclid(unsigned long long a, unsigned long long b)
{
	unsigned long long s = 1, t = 0;
	unsigned long long sdash = 0, tdash = 1;
	unsigned long long q, r, m, n;
    while (a != 0)
    {
        q = b / a;
        r = b % a;
        m = sdash - q * s;
        n = tdash - q * t;
        sdash = s;
        tdash = t;
        s = m;
        t = n;
        b = a;
        a = r;
    }
    return make_pair(b, make_pair(sdash, tdash));
}
unsigned long long modInverse(unsigned long long a, unsigned long long m)
{
    return (extendedEuclid(a, m).second.first + m) % m;
}

bool RelativelyPrime (unsigned long long n, unsigned long long e) {
	return (n<e) ? RelativelyPrime(e,n) : !(n%e) ? (e==1) : RelativelyPrime (e, n%e);
}

int main() {
	string msgtoencode,decodedmsg, em;
		vector <unsigned long long> bearcatticarray;
		vector <unsigned long long> decbearcatticarray;
		vector <unsigned long long> encarray;
		unsigned long long p, q, n, t, d,e;
		int curtime = (int)time(0);
		p = getprimenum(curtime);
		q = getprimenum(p);;
		n = p*q;
		t = (p-1)*(q-1);
		bool rp;
		do{
			cout<<"Enter a public key above 3 and less than "<<t<<".\n";
			cin>>e;
			rp=RelativelyPrime(n,e);
			d = modInverse(e,t);
			if(d==1)
				{
				rp=0;
				cout<<"\nThe above public key does not have modular inverse. please enter another number.";
				}
			if(rp) cout<<"\nSelected public key is "<<e;
			}while(rp==0);


		cout<<"\n\nFirst Prime is: "<<p<<"\n\nSecond Prime is: "<<q<<"\n\nCalculated n is: "<<n<<"\n\nCalculated Phi is: "<<t<<"\n\nCalculated d is: "<<d;


		cin.ignore();
		cout<<"\n\nEnter a String: ";
			getline(cin,msgtoencode);

		istringstream iss(msgtoencode);
		    string word;
		    while(iss >> word)
		   {
		    	bearcatticarray.push_back(stringtobearcatii(word));
		    }



		    cout<<"\n\nBEARCATTI Message: ";
		    for(unsigned int j=0;j<bearcatticarray.size();j++)
			    {
			    	cout<<bearcatticarray.at(j)<<" ";
			    	encarray.push_back(EncryptRSA(bearcatticarray.at(j),e,n));
			    }

		    cout<<"\n\nRSA Encrypted Message: ";

		    for(unsigned int j=0;j<encarray.size();j++)
		    			    {
		    			    	cout<<encarray.at(j)<<" ";
		    			    }
		    		    cout<<"\n\n";

			for(unsigned int j=0;j<encarray.size();j++)
				{
					decbearcatticarray.push_back(DecryptRSA(encarray.at(j),d,n));
				}

			cout<<"RSA Decrypted Message: ";
				for(unsigned int j=0;j<decbearcatticarray.size();j++)
					{
						cout<<decbearcatticarray.at(j)<<" ";
					}

		    cout<<"\n\nDecrypted Message: ";
	    for(unsigned int j=0;j<decbearcatticarray.size();j++)
		    {
		    	cout<<bearcatiitostring(decbearcatticarray.at(j))<<" ";
		    }
}
