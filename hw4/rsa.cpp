#include <cmath>  // To use log
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string s)  // Split the string to a vector using delimiter ' ' (space)
{
    vector<string> v;
    string buf = "";
    for (int i = 0; i < s.length(); i++) {
        // Whenever encounter a space, push the buffer string before that space, and then reset the buffer string
        if (s[i] == ' ') {
            v.push_back(buf);
            buf = "";
        } else
            buf += s[i];
    }
    v.push_back(buf);
    return v;
}

void quit(int errorCode)  // Exit the program
{
    cout << "Program terminated." << endl;
    if (errorCode == 0)
        cout << "You entered EXIT." << endl;
    else if (errorCode == 1)
        cout << "You entered an invalid command." << endl;
    else if (errorCode == 2)
        cout << "The specified file is not found." << endl;
    else if (errorCode == 3)
        cout << "Your choice of n is too small." << endl;
    else if (errorCode == 4)
        cout << "Your choice of p and q are not correct." << endl;
    else if (errorCode == 5)
        cout << "n must be a number." << endl;
    else if (errorCode == 6)
        cout << "Please provide one p and one q." << endl;
    exit(0);
}

vector<bool> decToBin(long num)  // Change the given number from base 10 to base 2
{
    vector<bool> res;
    while (num > 0) {
        res.push_back(num % 2);  // Keeps modding 2 to determine 1 or 0 on that binary digit
        num /= 2;                // Go to the next binary digit
    }
    return res;
}

long modexp(long b, vector<bool> a, long m)  // Direct implementation of handout 16
{
    long x = 1;
    long power = b % m;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == 1)
            x = (x * power) % m;
        power = (power * power) % m;  // This is the only change to avoid overflow
    }
    return x;
}

void encrypt(string filename, long n, string message) {
    if (n < 27)
        quit(3);  // Check if n < 27
    const long e = 65537;
    int x = 1 + log(n / 27) / log(100);  // Calculate x
    vector<long> Ms;                     // Ms store M in C = M^e mod n
    int count = 0;
    bool traversed = false;
    string converted;
    while (!traversed) {
        converted = "";
        int endIndex = x * (count + 1) < message.length()
                               ? x * (count + 1)
                               : message.length();  // Check if x > number of remaining characters (need to add 00)
        for (int i = count * x; i < endIndex; i++) {
            if (message[i] == ' ')
                converted += "00";  // This add 00 is for space
            else {
                if (int(message[i]) - 96 <= 9)
                    converted += "0";  // Check if the number has only 1 digit. If so, add 0 before it so that 7 becomes
                                       // 07
                converted += to_string(int(message[i]) - 96);  // 97 is 'a'. So -96 will get the correct numer
            }
        }
        if (x * (count + 1) >= message.length())  // If we just reach the end or need to add 00
        {
            for (int i = endIndex; i < x * (count + 1); i++) {
                converted += "00";  // This add 00 is to fill characters when number of remaining characters < x
            }
            traversed = true;  // Then we can stop
        }
        Ms.push_back(stol(converted));
        count += 1;
    }
    string res = "";
    for (int i = 0; i < Ms.size(); i++) {
        res += to_string(modexp(Ms[i], decToBin(e), n));  // Calculate C = M^e mod n
        if (i != Ms.size() - 1)
            res += ' ';  // If we are encrypting the last x characters, there's no need to add a space at the end
    }
    // Write to specified file
    ofstream fout(filename);
    fout << res;
    fout.close();
}

long mygcd(long p, long q)  // Direct implementation of handout 15
{
    if (q == 0)
        return p;
    return mygcd(q, p % q);
}

long extendedEuclidean(long e, long L)  // Direct implementation of HW4 Writeup
{
    long s = 0;
    long old_s = 1;
    long t = 1;
    long old_t = 0;
    long r = e;
    long old_r = L;
    long quotient;
    long temp;
    while (r != 0) {
        quotient = old_r / r;
        temp = r;
        r = old_r - quotient * r;
        old_r = temp;
        temp = s;
        s = old_s - quotient * s;
        old_s = temp;
        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }
    return old_t;
}

void decrypt(string input, string output, long p, long q) {
    ifstream fin(input);
    if (!fin.is_open())
        quit(2);  // Check if can not find encrypted file
    string line;
    getline(fin, line);
    vector<string> tempEncrypted = split(line);
    long n = p * q;
    int x = 1 + log(n / 27) / log(100);
    p -= 1;
    q -= 1;
    const long e = 65537;
    long L = p * q / mygcd(p, q);  // Calculate least common multiple(p-1, q-1)
    if (L < e)
        quit(4);  // Check if L < e (p and q are not going to work)
    if (mygcd(e, L) != 1)
        quit(4);  // Check if gcd(e, L) is not 1 (p and q are not going to work)
    long d = extendedEuclidean(e, L);
    d = d < 0 ? d + p * q : d;  // If the decryption key d < 0, add (p-1)*(q-1) to it as written in HW4 Writeup
    // Read encrypted file
    vector<long> encrypted;
    for (int i = 0; i < tempEncrypted.size(); i++) {
        encrypted.push_back(stol(tempEncrypted[i]));
    }
    string res;
    string decrypted;
    for (int i = 0; i < encrypted.size(); i++) {
        decrypted = "";
        string M = to_string(modexp(encrypted[i], decToBin(d), n));  // Calculate M = C^d mod n
        // If M's length is less than 2x, then it means there are missing leading 0s (For example, 162208 should be
        // 00162208)
        int diff = 2 * x - M.length();
        if (diff > 0) {
            for (int k = 0; k < diff; k++) {
                M = '0' + M;  // Add leading 0s
            }
        }
        for (int j = 0; j < M.length(); j += 2) {
            if (M.substr(j, 2) == "00")
                decrypted += ' ';  // 00 means space
            else
                decrypted += (char)stoi(M.substr(j, 2)) + 96;  // First change to ASCII, then add 96 to start from 'a'
        }
        res += decrypted;
    }
    // Write to output
    ofstream fout(output);
    fout << res;
    fout.close();
}

int main(int argc, char** argv) {
    if (argc != 3)
        quit(6);  // Check if there are less/more than one p and one q
    while (true) {
        cout << "Please enter your command:" << endl;
        string command;
        cin >> command;
        if (command == "EXIT")
            quit(0);  // Check if the user entered EXIT
        else if (command != "ENCRYPT" && command != "DECRYPT")
            quit(1);  // Check if the user entered an invalid command
        else if (command == "ENCRYPT") {
            string encryptedFile;
            cin >> encryptedFile;
            long n;
            cin >> n;
            if (cin.fail())
                quit(5);  // Check if the user enter a string as n
            string message;
            getline(cin, message);
            while (message[0] == ' ')  // Erase leading spaces
            {
                message = message.substr(1, message.length());
            }
            encrypt(encryptedFile, n, message);
        } else  // DECRYPT
        {
            string encryptedFile;
            cin >> encryptedFile;
            string decryptedFile;
            cin >> decryptedFile;
            decrypt(encryptedFile, decryptedFile, stol(argv[1]), stol(argv[2]));
        }
    }
    return 0;
}