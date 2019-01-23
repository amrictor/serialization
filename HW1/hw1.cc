#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

int countBits(int i){
    int numBits = 1;
    if(i == -8 || i == -2048 || i == -524288 || i == -134217728) numBits--;
    while(i!=0){
        i=i/2;
        numBits++;
    }
    return numBits;
}

int serialize(){ //HW1 serialization method
    int input;
    while(cin >> input){
        long len = (countBits(input)+3)/8; //calculates number of bytes (not counting first) needed to store input with 4bit length indicator at front
        long mask = (1L<<((8*len)+4)) - 1; //mask for all bits before length indicator
        long final = (input & mask) | (len << (8*len+4)); 
        cout << dec << input << ":";
        for(int i = len; i>=0;i--){ //prints one byte at a time, preceded by a space
            long print = final >> (8*i);
	        cout << " " << hex << setw(2) << setfill('0') << (print & 0xff);
    	}
    	cout <<'\n';
    }
    if (!cin.eof()){//handles non numeric input
        cerr << "Incorrect input. Self-destruct imminent.";
        return 13;
    }
    return 0;
}

int serializeShort(){ //9 lines of ugly, ugly code
    long input, numBits;
    while(cin >> input){
        (input == -8 || input == -2048 || input == -524288 || input == -134217728) ? numBits = (long) log2(abs(input))+1 : numBits = (long) log2(abs(input))+2;
        cout << dec << input << ":";
        for(int i = ((numBits+3L)/8L); i>=0;i--) cout << " " << hex << setw(2) << setfill('0') << (((input & ((1L<<((8*((numBits+3L)/8L))+4)) - 1)) | (((numBits+3L)/8L) << (8*((numBits+3L)/8L)+4))) >> (8*i) & 0xff);
        cout << '\n';
    }if (!cin.eof()){
        cerr << "Incorrect input. Self-destruct imminent.\n";
        return 13;}
    return 0;
}
int main(){
    serialize();
    
    return 0;
}


