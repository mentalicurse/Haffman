#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

class Node
{
	public:
	std::string key;
	 int freq;
	 Node *left, *right;
	 
	 bool operator () (const Node & x, const Node & y)
  {
    return x.size >= y.size;
  }
	Node (const std::string& str = "", int count = 0, Node * L = NULL, Node * R = NULL)
  {
    key = str;
    freq = count;
    left = L;
    right = R;
  }
  
  Node *join (Node x)
  {
    return new Node (x.key + key, x.freq + freq, new Node (x), this);
  }
};

Node *BuildTree (std::priority_queue < Node, std::vector < Node >, Node > htree)
{
  while (htree.size () > 1)
    {
      Node *n = new Node (htree.top ());
      htree.pop ();
      htree.push (*n->join (*new Node (htree.top ())));
      htree.pop ();
    }
  return new Node (htree.top ());
}

void CodingHuffman (Node * root, std::string code, std::unordered_map < std::string,
	      std::string > *codetable)
{
  if (root == nullptr)
    {
      return;
    }
  if (root->left!=NULL) CodingHuffman (root->left, code + "0", codetable);
  if (root->right!=NULL) CodingHuffman (root->right, code + "1", codetable);

   if (root->left==NULL && root->right==NULL)   (*codetable)[root->key] = code;
}

vector<bool> code;                
map<char,vector<bool> > tree;
