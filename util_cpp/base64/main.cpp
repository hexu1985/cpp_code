#include "ZBase64.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;
int main(int argc, char * argv[])
{
	if(3 != argc)
	{
		cout<<"Usage:"<<endl;
		cout<<"Encode, b64 1 string2Encode"<<endl;
		cout<<"Decode, b64 2 string2Decode"<<endl;
		
		return 1;
	}
	
	ZBase64	b64;
	int bType = 0;
	bType = atoi((const char*)argv[1]);
	int dataLen = strlen((const char*)argv[2]);
	if(1 == bType)
	{
		cout<<"Raw:"<<argv[2]<<endl;
		cout<<"RawLen:"<<dataLen<<endl;
		string str = b64.Encode((const unsigned char*)argv[2], dataLen);
		
		cout<<"Encode:"<<str<<endl;
		cout<<"EncodeLen:"<<str.length()<<endl;
	}
	else if(2 ==  bType)
	{
		cout<<"Raw:"<<argv[2]<<endl;
		cout<<"RawLen:"<<dataLen<<endl;
		int iOutLen = 0;
		string str = b64.Decode((const char*)argv[2], dataLen, iOutLen);
		
		cout<<"Decode:"<<str<<endl;
		cout<<"DecodeLen:"<<iOutLen<<endl;
	}
	else
	{
		cout<<"Usage:"<<endl;
		cout<<"Encode, b64 1 string2Encode"<<endl;
		cout<<"Decode, b64 2 string2Decode"<<endl;
		
		return 2;
	}
	
	
	return 0;
}
