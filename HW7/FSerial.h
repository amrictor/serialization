#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>

void serialize(const bool, std::ostream &);
void serialize(const short, std::ostream &);
void serialize(const int, std::ostream &);
void serialize(const long, std::ostream &);
void serialize(const char, std::ostream &);
void serialize(const std::string &, std::ostream &);

void unserialize(std::istream &, bool &);
void unserialize(std::istream &, short &);
void unserialize(std::istream &, int &);
void unserialize(std::istream &, long &);
void unserialize(std::istream &, char &);
void unserialize(std::istream &, std::string &);

class IFSerial {
public:
	IFSerial(const std::string filename);
	~IFSerial();
	template <typename T>
	IFSerial& operator>> (T& rhs){
		try {
			unserialize(file, rhs);
		} catch (std::string msg) {
			file.setstate(std::ios::failbit);
		}
		return *this;
	}
	bool eof() const;
	bool fail() const;
	explicit operator bool() const; //evaluation in a boolean context

private:
	std::ifstream file;
};

class OFSerial {
public:
	OFSerial(const std::string filename);
	~OFSerial();
	template <typename T>
	OFSerial& operator<< (const T rhs){
		serialize(rhs, file);;
		return *this;
	}
	bool fail() const;
	explicit operator bool() const; //evaluation in a boolean context

private:
	std::ofstream file;
};
#endif
