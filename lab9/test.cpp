#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <string>

#define A 54059 
#define B 76963 
#define C 86969 

using namespace std;

unsigned hash_str(const char* s)
{
   unsigned h = 31;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h % C; 
}

string gen_random(int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    string temp = "";

    for (int i = 0; i < len; ++i) {
        temp += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return temp;
}

int main()
{
    set<string> all;
	srand(1);

	for(int i = 0; i < 10; i++) {
		string gen = gen_random(5);
		all.insert(gen);
	}

    set<string>::iterator it;
    for (string str : all)
    {
        cout << str << endl;
    }

}
