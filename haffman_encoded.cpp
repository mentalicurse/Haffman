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

void CodingHuffman (Node * root, std::string code, std::unordered_map < std::string, std::string > *codetable)
{
  if (root == nullptr)
    {
      return;
    }
  if (root->left!=NULL) CodingHuffman (root->left, code + "0", codetable);
  if (root->right!=NULL) CodingHuffman (root->right, code + "1", codetable);

   if (root->left==NULL && root->right==NULL)   (*codetable)[root->key] = code;
}


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

void HUFFMAN ()
{
  int *ABC = new int[256];
  for (int i = 0; i < 256; i++)
    {
      ABC[i] = 0;
    }
  FILE *input = fopen ("input.txt", "r");
  if (input == nullptr)
    {
      std::cout<<"Файл не открывается.Исправьте ошибку!";
	  exit();
    }

  unsigned char c = 0;
  while (!feof (input))
    {
      c = fgetc (input);
      if (!feof (input))
	{
	  ABC[c]++;
	}
    }

  fclose (input);

  std::priority_queue < Node, std::vector < Node >, Node > htree;
  for (int i = 0; i < 256; i++)
    {	
      if (ABC[i] != 0)
	{
	  std::string s (1, static_cast < char >(i));

	  Node newhtree (s, ABC[i]);
	  std::cout << s << " : " << newhtree.size << std::endl;
	  htree.push (newhtree);
	}
    }

  Node *Tree = BuildTree (htree);
  std::unordered_map < std::string, std::string > codetable;
  CodingHuffman (Tree, "", &codetable);
	
}


int main ()
{
HUFFMAN ();
}
