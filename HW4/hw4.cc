#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <unistd.h>
#include <sstream>

using namespace std;

int countBits(long i){
     int numBits;
     (fmod(log2(abs(i))+5,8)==0 && i<0) ? numBits = (long) log2(abs(i))+1 : numBits = (long) log2(abs(i))+2;
     if(i == -pow(2, 63)) numBits =  64;
     return numBits;
}
void serializeNum(long input, std::ostream &stream){
	long addBytes = (countBits(input)+3)/8; //additional bytes
	long first = (0xf0 & (addBytes<<4))|(0x0f & (input>>((8*addBytes)))); //first byte with length, first four bits of number
    if(addBytes==8) (input<0) ? first = 0x0f | (addBytes<<4) : first = 0xff &( addBytes<<4);
	stream<<char(first);
	for(int i = addBytes-1; i>=0; i--){
		long print = input>>(8*i); //iterates through number and prints additional bytes
		stream<<char(print&0xff);
	}
}
long unserializeNum(std::istream &in){
     unsigned long c = in.get(); //c is first byte (length and first four bits)
     long addBytes = c>>4; //number of additional bytes from first four bits of first byte
     long val = (c&0x0F)<<((addBytes*8)); //result value, started with the bottom four bits of first byte (shifted appropriate length)
     if(addBytes==8) val = 0; //in case of big numbers, avoid overflow
     if(addBytes>8) throw "Item of length " + to_string(addBytes) + " is too big to store."s;
     for(int i =addBytes-1;i>=0;i--){
         long num;
         if((num = in.get())==-1) throw "End of stream reached before length of " + to_string(addBytes) + " attained."s;
         val |= num<<(8*i); //iterates through bytes and masks them onto result val in appropriate place
     }
     long topBit =(8*addBytes)+3; //position of top bit
     if(topBit>63) topBit =63;
     if(val>>topBit) val |= ~((1L<<topBit)-1); //sign extend if negative
     return val;
}
//end of helper functions

void serialize(bool b, std::ostream &stream){
	(b) ? stream<<'t': stream<<'f';
}
void serialize(short s, std::ostream &stream){
	stream<<'s';
	serializeNum(s, stream);
}
void serialize(int i, std::ostream &stream){
    stream<<'i';
	serializeNum(i, stream);
}
void serialize(long l, std::ostream &stream){
    stream<<'l';
	serializeNum(l, stream);
}
void serialize(char ch, std::ostream &stream){
	stream<<'c'<< ch;
}
void serialize(const std::string &str, std::ostream &stream){
	stream << 'S';
    serializeNum(str.length(), stream);
    for(char ch: str) stream << ch; 
}
void unserialize(std::istream &in, bool &b){
	char tag = in.get();
	//cout<<tag;
	if(tag=='t') b=true;
	else if(tag=='f') b=false;
	else throw ("Item tagged \'"s +tag +"\' not actually a boolean, but nice try."s);
}
void unserialize(std::istream &in, short &s){
    char tag = in.get();
    if(tag!='s') throw "Item tagged \'"s +tag +"\' not actually a short, but nice try."s; 
    long val = unserializeNum(in);
	if(val>32767 || val<-32768) throw "Item is too big for a short."s;
	s = val;
}
void unserialize(std::istream &in, int &i){
    char tag = in.get();
    if(tag!='i') throw "Item tagged \'"s +tag +"\' not actually an int, but nice try."s; 
    long val = unserializeNum(in);
	if(val>2147483647 || val<-2147483648) throw "Item is too big for an int."s;
	i = val;
}
void unserialize(std::istream &in, long &l){
    char tag = in.get();
    if(tag!='l') throw "Item tagged \'"s +tag +"\' not actually a long, but nice try."s; 
	l = unserializeNum(in);
}
void unserialize(std::istream &in, char &ch){
	char tag = in.get();
    if(tag!='c') throw "Item tagged \'"s +tag +"\' not actually a char, but nice try."s; 
    ch = in.get();
}
void unserialize(std::istream &in, std::string &str){
    char tag = in.get();
    if(tag!='S') throw "Item tagged \'"s +tag +"\' not actually a string, but nice try."s; 
    long length = unserializeNum(in);
	str = "";
	for(int i = 0; i<length; i++){
		char ch;
		if((ch=in.get())!=-1) str+=ch;
		else throw "End of stream reached before length of "s + to_string(length) + " attained."s; 
	}
}
