#include "Serial.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

    int main() {
        cout << "Test begins\n\n";
		
		string S;
		short s;
		int i;
		long l;
		char c;
		bool b;
		
		cout<<"Testing constructors\n";
		//testContructors
		Serial ser;
		assert(ser.str() == ""s && ser.size()==0 && ser.empty());
		
		ser.str("FUCK");
		Serial copy(ser);
		assert(ser.str()==copy.str());
		Serial assign = ser;
		assert(ser.str()==assign.str());
		ser.str("");

		cout<<"Testing const-correctness\n";
		//testConstCorrectness
		const Serial con;
		assert(con.size()==0 && con.str()=="" && con.empty());
		const string cS = "Hello World";
		ser.put(cS);
		assert(ser.str()=="S\x10\x0b" "Hello World"s && ser.size()==14 && !ser.empty()); // cannot convert  bool (Serial::) error
		ser.str("");
		const int ci = 4;
		ser.put(ci);
		assert(ser.str()=="i\x04"s && ser.size()==2 && !ser.empty());
		ser.str("");
		const long cl = 4;
		ser.put(cl);
		assert(ser.str()=="l\x04"s && ser.size()==2 && !ser.empty());
		ser.str("");
		const short cs = 4;
		ser.put(cs);
		assert(ser.str()=="s\x04"s && ser.size()==2 && !ser.empty());
		ser.str("");
		const char cc = 'f';
		ser.put(cc);
		assert(ser.str()=="cf"s && ser.size()==2 && !ser.empty());
		ser.str("");
		const bool cb = true;
		ser.put(cb);
		assert(ser.str()=="t"s && ser.size()==1 && !ser.empty());
		ser.str("");

		//Begin HW2 Tests, backwards and forwards
		
		cout<<"\nBegin HW2 Tests: Serializing\n\n";
		//testPUTS
		
		cout<<"testAll\n";
		//testAll
		ser.put(34374);
		assert(ser.str()=="\x69\x20\x86\x46"s && ser.size()==4 && !ser.empty());
		ser.str("");
		ser.put(short(-84));
		assert(ser.str()=="\x73\x1f\xac"s && ser.size()==3 && !ser.empty());
		ser.str("");
		ser.put('g');
		assert(ser.str()=="\x63\x67"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put("all type of test data"s);
		assert(ser.str()=="\x53\x10\x15\x61\x6c\x6c\x20\x74\x79\x70\x65\x20\x6f\x66\x20\x74\x65\x73\x74\x20\x64\x61\x74\x61"s && ser.size()==24 && !ser.empty());
		ser.str("");
		ser.put(7666555444);
		assert(ser.str()=="\x6c\x41\xc8\xf6\x5a\x34"s && ser.size()==6 && !ser.empty());
		ser.str("");
		ser.put('`');
		assert(ser.str()=="\x63\x60"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put(" THANK	you	"s);
		assert(ser.str()=="\x53\x10\x0b\x20\x54\x48\x41\x4e\x4b\x09\x79\x6f\x75\x09"s && ser.size()==14 && !ser.empty());
		
		cout<<"testChar\n";
		//testChars
		ser.str("");
		ser.put('!');
		assert(ser.str()=="\x63\x21"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('@');
		assert(ser.str()=="\x63\x40"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('%');
		assert(ser.str()=="\x63\x25"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('^');
		assert(ser.str()=="\x63\x5e"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('-');
		assert(ser.str()=="\x63\x2d"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put(':');
		assert(ser.str()=="\x63\x3a"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('|');
		assert(ser.str()=="\x63\x7c"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('	');
		assert(ser.str()=="\x63\x09"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('/');
		assert(ser.str()=="\x63\x2f"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('5');
		assert(ser.str()=="\x63\x35"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('f');
		assert(ser.str()=="\x63\x66"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('"');
		assert(ser.str()=="\x63\x22"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put(',');
		assert(ser.str()=="\x63\x2c"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put('+');
		assert(ser.str()=="\x63\x2b"s && ser.size()==2 && !ser.empty());
		
		cout<<"testInts\n";
		//testInts
		ser.str("");
		ser.put(35000);
		assert(ser.str()=="\x69\x20\x88\xb8"s && ser.size()==4 && !ser.empty());
		ser.str("");
		ser.put(2147483647);
		assert(ser.str()=="\x69\x40\x7f\xff\xff\xff"s && ser.size()==6 && !ser.empty());
		ser.str("");
		ser.put(int(-2147483648));
		assert(ser.str()=="\x69\x4f\x80\x00\x00\x00"s && ser.size()==6 && !ser.empty());
		ser.str("");
		ser.put(32768);
		assert(ser.str()=="\x69\x20\x80\x00"s && ser.size()==4 && !ser.empty());
		ser.str("");
		ser.put(-32769);
		assert(ser.str()=="\x69\x2f\x7f\xff"s && ser.size()==4 && !ser.empty());
		
		cout<<"testLongs\n";
		//testLongs
		ser.str("");
		ser.put(3111222333);
		assert(ser.str()=="\x6c\x40\xb9\x71\x7c\x3d"s && ser.size()==6 && !ser.empty());
		ser.str("");
		ser.put(-4555666777);
		assert(ser.str()=="\x6c\x4e\xf0\x76\x0a\xa7"s && ser.size()==6 && !ser.empty());
		ser.str("");
		ser.put(9223372036854775807);
		assert(ser.str()=="\x6c\x80\x7f\xff\xff\xff\xff\xff\xff\xff"s && ser.size()==10 && !ser.empty());
		ser.str("");
		ser.put(-9223372036854775807-1);
		assert(ser.str()=="\x6c\x8f\x80\x00\x00\x00\x00\x00\x00\x00"s && ser.size()==10 && !ser.empty());
		ser.str("");
		ser.put(2147483648);
		assert(ser.str()=="\x6c\x40\x80\x00\x00\x00"s && ser.size()==6 && !ser.empty());
		ser.str("");
		ser.put(-2147483649);
		assert(ser.str()=="\x6c\x4f\x7f\xff\xff\xff"s && ser.size()==6 && !ser.empty());
		
		cout<<"testShorts\n";
		//testShorts
		ser.str("");
		ser.put(short(32767));
		assert(ser.str()=="\x73\x20\x7f\xff"s && ser.size()==4 && !ser.empty());
		ser.str("");
		ser.put(short(6));
		assert(ser.str()=="\x73\x06"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put(short(-10));
		assert(ser.str()=="\x73\x1f\xf6"s && ser.size()==3 && !ser.empty());
		ser.str("");
		ser.put(short(0));
		assert(ser.str()=="\x73\x00"s && ser.size()==2 && !ser.empty());
		ser.str("");
		ser.put(short(-32768));
		assert(ser.str()=="\x73\x2f\x80\x00"s && ser.size()==4 && !ser.empty());
		
		cout<<"testStrings\n";
		//testStrings
		ser.str("");
		ser.put("This is HW2 test case."s);		assert(ser.str()=="\x53\x10\x16\x54\x68\x69\x73\x20\x69\x73\x20\x48\x57\x32\x20\x74\x65\x73\x74\x20\x63\x61\x73\x65\x2e"s && ser.size()==25 && !ser.empty());
		ser.str("");
		ser.put("Today is 12/02/2018 @csu & that's it."s);
		assert(ser.str()=="\x53\x10\x25\x54\x6f\x64\x61\x79\x20\x69\x73\x20\x31\x32\x2f\x30\x32\x2f\x32\x30\x31\x38\x20\x40\x63\x73\x75\x20\x26\x20\x74\x68\x61\x74\x27\x73\x20\x69\x74\x2e"s && ser.size()==40 && !ser.empty());
		ser.str("");
		ser.put("#HW2	#CS253{}"s);
		assert(ser.str()=="\x53\x10\x0d\x23\x48\x57\x32\x09\x23\x43\x53\x32\x35\x33\x7b\x7d"s && ser.size()==16 && !ser.empty());
		ser.str("");

		
		cout<<"\nBegin HW2 Tests: Unserializing\n\n";
		//testGETS
		try {
			
			cout<<"testAll\n";
			//testAll
			ser.str("\x69\x20\x86\x46"s);
			ser.get(i);
			assert(i == 34374);
			ser.str("\x73\x1f\xac"s);
			ser.get(s);
			assert(s == -84);
			ser.str("\x63\x67"s);
			ser.get(c);
			assert(c == 'g');
			ser.str("\x53\x10\x15\x61\x6c\x6c\x20\x74\x79\x70\x65\x20\x6f\x66\x20\x74\x65\x73\x74\x20\x64\x61\x74\x61"s);
			ser.get(S);
			assert(S == "all type of test data"s);
			ser.str("\x6c\x41\xc8\xf6\x5a\x34"s);
			ser.get(l);
			assert(l == 7666555444);
			ser.str("\x63\x60"s);
			ser.get(c);
			assert(c == '`');
			ser.str("\x53\x10\x0b\x20\x54\x48\x41\x4e\x4b\x09\x79\x6f\x75\x09"s);
			ser.get(S);
			assert(S == " THANK	you	"s);
			
			cout<<"testChars\n";
			//testChars
			ser.str("\x63\x21"s);
			ser.get(c);
			assert(c == '!');
			ser.str("\x63\x40"s);
			ser.get(c);
			assert(c == '@');
			ser.str("\x63\x25"s);
			ser.get(c);
			assert(c == '%');
			ser.str("\x63\x5e"s);
			ser.get(c);
			assert(c == '^');
			ser.str("\x63\x2d"s);
			ser.get(c);
			assert(c == '-');
			ser.str("\x63\x3a"s);
			ser.get(c);
			assert(c == ':');
			ser.str("\x63\x7c"s);
			ser.get(c);
			assert(c == '|');
			ser.str("\x63\x09"s);
			ser.get(c);
			assert(c == '	');
			ser.str("\x63\x2f"s);
			ser.get(c);
			assert(c == '/');
			ser.str("\x63\x35"s);
			ser.get(c);
			assert(c == '5');
			ser.str("\x63\x66"s);
			ser.get(c);
			assert(c == 'f');
			ser.str("\x63\x22"s);
			ser.get(c);
			assert(c == '"');
			ser.str("\x63\x2c"s);
			ser.get(c);
			assert(c == ',');
			ser.str("\x63\x2b"s);
			ser.get(c);
			assert(c == '+');
			
			cout<<"testInts\n";
			//testInts
			ser.str("\x69\x20\x88\xb8"s);
			ser.get(i);
			assert(i == 35000);
			ser.str("\x69\x40\x7f\xff\xff\xff"s);
			ser.get(i);
			assert(i == 2147483647);
			ser.str("\x69\x4f\x80\x00\x00\x00"s);
			ser.get(i);
			assert(i == -2147483648);
			ser.str("\x69\x20\x80\x00"s);
			ser.get(i);
			assert(i == 32768);
			ser.str("\x69\x2f\x7f\xff"s);
			ser.get(i);
			assert(i == -32769);

			cout<<"testLongs\n";
			//testLongs
			ser.str("\x6c\x40\xb9\x71\x7c\x3d"s);
			ser.get(l);
			assert(l == 3111222333);
			ser.str("\x6c\x4e\xf0\x76\x0a\xa7"s);
			ser.get(l);
			assert(l == -4555666777);
			ser.str("\x6c\x80\x7f\xff\xff\xff\xff\xff\xff\xff"s);
			ser.get(l);
			assert(l == 9223372036854775807);
			ser.str("\x6c\x8f\x80\x00\x00\x00\x00\x00\x00\x00"s);
			ser.get(l);
			assert(l == -9223372036854775807-1);
			ser.str("\x6c\x40\x80\x00\x00\x00"s);
			ser.get(l);
			assert(l == 2147483648);
			ser.str("\x6c\x4f\x7f\xff\xff\xff"s);
			ser.get(l);
			assert(l == -2147483649);
			
			cout<<"testShorts\n";
			//testShorts
			ser.str("\x73\x20\x7f\xff"s);
			ser.get(s);
			assert(s == 32767);
			ser.str("\x73\x06"s);
			ser.get(s);
			assert(s == 6);
			ser.str("\x73\x1f\xf6"s);
			ser.get(s);
			assert(s == -10);
			ser.str("\x73\x00"s);
			ser.get(s);
			assert(s == 0);
			ser.str("\x73\x2f\x80\x00"s);
			ser.get(s);
			assert(s == -32768);
			
			cout<<"testStrings\n";
			//testStrings
			ser.str("\x53\x10\x16\x54\x68\x69\x73\x20\x69\x73\x20\x48\x57\x32\x20\x74\x65\x73\x74\x20\x63\x61\x73\x65\x2e"s);
			ser.get(S);
			assert(S == "This is HW2 test case."s);
			ser.str("\x53\x10\x25\x54\x6f\x64\x61\x79\x20\x69\x73\x20\x31\x32\x2f\x30\x32\x2f\x32\x30\x31\x38\x20\x40\x63\x73\x75\x20\x26\x20\x74\x68\x61\x74\x27\x73\x20\x69\x74\x2e"s);
			ser.get(S);
			assert(S == "Today is 12/02/2018 @csu & that's it."s);
			ser.str("\x53\x10\x0d\x23\x48\x57\x32\x09\x23\x43\x53\x32\x35\x33\x7b\x7d"s);
			ser.get(S);
			assert(S == "#HW2	#CS253{}"s);
			
		}
		catch (string msg) {
			cerr << "Unserialize error: " << msg << '\n';
		}
		
		//Begin HW4 Tests
		
		cout<<"\nRunning HW4 Tests: Serializing\n";
		
		ser.put(short(5));
		assert(ser.str()=="s" "\x05");
		ser.str("");
		ser.put(true);
		assert(ser.str()=="t");
		ser.str("");
		ser.put(false);
		assert(ser.str()=="f");
		ser.str("");
		ser.put(short(-12));
		assert(ser.str()=="s" "\x1f\xf4");
		ser.str("");
		ser.put(short(32767));
		assert(ser.str()=="s" "\x20\x7f\xff");
		ser.str("");
		ser.put(short(-32768));
		assert(ser.str()=="s" "\x2f\x80\x0"s);
		ser.str("");
		ser.put(short(0));
		assert(ser.str()=="s" "\x0"s);
		ser.str("");
		ser.put(2147483647);
		assert(ser.str()=="i" "\x40\x7f\xff\xff\xff");
		ser.str("");
		ser.put(int(-2147483648));
		assert(ser.str()=="i" "\x4f\x80\x0\x0\x0"s);
		ser.str("");
		ser.put(32768);
		assert(ser.str()=="i" "\x20\x80\x0"s);
		ser.str("");
		ser.put(-32769);
		assert(ser.str()=="i" "\x2f\x7f\xff");
		ser.str("");
		ser.put(111222333);
		assert(ser.str()=="i" "\x36\xa1\x1e\x3d");
		ser.str("");
		ser.put(9223372036854775807);
		assert(ser.str()=="l" "\x80\x7f\xff\xff\xff\xff\xff\xff\xff");
		ser.str("");
		ser.put(-9223372036854775807-1);
		assert(ser.str()=="l" "\x8f\x80\x0\x0\x0\x0\x0\x0\x0"s);
		ser.str("");
		ser.put(1222333444555);
		assert(ser.str()=="l" "\x51\x1c\x98\xc0\x31\xcb");
		ser.str("");
		ser.put(' ');
		assert(ser.str()=="c" "\x20");
		ser.str("");
		ser.put('	');
		assert(ser.str()=="c" "\x09");
		ser.str("");
		ser.put('^');
		assert(ser.str()=="c" "\x5e");
		ser.str("");
		ser.put("TESTING string1."s);
		assert(ser.str()=="S" "\x10\x10" "TESTING string1.");
		ser.str("");
		ser.put("TESTING string with tab	."s);
		assert(ser.str()=="S" "\x10\x19" "TESTING string with tab	.");
		ser.str("");
		
		
		cout<<"Running HW4 Tests: Unserializing\n";
		//testGETS
		try{
			ser.str("f" "s"s "\x05");
			ser.get(b);
			assert(b == 0);
			ser.str("t" "s"s "\x1f\xf4");
			ser.get(b);
			assert(b == 1);
			ser.str("s"s "\x20\x7f\xff");
			ser.get(s);
			assert(s == 32767);
			ser.str("s" "\x2f\x80\x0"s);
			ser.get(s);
			assert(s == -32768);
			ser.str("s" "\x0"s);
			ser.get(s);
			assert(s == 0);
			ser.str("i" "\x40\x7f\xff\xff\xff");
			ser.get(i);
			assert(i == 2147483647);
			ser.str("i" "\x4f\x80\x0\x0\x0"s);
			ser.get(i);
			assert(i == -2147483648);
			ser.str("i" "\x20\x80\x0"s);
			ser.get(i);
			assert(i == 32768);
			ser.str("i" "\x2f\x7f\xff");
			ser.get(i);
			assert(i == -32769);
			ser.str("i" "\x37\x5b\xcd\x15");
			ser.get(i);
			assert(i == 123456789);
			ser.str("l" "\x80\x7f\xff\xff\xff\xff\xff\xff\xff");
			ser.get(l);
			assert(l == 9223372036854775807);
			ser.str("l" "\x8f\x80\x0\x0\x0\x0\x0\x0\x0"s);
			ser.get(l);
			assert(l == -9223372036854775807-1);
			ser.str("l" "\x8f\xf2\x1f\xae\x74\x50\x49\x11\xcc");
			ser.get(l);
			assert(l == -999888777666555444);
			ser.str("c" "\x7e");
			ser.get(c);
			assert(c == '~');
			ser.str("c" "\x7c");
			ser.get(c);
			assert(c == '|');
			ser.str("c" "\x2f");
			ser.get(c);
			assert(c == '/');
			ser.str("S" "\x05" "test.");
			ser.get(S);
			assert(S == "test.");
			ser.str("S" "\x10\x19" "testing STRING with tab	.");
			ser.get(S);
			assert(S == "testing STRING with tab	.");

		}
		catch (string msg) {
			cerr << "Unserialize error: " << msg << '\n';
		}
		
		cout<<"Running extended HW5 test battery\n\n";
		try{
			ser.str("s"s "\x20\x7f\xff");
			ser.str(ser.str() + "s" "\x2f\x80\x0"s);
			ser.str(ser.str() + "s" "\x0"s);
			ser.str(ser.str() + "i" "\x40\x7f\xff\xff\xff");
			ser.str(ser.str() + "i" "\x4f\x80\x0\x0\x0"s);
			ser.str(ser.str() + "i" "\x20\x80\x0"s);
			ser.get(s);
			assert(s == 32767);
			ser.get(s);
			assert(s == -32768);
			ser.get(s);
			assert(s == 0);
			ser.get(i);
			assert(i == 2147483647);
			ser.get(i);
			assert(i == -2147483648);
			ser.get(i);
			assert(i == 32768);
			cout << "Multiple unserialize\n";
			
			ser.str("");
			ser.put(string("Hey bb"));
			ser.put(12345);
			ser.put((short)69);
			ser.get(S);
			assert(S == string("Hey bb"));
			ser.get(i);
			assert(i == 12345);
			ser.put(true);
			ser.put('t');
			ser.get(s);
			assert(s == 69);
			ser.get(b);
			assert(b == 1);
			ser.put(string("LlLlMmmMMmAMooaooooo ,.,';lkjhgaoweor;34567 9345 "));
			ser.get(c);
			assert(c == 't');
			ser.get(S);
			assert(S == string("LlLlMmmMMmAMooaooooo ,.,';lkjhgaoweor;34567 9345 "));
			cout << "Continous serialize & unserialize\n";
		}
		catch (string msg) {
			cerr << "extended HW5 test battery error: " << msg << '\n';
		}
		
		cout<<"\nBegin error testing.\n\n";
		
		cout<<"Checking: not a boolean\n";
		bool caught = false;
		try{
			ser.str("\x37"s);
			ser.get(b);
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;

		
		cout<<"Checking: not a tagged short\n";
		try{
			ser.str("\x69\x20\x9a\x6e"s);
			ser.get(s);			
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;
		
		
		cout<<"Checking: too big for short\n";
		try{
			ser.str("\x73\x20\x9a\x6e"s);
			ser.get(s);			
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;
		
		
		cout<<"Checking: not a tagged int\n";
		try{
			ser.str("\x6c\x42\x4a\x13\xfe\xf1"s);
			ser.get(i);			
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;
		
		
		cout<<"Checking: too big for int\n";
		try{
			ser.str("\x69\x42\x4a\x13\xfe\xf1"s);
			ser.get(i);			
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;
		
		
		cout<<"Checking: not a tagged long\n";
		try{
			ser.str("\x73\x20\x9a\x6e"s);
			ser.get(l);			
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;
		
				
		cout<<"Checking: too big for long\n";
		try{
			ser.str("\x6c\x90\x00\x7f\xff\xff\xff\xff\xff\xff\xff"s);
			ser.get(l);			
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;
		
		
		cout<<"Checking: not a tagged char\n";
		try{
			ser.str("\x69\x2b"s);
			ser.get(c);			
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;
		
		
		cout<<"Checking: not a tagged string\n";
		try{
			ser.str("\x73\x10\x16\x54\x68\x69\x73\x20\x69\x73\x20\x48\x57\x32\x20\x74\x65\x73\x74\x20\x63\x61\x73\x65\x2e"s);
			ser.get(S);			
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;
		
		
		cout<<"Checking: length too large (string)\n";
		try{
			ser.str("\x53\x10\x25\x54\x68\x69\x73\x20\x69\x73\x20\x48\x57\x32\x20\x74\x65\x73\x74\x20\x63\x61\x73\x65\x2e"s);
			ser.get(S);			
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;
		
		
		cout<<"Checking: length too large (number)\n";
		try{
			ser.str("\x69\x62\x4a\x13\xfe\xf1"s);
			ser.get(i);			
		}
		catch (string msg) {
			caught = true;
		}
		assert(caught); caught = false;
		
		
		cout<<"Checking: state after error\n";
		try{
			ser.str("s" "\x2f\x80\x0"s);
			try{ser.get(i);
			}catch (string msg) {}
			try{ser.get(c);
			}catch (string msg) {}
			try{ser.get(b);
			}catch (string msg) {}
			try{ser.get(l);
			}catch (string msg) {}
			try{ser.get(S);
			}catch (string msg) {}
			ser.get(s);
			assert(s == -32768);
			
			ser.str("\x69\x20\x88\xb8"s);
			try{ser.get(s);
			}catch (string msg) {}
			ser.get(i);
			assert(i == 35000);
		}catch (string msg) {
			cerr << "state after error: error: " << msg << '\n';
		}
		
// 		try{
// 			ser.str("s" "\x80\x7f\xff\xff\xff\xff\xff\xff\xff"s);
// 			try{
// 				ser.get(s);
// 			}catch (string msg) {}
// 			assert(ser.str() == "s" "\x80\x7f\xff\xff\xff\xff\xff\xff\xff"s);
// 		}catch (string msg) {
// 			cerr << "state after error: short editing error: " << msg << '\n';
// 		}
/*		
		try{
			ser.str("c");
			try{
				ser.get(c);
			}catch (string msg) {}
			assert(ser.str() == "c");
		}catch (string msg) {
			cerr << "state after error: char editing error: " << msg << '\n';
		}
		
		try{
			ser.str("S" "\x80\x7f\xff\xff\xff\xff\xff\xff\xff"s);
			try{
				ser.get(S);
			}catch (string msg) {}
			assert(ser.str() == "S" "\x80\x7f\xff\xff\xff\xff\xff\xff\xff"s);
		}catch (string msg) {
			cerr << "state after error: string editing error: " << msg << '\n';
		}
		
		try{
			ser.str("i" "\x80\x7f\xff\xff\xff\xff\xff\xff\xff"s);
			try{
				ser.get(i);
			}catch (string msg) {}
			assert(ser.str() == "i" "\x80\x7f\xff\xff\xff\xff\xff\xff\xff"s);
		}catch (string msg) {
			cerr << "state after error: int editing error: " << msg << '\n';
		}
		
		try{
			ser.str("l" "\x21"s);
			try{
				ser.get(l);
			}catch (string msg) {}
			assert(ser.str() == "l" "\x21"s);
		}catch (string msg) {
			cerr << "state after error: int editing error: " << msg << '\n';
		}
		*/
		cout<<"Checking: assignment operator\n";
		try{
			ser.str("l" "\x21"s);
			
			Serial ser2;
			ser2 = ser;
			assert(ser2.str() == "l" "\x21"s);
		}catch (string msg) {
			cerr << "assignment operator: error " << msg << '\n';
		}
		
		cout<<"Checking: copy constructor\n";
		try{
			ser.str("l" "\x21"s);
			
			Serial ser2 = ser;
			assert(ser2.str() == "l" "\x21"s);
		}catch (string msg) {
			cerr << "copy constructor: error " << msg << '\n';
		}
		
		cout << "\nAll errors caught\n\n";
        cout << "Test ends\n";

        return 0;
    }
