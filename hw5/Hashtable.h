#include <string>
#include <iostream>
#include <vector>
#include <cmath> // To calculate power

template<class T>
class Hashtable
{

    public:
        Hashtable (bool debug = false, unsigned int size = 11);
        ~Hashtable ();
        int add (std::string k, const T& val);
        const T& lookup (std::string k);
        void reportAll (std::ostream& out) const;

    private:
        std::vector<T*> tableT; // Must use pointer because we don't know the initial value for T
        std::vector<std::string*> tableK; // Another table for k
        std::vector<int> rs; // r1, r2, r3, r4, r5
        std::vector<int> primes = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117}; // Resize reference
        std::vector<int> debugRs = {983132572, 1468777056, 552714139, 984953261, 261934300}; // Arbitrary r1, r2, r3, r4, r5 for debug mode
        int size;
        double curSize; // This double is to make load factor calculable. Otherwise it will always be 0
        bool debug;
        int hash (std::string k) const;
        void resize ();
};

template<class T>
Hashtable<T>::Hashtable (bool debug, unsigned int size)
{
    this->size = size;
    this->debug = debug;
    curSize = 0;
    // Initialize tableK and tableT both to full of nullptrs
    for (int i = 0; i < size; i++)
    {
        tableT.push_back(nullptr);
        tableK.push_back(nullptr);
    }
    if (debug) rs = debugRs; // If in debug mode, set rs to the hardcoded debugRs
    else // Otherwise generate 5 random rs
    {
        for (int i = 0; i < 5; i++)
        {
            rs.push_back(rand() % size);
        }
    }
}

template<class T>
Hashtable<T>::~Hashtable ()
{
    for (int i = 0; i < size; i++)
    {
        // Only deallocate when the position actually contains something
        if (tableK[i] != nullptr) delete tableK[i];
        if (tableT[i] != nullptr) delete tableT[i];
    }
}

template<class T>
int Hashtable<T>::hash(std::string k) const
{
    long long res = 0;
    std::string temp;
    int startIndex = k.length();
    std::vector<int> ws; // Stores w1, w2, w3, w4, w5
    // Leave the frontmost (<)6 letters handled at last, first focus on letters behind them
    while (startIndex >= 6) // If k's length < 6, then won't go into this while loop
    {
        int sum = 0; // w
        startIndex -= 6; // Move frontward 6 indices
        temp = k.substr(startIndex, 6); // Get the current string of length 6
        for (int i = 0; i < 6; i++)
        {
            sum += pow(27, 6-i-1) * (temp[i] - 'a' + 1); // Convert using ASCII
        }
        ws.push_back(sum);
    }
    // Handle the frontmost (<)6 letters
    int sum = 0; // w
    int endIndex = k.length() % 6; // Since the length may be less than 6, we need to specify an end index
    k = k.substr(0, endIndex);
    for (int i = 0; i < endIndex; i++)
    {
        sum += pow(27, endIndex-i-1) * (k[i] - 'a' + 1);
    }
    if (sum !=0 ) ws.push_back(sum); // The frontmost (<)6 letters could be empty, in that case, don't add its w
    for (int i = 0; i < ws.size(); i++)
    {
        res += (long long) ws[i] * rs[4-i]; // 4-i because the vector storing r1, r2, r3, r4, r5 are reversed, long long casting to avoid overflow
    }
    return res % size;
}

template<class T>
const T& Hashtable<T>::lookup (std::string k)
{
    int count = 1; // count is #collisions
    int hash = this->hash(k);
    int initialHash = hash; // Need to memorize initialHash for quadratic probing
    for (int i = 0; i < size; i++)
    {
        if (tableK[hash] == nullptr) return false; // If the hashed index has nullptr, then k is definitely not in the hashtable
        if (*tableK[hash] == k) return *tableT[hash]; // If found, return the key's corresponding value
        // Quadratic probing
        hash = initialHash + pow(count, 2);
        hash %= size;
        count += 1;
    }
    return false;
}

template<class T>
int Hashtable<T>::add (std::string k, const T& val)
{
    if (curSize / size >= 0.5) resize(); // If load factor >= 0.5, we should resize the hashtable
    int hash = this->hash(k);
    int initialHash = hash; // Need to memorize initialHash for quadratic probing
    int count = 1; // count is #collisions
    for (int i = 0; i < size; i++)
    {
        if (tableK[hash] == nullptr) // If we find an empty spot
        {
            // Create pointers of the key and the value, increase #elements by 1, and there's no need to go further
            tableK[hash] = new std::string(k);
            tableT[hash] = new T(val);
            curSize += 1;
            break;
        }
        else if (*tableK[hash] == k) return 0; // If k is already in hashtable, do nothing
        // Quadratic probing
        hash = initialHash + pow(count, 2);
        hash %= size;
        count += 1;
    }
    return count-1; // count-1 is the number of probes/collisions since I initialized count to 1
}

template<class T>
void Hashtable<T>::resize ()
{
    // Find the smallest larger size
    for (int i = 0; i < primes.size(); i++)
    {
        if (size < primes[i])
        {
            size = primes[i];
            break;
        }
    }
    if (!debug) // If we are not in debug mode, we need to regenerate 5 random rs
    {
        rs.clear(); // Clear current rs
        for (int i = 0; i < 5; i++)
        {
            rs.push_back(rand() % size);
        }
    }
    // tempK and tempT will become the new tableK and tableT
    std::vector<std::string*> tempK;
    std::vector<T*> tempT;
    // Initialize tempK and tempT to all nullptrs just like we do for tableK and tableT
    for (int i = 0; i < size; i++)
    {
        tempK.push_back(nullptr);
        tempT.push_back(nullptr);
    }
    for (int i = 0; i < tableK.size(); i++)
    {
        if (tableK[i] != nullptr) // If the original tableK has element in this position
        {
            int count = 1; // count is #collisions
            // Then get the corresponding elements in orginal tableK and tableT
            std::string* kPtr = tableK[i];
            T* valPtr = tableT[i];
            // Insert them to the new tempK and tempT
            int hash = this->hash(*tableK[i]);
            int initialHash = hash;
            for (int i = 0; i < size; i++)
            {
                if (tempK[hash] == nullptr)
                {
                    tempK[hash] = kPtr;
                    tempT[hash] = valPtr;
                    break;
                }
                // Quadratic probing
                hash = initialHash + pow(count, 2);
                hash %= size;
                count += 1;
            }
        }
    }
    // Now tempK becomes tableK and tempT becomes tableT
    tableK = tempK;
    tableT = tempT;
}

template<class T>
void Hashtable<T>::reportAll (std::ostream& out) const
{
    for (int i = 0; i < size; i++)
    {
        if(tableK[i] != nullptr) // Only report when the position actually contains something
        {
            out << *tableK[i] << " " << *tableT[i] << std::endl;
        }
    }
}