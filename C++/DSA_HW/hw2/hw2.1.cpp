// A Program to find the longest common 
// prefix of the given words 

#include<bits/stdc++.h> 
using namespace std; 

// Alphabet size (# of symbols) 
#define ALPHABET_SIZE (26) 

// Converts key current character into index 
// use only 'a' through 'z' and lower case 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

#define MAX 200005
string arr[MAX];
// Trie node 
struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 

	// isLeaf is true if the node represents 
	// end of a word 
	bool isLeaf; 
}; 

// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = new TrieNode; 

	if (pNode) 
	{ 
		int i; 

		pNode->isLeaf = false; 

		for (i = 0; i < ALPHABET_SIZE; i++) 
			pNode->children[i] = NULL; 
	} 

	return pNode; 
} 

// If not present, inserts key into trie 
// If the key is prefix of trie node, just marks leaf node 
void insert(struct TrieNode *root, string key) 
{ 
	int length = key.length(); 
	int index; 

	struct TrieNode *pCrawl = root; 

	for (int level = 0; level < length; level++) 
	{ 
		index = CHAR_TO_INDEX(key[level]); 
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 

		pCrawl = pCrawl->children[index]; 
	} 

	// mark last node as leaf 
	pCrawl->isLeaf = true; 
} 

// Counts and returns the number of children of the 
// current node 
int countChildren(struct TrieNode *node, int *index) 
{ 
	int count = 0; 
	for (int i=0; i<ALPHABET_SIZE; i++) 
	{ 
		if (node->children[i] != NULL) 
		{ 
			count++; 
			*index = i; 
		} 
	} 
	return (count); 
} 

// Peform a walk on the trie and return the 
// longest common prefix string 
int walkTrie(struct TrieNode *root) 
{ 
	struct TrieNode *pCrawl = root; 
	int index, cnt = 0; 
	//string prefix; 

	while (countChildren(pCrawl, &index) == 1 && 
			pCrawl->isLeaf == false) 
	{ 
		pCrawl = pCrawl->children[index]; 
		//prefix.push_back('a'+index); 
		cnt++;
	} 
	//return (prefix); 
	return cnt;
} 

// A Function to construct trie 
void constructTrie(string arr[], int a, int b, struct TrieNode *root) 
{ 
	insert(root, arr[a]);
	insert(root, arr[b]);
	return; 
} 

// A Function that returns the longest common prefix 
// from the array of strings 
int commonPrefix(string arr[], int a, int b) 
{ 
	struct TrieNode *root = getNode(); 
	constructTrie(arr, a, b, root); 

	// Perform a walk on the trie 
	return walkTrie(root); 
} 

// Driver program to test above function 
int main() 
{ 
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, q, l, a, b;
	string c;
	cin >> n;
    for (int i = 1; i <= n; ++i) {
    	cin >> l >> c;
    	if (!l) arr[i] = c;
    	arr[i] = arr[l] + c;
    }
	cin >> q;
	for (int i = 0; i < q; ++i) {
		cin >> a >> b;
		cout << commonPrefix(arr, a, b) << '\n';
	}
	return 0; 
} 
