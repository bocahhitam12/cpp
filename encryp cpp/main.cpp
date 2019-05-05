#include <iostream>
#include <cstring>
#include "AES.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <sstream> 
#include <string>



using namespace std;

void print(unsigned char* state, int len);
void plain(unsigned char* state, int len);

char* readFileBytes(const char *name)
{
    std::ifstream fl(name);
    fl.seekg( 0, std::ios::end );
    size_t len = fl.tellg();
    char *ret = new char[len];
    fl.seekg(0, std::ios::beg); 
    fl.read(ret, len);
    fl.close();
    return ret;
}

int tambahKey = 0;
int hasilKey ;

int main(int argc, char* argv[])
{		
	char menu;

  do {
    printf("\n Enkrip (e) ");
    printf("\n Exit (x) ");
    printf("\n Pilih :  ");
    menu = getche();
    printf("\n");

    switch(menu) {

    case 'e':
    //GET tanggal sebagai KEY
  	time_t rawtime;
  	struct tm * timeinfo;
  	char buffer[80];

  	time (&rawtime);
  	timeinfo = localtime(&rawtime);

  	strftime(buffer,sizeof(buffer),"%d%m%Y",timeinfo);
  	string awal(buffer);
  	//reverse tanggal
	string reverse_str(awal.rbegin(), awal.rend());
	string awalKey;
	awalKey = awal + reverse_str;
	//cout << awalKey;
	//keyBerubah
	stringstream toInt(reverse_str); 
	int x = 0; 
    toInt >> x;
    //cout << "Value of x : " << x; 
	hasilKey = x + tambahKey;
	//cout << "Value of hasilkey : " << hasilKey;
	stringstream ss;
	ss << hasilKey;
	string stri = ss.str();
	//cout << "Value of stri : " << stri;
	string akhirKey = awal + stri;
	cout << akhirKey;
	//ubah ke ASCII
	string str=akhirKey;
	int lengthChar = str.length();
	unsigned char key[lengthChar];
	for(int i = 0; i<str.length(); i++){
		key[i] = str.at(i);
		//printf("%d ", key[i]); 
	}
	//unsigned char input[] = {105, 110, 112, 117, 116};
	unsigned char iv[]    = {49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 49, 50, 51, 52, 53, 54};
	//unsigned char key[]   = {49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 49, 50, 51, 52, 53, 54};
	unsigned char output[100] ={0};
    unsigned char temp[100] = {0};

	//file to input
	char *input = readFileBytes("input.txt");
	printf("isi file : %s\n",input);
	printf("panjang string = %d\n", strlen(input));  
    //padding
    int lenin = strlen(input);
    int pad_length = 16 - (lenin % 16);
    unsigned char input_new[lenin+ pad_length];
    int i;
    for(i=0;i<lenin + pad_length;i++) {
    	if(i < lenin) {
    		input_new[i] = input[i];
		} else {
			input_new[i] = pad_length;
		}
	}
//	unsigned char 
	AESModeOfOperation moo;
	moo.set_key(key);
	moo.set_mode(MODE_CBC);
	moo.set_iv(iv);
    int olen = sizeof input_new;

  	
    memcpy(temp, input_new, sizeof input_new);
	int len = moo.Encrypt(temp, olen, output);
	printf("len = %d\n", len);
    printf("output");
	print(output, len);

	//save to file
  	ofstream myfile;
  	myfile.open ("test.txt");
  	myfile << output;
  	myfile.close();
  	
  	//tambahkey
  	tambahKey++;
  	
	
	printf("\n\nDecrypt----------\n");
	len = moo.Decrypt(output, len, output);
	printf("len = %d\n", len);
    printf("input");
	print(output, len- output[len-1]);
    printf("Plaintext:");
	plain(output, len - output[len-1]);
	//system("PAUSE");
	delete[] input;
	break;
   }
  } while(menu != 'x');

	return 0;
}

void print(unsigned char* state, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
        if ( i%16 == 0) printf("\n");
//		printf("%s%X ",state[i]>15 ? "" : "0", state[i]);
        printf("%d  ", (int)(state[i] & 0xff));
	}
	printf("\n");
}

void plain(unsigned char* state, int len)
{
	int i;
	char temp3[100] = {0};
	for(i=0; i<len; i++)
	{
        if ( i%16 == 0) printf("\n");
//		printf("%s%X ",state[i]>15 ? "" : "0", state[i]);
        temp3[i] = ("%c", (int)(state[i] & 0xff));   
	}
	printf("%s\n", temp3); 
	printf("\n");
}



