#include "Hashtable.h"
#include <time.h> // To allow different random seeds

using namespace std;

string genRandomString(int length) // generate random strings
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string res = "";
    for (int i = 0; i < length; i++)
    {
        res += alphabet[rand() % (alphabet.length())];
    }
    return res;
}

int main()
{
    srand(time(0));
    double confirmedTimes = 0; // This is the number of times that there occurs a collision with <= 23 people
    for (int i = 0; i < 10000; i++)
    {
        Hashtable<int> table(true, 365);
        string randomString;
        for (int j = 0; j < 365; j++)
        {
            string randomString = genRandomString(16 + j%16); // 16 is just a random number I pick
            // We "basically" don't need to consider resize because the probability that there's no collision with 183(365/2) birthdays is extremely small(< 10^(-20))
            if (table.add(randomString, 2) >= 1) // 2 is just a random number I pick
            {
                if (j < 23) confirmedTimes += 1; // j < 23 instead of <= since j is initialized to 0
                break;
            }
        }
    }
    cout << confirmedTimes / 10000 << endl;

    return 0;
}