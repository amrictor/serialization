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

		void put(const char*); //left undefined to create compilation error
        
		void put(const bool);
		void put(const short);
		void put(const int);
		void put(const long);
		void put(const char);
		void put(const std::string);

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
		
		//HW6 operator declarations
		Serial& operator+=(const Serial&);
		Serial operator+(const Serial&) const;
        
		bool operator==(const Serial&) const;
		bool operator!=(const Serial&) const;
		
        template <typename T> 
        Serial& operator+=(const T& rhs) { //works on its own
			put(rhs);
			return *this;
		}
		
		template <typename T> 
		Serial operator+(const T& rhs) const { 
			Serial copy = *this;
			return copy+=rhs;
		}
		
		template <typename T> 
		friend Serial operator+(const T& lhs, const Serial& rhs){
		    Serial temp;
		    temp.put(lhs);
		    temp.str(temp.str()+rhs.str());
		    return temp;
		}
		
		template <typename T> 
		friend void operator<<=(T& lhs, Serial& rhs){
		    rhs.get(lhs);
		}
		
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
