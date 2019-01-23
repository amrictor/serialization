#include "Serial.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <unistd.h>
#include <sstream>
#include <type_traits>

using namespace std;

Serial::Serial() : contents("") { } //default ctor
Serial::Serial(const Serial & ser) : contents(ser.str()) { } //copy ctor
const Serial & Serial::operator= (const Serial & ser){ //assignment overload
	if(this!= &ser) contents = ser.str();
	return *this;
}
Serial::~Serial() { } //dtor

//puts
void Serial::put(bool b){
	contents += b ? 't' : 'f';
}
void Serial::put(short s){
	contents += 's' + serializeNum(s);
}
void Serial::put(int i){
	contents += 'i' + serializeNum(i);
}
void Serial::put(long l){
	contents += 'l' + serializeNum(l);
}
void Serial::put(const string s) {
	contents += 'S';
	contents += serializeNum(s.length());
	for(char c: s) contents += c; 
}
void Serial::put(const char* s){
	cout<<s<<'\n';
    //static_assert(false, "A C string? What the fuck man\n");
    Serial::put(string(s));
}
void Serial::put(char c){
	contents+='c';
	contents+= c;
}
//gets
void Serial::get(bool &b){
	char c = Serial::getChar();
	if(c=='t') b=true;
	else if(c=='f') b=false;
	else {
		ungetChar();
		throw "Item tagged \'"s + c +"\' not actually a boolean, but nice try."s;	
	}
}
void Serial::get(short &s){
	char tag = getChar();
	if(tag!='s') {
		ungetChar();
		throw "Item tagged \'"s + tag +"\' not actually a short, but nice try."s;
	}
	long val = unserializeNum();
	if(val>32767 || val<-32768) throw "Item is too big for a short."s;
	s = val;
}
void Serial::get(int &i){
	char tag = getChar();
	if(tag!='i'){
		ungetChar();
		throw "Item tagged \'"s +tag +"\' not actually an int, but nice try."s; 
	}
	long val = unserializeNum();
	if(val>2147483647 || val<-2147483648) throw "Item is too big for an int."s;
	i = val;
}
void Serial::get(long &l){
	char tag = getChar();
	if(tag!='l'){
        ungetChar();
        throw "Item tagged \'"s + tag +"\' not actually a long, but nice try."s; 
    }l = unserializeNum();
}
void Serial::get(string &s){
	char tag = getChar();
	if(tag!='S') {
		ungetChar();
		throw "Item tagged \'"s +tag +"\' not actually a string, but nice try."s; 
	}
	long length = unserializeNum();
	string temp = "";
	for(int i = 0; i<length; i++) temp+=getChar();
	s = temp;
}
void Serial::get(char &c){
	char tag = getChar();
	if(tag!='c') {
		ungetChar();
		throw "Item tagged \'"s +tag+ "\' not actually a char, but nice try."s;
	}
	c = getChar();
}

//other
string Serial::str() const{
	return contents;
}
void Serial::str(string s){
	contents = s;
}
int Serial::size() const {
	return contents.length();
}
bool Serial::empty() const{ //when contents = const string get fucked with a const bool
	return contents.length()==0;
}
void Serial::ungetChar(){
	contents = gotten+contents;
}
char Serial::getChar(){
	if(contents.length()==0) throw "End of string reached before operation completed."s;
	gotten = contents.at(0);
	contents = contents.substr(1);
	return gotten;
}
int Serial::countBits(long i){
	int numBits;
	(fmod(log2(abs(i))+5,8)==0 && i<0) ? numBits = (long) log2(abs(i))+1 : numBits = (long) log2(abs(i))+2;
	if(i == -pow(2, 63)) numBits = 64;
	return numBits;
}
string Serial::serializeNum(long input){
	long addBytes = (countBits(input)+3)/8; //additional bytes
	long first = (addBytes==8) ? ( (input<0) ? 0x0f | (addBytes<<4) : addBytes<<4 ) : (0xf0 & (addBytes<<4))|(0x0f & (input>>((8*addBytes)))); //first byte with four bit length + first four bits of number
	string s = "";
	s+=char(first);
	for(int i = addBytes-1; i>=0; i--){
		long print = input>>(8*i); //iterates through number and prints additional bytes
		s+=char(print&0xff);
	}
	return s;
}
long Serial::unserializeNum(){
	long c = getChar() & 0xff; //c is first byte (length and first four bits)
	long addBytes = c>>4; //number of additional bytes from first four bits of first byte
	long val = (c&0x0F)<<((addBytes*8)); //result value, started with the bottom four bits of first byte (shifted appropriate length)
	if(addBytes==8) val = 0; //in case of big numbers, avoid overflow
	if(addBytes>8) throw "Item of length " + to_string(addBytes) + " is too big to store."s;
	for(int i = addBytes-1;i>=0;i--) val |= (long(getChar()) & 0xff) << (8*i); //iterates through bytes and masks them onto result val in appropriate place
	//cout<<"num: "<<val<<'\n';
	long topBit = ((8*addBytes)+3<63) ? (8*addBytes)+3 : 63; //position of top bit
	//cout<<"top: "<<topBit<<'\n';
	if(val>>topBit) val |= ~((1L<<topBit)-1); //sign extend if negative
	return val;
}

ostream &operator<<(ostream& oss, const Serial& ser){
	oss<<"String: "<<ser.str()<<"\tSize: "<<ser.size()<<"\tEmpty: "<<ser.empty()<<'\n';
	return oss;
}

