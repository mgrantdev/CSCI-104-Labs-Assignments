#include "MinHeap.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

class Node {
public:
    string word;                                 // the word we are currently visiting
    int curSteps;                                // curSteps is the g-value of that word
    const bool operator<(const Node& rhs) const  // Overload < since I use MinHeap<Node>
    {
        return word < rhs.word;  // Node comparison is the alphabetical comparison of Node.word
    }
};

// Lower all letters in a word since we don't distinguish between capital and lowercase letters
void toLower(string& word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }
}

// Get the heuristic value
int heuristic(string word1, string word2) {
    int count = 0;
    for (int i = 0; i < word1.length(); i++) {
        // Heuristic is the number of incorrect letters, so when there is one I add one
        if (word1[i] != word2[i])
            count += 1;
    }
    return count;
}

int main(int argc, char* argv[]) {
    // Reading and lowering the input words
    string startWord = argv[1];
    toLower(startWord);
    string endWord = argv[2];
    toLower(endWord);

    map<string, set<string>>
            possibleWords;  // This map stores all of the possible words a word can become by only changing one letter

    // This set stores all the words in the input file so that when doing A* search, we can check if a possible next
    // word is in the input Use a set to achieve O(log(n)) lookup time complexity
    set<string> wordList;

    ifstream fin(argv[3]);
    string word;  // buffer string
    getline(fin, word);
    while (getline(fin, word)) {
        toLower(word);          // Lowering all letters in a word
        wordList.insert(word);  // Add all words in the input file to wordList
        for (int i = 0; i < word.length(); i++) {
            possibleWords[word].insert(word);
            for (int j = 0; j < 26; j++)  // Find all possible words by only changing one letter
            {
                string possibleWord = word.substr(0, i) + char('a' + j)
                                      + word.substr(i + 1, word.length());  // char('a'+j) is the possible ASCII value
                if (possibleWords[word].find(possibleWord) != possibleWords[word].end())
                    continue;  // Don't want duplicate possible words
                possibleWords[word].insert(possibleWord);
            }
        }
    }

    MinHeap<Node> pq(2);
    // All use set to achieve O(log(n)) lookup time
    set<string> visited;    // This set stores all the words we've explored to avoid repetitive visits (unless new
                            // priority is lower)
    map<string, int> minG;  // This set stores the minimum g-value of a word
    map<string, int> minP;  // This set stores the minimum priority = f*(n+1)+h of a word
    // Other initializations
    int length = startWord.length();
    Node start;
    start.word = startWord;
    start.curSteps = 0;
    int count = 0;       // count is the number of expansions
    bool found = false;  // This is to determine if there is no transformation
    set<string>::iterator it;
    pq.add(start,
           heuristic(startWord, endWord) * (length + 1)
                   + heuristic(startWord, endWord));  // priority = f*(n+1)+h, where f=g+h
    minG[startWord] = 0;  // g-value of the start word is 0 (we haven't made any explorations yet)
    visited.insert(startWord);
    while (!pq.isEmpty()) {
        Node node = pq.peek();
        pq.remove();
        string word = node.word;
        int curSteps = node.curSteps;
        // Want to update the g-value of a word if there is a shorter path. However, my heap has no update.
        // So, I'll just add any g-value of that word to the heap. But when popped, only use the smallest one.
        while (curSteps > minG[word]) {
            node = pq.peek();
            pq.remove();
            word = node.word;
            curSteps = node.curSteps;
        }
        if (word == endWord)  // There is a transformation
        {
            found = true;              // Set found to true so that don't output "No transformation later"
            cout << curSteps << endl;  // Output the length of the shortest path
            cout << count << endl;     // Output the number of expansions we've made
            break;                     // Terminate the loop
        }
        count += 1;  // Only after finding the smallest g-value of a word, we increase the number of expansions
        for (it = possibleWords[word].begin(); it != possibleWords[word].end();
             ++it)  // Traverse the possible next words
        {
            string possibleWord = *it;
            if (wordList.find(possibleWord)
                        != wordList.end()  // If this potential word is not in the wordList, just skip it
                && (visited.find(possibleWord) == visited.end()  // This word hasn't been visited yet or
                    || (curSteps + 1 + heuristic(possibleWord, endWord)) * (length + 1)
                                       + heuristic(possibleWord, endWord)
                               < minP[possibleWord]))  // There is a shorter path
            {
                visited.insert(possibleWord);
                Node newNode;
                newNode.word = possibleWord;
                // "Updating" g-value and priority
                newNode.curSteps = curSteps + 1;    // Increase g-value by 1
                minG[possibleWord] = curSteps + 1;  // Increase g-value by 1
                int priority = (newNode.curSteps + heuristic(possibleWord, endWord)) * (length + 1)
                               + heuristic(possibleWord, endWord);  // f*(n+1)+h
                minP[possibleWord] = priority;                      // f*(n+1)+h
                pq.add(newNode, priority);
            }
        }
    }
    if (!found)  // If there is no transformation
    {
        cout << "No transformation" << endl;
        cout << count << endl;
    }
}