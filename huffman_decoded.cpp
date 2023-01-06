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
	string key;
	 int freq;
	 Node *left, *right;
	 
	 bool operator () (const Node & x, const Node & y)
  {
    return x.size >= y.size;
  }
	Node (const string& str = "", int count = 0, Node * L = NULL, Node * R = NULL)
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

Node *BuildTree (priority_queue < Node, vector < Node >, Node > htree)
{
  while (htree.size () > 1)
    {
      Node *t = new Node (htree.top ());
      htree.pop ();
      htree.push (*t->join (*new Node (htree.top ())));
      htree.pop ();
    }
  return new Node (htree.top ());
}

void DecodingHuffman(){
	int *ABC = new int[256];
  for (int i = 0; i < 256; i++)
    {
      ABC[i] = 0;
    }
  FILE *input = fopen ("encoded.txt", "r");
  if (input == nullptr)
    {
      cout<<"Файл не открывается.Исправьте ошибку!";
	  exit(0);
    }
}

int main(){
	DecodingHuffman()
}
