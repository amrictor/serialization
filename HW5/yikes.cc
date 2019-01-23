
#include <iostream>
#include <string>

using namespace std;
class C {
    public:
        C(string s) : contents(s){};
        string contents;
        bool check() const{
            return (contents=="Hello World");
        }
};
int main()
{
    const string s = "Hello World";
    C obj= C(s);
    
    cout<<obj.check();

    return 0;
}

