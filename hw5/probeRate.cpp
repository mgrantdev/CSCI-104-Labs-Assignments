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
    double totalRate = 0; // This is the total probe rate (i.e. probe rate 1 + probe rate 2 + ...)
    for (int i = 0; i < 100; i++)
    {
        double total = 0; // The total number of probe for the current trial
        Hashtable<int> table(true, 11); // Initialize only size of 11 to call resize
        for (int i = 0; i < 3000; i++) // Insert 3000 items
        {
            string randomString = genRandomString(12 + i%12); // 12 is just a random number I pick
            total += table.add(randomString, 2); // 2 is just a random number I pick
        }
        totalRate += total / 3000;
    }
    cout << "The average probe rate is: " << totalRate / 100 << endl;

    return 0;
}