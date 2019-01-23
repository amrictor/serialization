#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <string>
#include <iostream>

class Serial
{
	public:
		Serial();
		Serial(const Serial & ser) : contents(ser.str()){};
		const Serial & operator= (const Serial & ser);
		~Serial();
		
		void put(bool);
		void put(short);
		void put(int);
		void put(long);
		void put(char);
		void put(std::string);

		void get(bool &);
		void get(short &);
		void get(int &);
		void get(long &);
		void get(char &);
		void get(std::string &); 
		
		std::string str() const;
		void str(std::string s);
		int size();
		bool empty();
		
	private:
		std::string contents;
		char getChar(std::string &);
		int countBits(long);
		std::string serializeNum(long);
		long unserializeNum(std::string &s);
};
#endif
