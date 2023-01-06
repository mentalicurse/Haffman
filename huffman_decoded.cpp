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
