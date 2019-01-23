#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


using namespace std;

int countBits(long i){ 
     int numBits;
     (fmod(log2(abs(i))+5,8)==0 && i<0) ? numBits = (long) log2(abs(i))+1 : numBits = (long) log2(abs(i))+2;
     if(i == -pow(2, 63)) numBits =  64;
     return numBits;
}
void print(int length, long value){
    for(int i = length; i>=0; i--){
        long print = value >> (8*i);
        cout<< " " << hex << setw(2) << setfill('0') << (print & 0xff);
    }
}
void printNum(long input){
    long len = (countBits(input)+3)/8; //calculates number of bytes (not counting first) needed to store input with 4bit length indicator at front
    long mask = (1L<<((8*len)+4)) - 1; //mask for all bits before length indicator
    long result = (input & mask) | (len << (8*len+4));
    print(len, result);
}
void serializeNum(long input){ 
    int c;
    if(input>=-32768 && input<32768) c = 's';
    else if(input>=-2147483648 && input<2147483648) c = 'i';
    else c = 'l'; 
    cout<<hex<< c;
    long numBits = countBits(input);
    if(numBits>59){
        long newLength = (countBits(input>>32)+3)/8;
        long startMask = (1L<<(8*newLength+4))-1;//mask for first half
        long lengthMask = ((numBits+3)/8)<<(8*newLength+4);
        long start = ((input>>32) & startMask) | lengthMask;
        long end = input & 0xFFFFFFFF;
        print(newLength, start);
        print(3, end);
    }
    else printNum(input);
    cout << '\n';
}
void serializeStr(string s){
    cout << hex << (int)'S';
    printNum(s.length());
    for(char c: s) cout << " " << hex << setw(2)<<setfill('0')<<(int)c; 
    cout<< '\n';
}
void serialize(char *fileName, char *programName){ //HW2 serialization method
    int c;
    ifstream in(fileName);
    if(in.fail()){
        cerr << programName <<": Error with \"" << fileName << "\": File not found.\n";
        exit(EXIT_FAILURE);
    }
    while((c=in.get())){
        if(c=='\''){
            c= in.get();
            if(in.get()!='\'') { //handles ' without second '
                cerr << programName <<": Something went wrong with the number of single quotes. Step away from your computer. Self destruct imminent.\n";
                exit(EXIT_FAILURE);
            }
            cout<< hex<< (int)'c' << " " << hex << setfill('0') << setw(2)<< c << '\n';
        }
        else if(c=='\"'){
            string s="";
            c = in.get();
            while(c!='\"'){
                s+=c;
                c = in.get();
                if (in.eof()){ //handles " without second "
                    cerr << programName << ": Something went wrong with the number of double quotes. Step away from your computer. Self destruct imminent.\n";
                    exit(EXIT_FAILURE);
                }
            }
            serializeStr(s);
        }
        else if((c>='0' && c<='9')||c=='-'){
            in.unget();
            long num;
            if (!(in>>num)||in.get()=='-'){ //handles non numeric input in case of weird -stuff
                cerr << programName << ": Something went wrong with input types. Step away from your computer. Self destruct imminent.\n";
                exit(EXIT_FAILURE);
            }
            in.unget();
            serializeNum(num);
        }
        else if(c>' '){
            cerr << programName << ": Something went wrong with input types. Step away from your computer. Self destruct imminent.\n";
            exit(EXIT_FAILURE);
        }
        else if(in.eof()) return;
    }
    in.close();
	return;
}

int main(int argc, char *argv[]){
    if(argc<2) {
        cerr<< "usage: " << argv[0] << " [fileName0] [fileName1] ... [fileNameN]\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i<argc; i++) serialize(argv[i], argv[0]);
    return 0;
}


