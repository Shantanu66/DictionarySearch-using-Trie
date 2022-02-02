/*@desc Trie Articles 
 *
 * @author Rahul_Sharma, Vishwajeet_Kakde
 * 
 * @remark Path and name of files containing companies list (company.dat/txt) and file containing article to be analyzed (article.dat/txt)
 *         must be provided by user
 * 
 * @reference https://www.youtube.com/watch?v=AXjmTQ8LEoI
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <algorithm>
#include <malloc.h>
#include <queue> 
#include <ctype.h>
#include <windows.h>
#include <math.h>
#include <stack>
#include <list>
#include <string>
#include <iomanip>

using namespace std;

int *CountCompanyOccurrence = new int;

template<typename Out>
void split(const string &s, char delim, Out result);

// splits a given string based on parametrized delimiter such as space, tab, endl
vector<string> split(const string &s, char delim);

// detects articles in a string such as - and, of, is, but, etc.
bool excludeArticles(string CheckString);

// struct for each trie nodes
struct trieNode{
    map<char, trieNode> children;
    bool endOfWord;
    
    // EOW nodes of all aliases of a company name's point to a single index in a special array
	int *pointerToGlobalCountCompanyOccurrenceArray;
};

class trie{
    public:
    trieNode root;
    
    // public:
    trie();
    
    // function to insert word into trie
    void insert(string word, int CountCompanyOccurrenceIndex);
    
    // function to search if given word exists in a trie
    bool search(string word);
};