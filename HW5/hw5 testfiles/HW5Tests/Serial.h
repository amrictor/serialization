#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <string>
#include <iostream>

class Serial
{
	public:
		Serial();
		Serial(const Serial & ser);
		const Serial & operator= (const Serial & ser);
		~Serial();
		
		void put(const bool);
		void put(const short);
		void put(const int);
		void put(const long);
		void put(const char);
		void put(const std::string);
        void put(const char*);

		void get(bool &);
		void get(short &);
		void get(int &);
		void get(long &);
		void get(char &);
		void get(std::string &); 
		
		std::string str() const;
		void str(const std::string s);
		int size() const;
		bool empty() const;
		
		friend std::ostream &operator<< (std::ostream&, const Serial&);
		
	private:
		std::string contents;
		char gotten;
		void ungetChar();
		char getChar();
		int countBits(long);
		std::string serializeNum(long);
		long unserializeNum();
};
#endif
