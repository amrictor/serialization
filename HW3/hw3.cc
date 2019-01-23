//THIS VERSION PASSES ALL HW3 TESTS
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <unistd.h>

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
    if(numBits>59){ //dealing with >59bit longs yikes
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
        exit(1);
    }
    while((c=in.get())){
        if(c=='\''){
            c= in.get();
            if(in.get()!='\'') { //handles ' without second '
                cerr << programName <<": Error in \""<<fileName<<"\": Characters must be contained by single quotes on either side. Step away from your computer. Self destruct imminent.\n";
                exit(2);
            }
            cout<< hex<< (int)'c' << " " <<  hex << setfill('0') << setw(2) << c << '\n';
        }
        else if(c=='\"'){
            string s="";
            c = in.get();
            while(c!='\"'){
                s+=c;
                c = in.get();
                if (in.eof()){ //handles " without second "
                    cerr << programName << ": Error in \""<<fileName<<"\": Strings must be contained by double quotes on either side. Step away from your computer. Self destruct imminent.\n";
                    exit(3);
                }
            }
            serializeStr(s);
        }
        else if((c>='0' && c<='9')||c=='-'){
            in.unget();
            long num;
            if (!(in>>num)||in.get()=='-'){ //handles non numeric input in case of weird -stuff
                cerr << programName << ": Error in \""<<fileName<<"\": Input is not allowed. Step away from your computer. Self destruct imminent.\n";
                exit(4);
            }
            in.unget();
            serializeNum(num);
        }
        else if(c=='t'||c=='f'){
            in.unget();
            string s;
            in >> s;
            if(s=="true"||s=="false") cout << hex << c << '\n';
            else{ //bad input starting with t or f
                cerr << programName << ": Error in \""<<fileName<<"\": Input is not allowed. Step away from your computer. Self destruct imminent.\n";
                exit(5);
            }
        }
        else if(in.eof()) break;
		else if(!isspace(c)){
            cerr << programName << ": Error in \""<<fileName<<"\": Input is not allowed. Step away from your computer. Self destruct imminent.\n";
            exit(6);
        }
        
//         else if(in.eof()) break;
//         else if(!isspace(c)){ //bad input
//             cerr << programName << ": Input is not allowed. Step away from your computer. Self destruct imminent.\n";
//             exit(6);
//         }
    }
    in.close();
    return;
}
long unserializeNum(ifstream *in, char *programName, char *fileName, int tag){
	while(isspace(in->get())){}
	int topBit = -1;
	in->unget();
	string len = "";
	len += in->get();
	string val = "";
	long result;
	int numChars = 1;
	for(unsigned int i = 0; i<(2*stoul(len, nullptr, 16))+1; i++){
		char temp = in->get(); 
//		(isspace(temp)) ? cout<<"SPACE" : cout<<temp;
		if(!isspace(temp)){			
			val+=temp;
			topBit+=4;
			numChars++;
		}else{
			if(numChars!=2 && numChars!=0){
				cerr<< programName << ": Error in \""<<fileName<<"\": Input is incorrectly spaced. Step away from your computer. Self destruct imminent.\n";
				exit(7);
			}
			numChars=0;
			i--;
		}
	}
	if(val.length()>16) {
		if(val[0]!='0' && tolower(val[0]) !='f') {
			cerr<< programName << ": Error in \""<<fileName<<"\": Number is too large for data type. Step away from your computer. Self destruct imminent.\n";
			exit(8);
		}
		val = val.substr(1); 
		topBit-=4;
	}
	(stoul(val, nullptr, 16)>>topBit) ? result = stoul(val, nullptr, 16)|~((1L<<topBit)-1) : result = stoul(val, nullptr, 16);
	if((tag=='s' && (result>32767||result<-32768))||(tag=='i' && (result>2147483647||result<-2147483648))) {
		cerr<< programName << ": Error in \""<<fileName<<"\": Number is too large for data type. Step away from your computer. Self destruct imminent.\n";
		exit(9);
	}
	return result;
}
string unserializeStr(ifstream *in, char *programName, char *fileName){
	long length = unserializeNum(in, programName, fileName, 'l');
	string s = "";
	for(int i = 0; i<length; i++){
		int c;
		if(*in>>c) s+=c;
		else {
			cerr<< programName << ": Error in \""<< fileName <<"\": End of file reached prematurely. Step away from your computer. Self destruct imminent.\n";
			exit(10);
		}
	}
	return "\""+s+"\"";
}
void unserialize(char *fileName, char *programName){
    int c;
    ifstream in(fileName);
    if(in.fail()){
        cerr << programName <<": Error with \"" << fileName << "\": File not found.\n";
        exit(11);
    }
    while(in>>hex>>c){
        switch(c){
            case's':
            case'i':
            case'l': cout<<dec<<unserializeNum(&in, programName, fileName, c)<< '\n';break;
            case'c':
				unsigned int temp;
                in>>hex>>temp;
				if(temp>0x7F){
					cerr << programName << ": Error in \""<<fileName<<"\": Input is not a valid character. Step away from your computer. Self destruct imminent.\n";
					exit(12);
				}
                cout<<'\''<<(char)temp<<"\'\n";break;
            case'S': cout<<unserializeStr(&in, programName, fileName)<<'\n';break;
            case't': cout<<"true\n";break;
            case'f': cout<<"false\n";break;
            default: 
                cerr << programName << ": Error in \""<<fileName<<"\": Nonexistent tag. Step away from your computer. Self destruct imminent.\n";
                exit(13);
        }
    }
    if(!in.eof()){
		cerr << programName << ": Error in \""<<fileName<<"\": Input could not be read properly. Step away from your computer. Self destruct imminent.\n";
			exit(14);
	}
}
int main(int argc, char * const argv[]){
    char opt;
    int v = 0;
    int s = 0;
    int u = 0;
    while ((opt = getopt(argc, argv, "+usv")) != -1){
        switch(opt){
            case's': s=1;break;
            case'u': u=1;break;
            case'v': v=1;break;
	    default: exit(15);
        }
    }
    if(optind>=argc || (u&&s)) {
        cerr<< "usage: " << argv[0] << " [-s|-u|-v] [fileName0] [fileName1] ... [fileNameN]\n";
        exit(16);
    }
    for (int i = optind; i<argc; i++){
        if(v) cerr<<"Processing file " << argv[i]<<'\n';
		if(!u) serialize(argv[i], argv[0]);
        else if(u && !s) unserialize(argv[i], argv[0]);
		else{
			cerr<< "usage: " << argv[0] << " [-s|-u|-v] [fileName0] [fileName1] ... [fileNameN]\n";
			exit(17);
		}
	}
    return 0;
}


