#include <iostream>
#include <string>
#include <vector>

using namespace std;

// path is the current string
// we need to store a vector of the input in's index of every letter in path to include repeat paths
struct node {
    vector<int> pathIndices;
    string path;
};

// check if a number num is in vector vec
bool inVector(int num, vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) {
        if (num == vec[i]) {
            return true;
        }
    }
    return false;
}

// dfs
void permutations(std::string in) {
    // initial settings
    vector<string> result;
    vector<node> stack;
    node start;
    vector<int> startVector;
    startVector.push_back(-1);
    start.pathIndices = startVector;
    start.path = "";
    stack.push_back(start);

    while (stack.size() != 0) {
        node cur = stack.back();
        stack.pop_back();
        vector<int> pathIndices = cur.pathIndices;
        string path = cur.path;

        // we have found a permutation
        if (path.length() == in.length()) {
            result.push_back(path);
        }

        for (int i = 0; i < in.length(); i++) {
            // find all remaining letters of the input in which are not in current path so that we can add them to path
            // to do permutations we use index to compare because if there are repeating letters in different indices
            // then only using letter to compare will return true
            if (!inVector(i, pathIndices)) {
                node newNode;
                newNode.pathIndices = pathIndices;
                newNode.pathIndices.push_back(i);
                newNode.path = path + in[i];
                stack.push_back(newNode);
            }
        }
    }

    // print the result
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }
}