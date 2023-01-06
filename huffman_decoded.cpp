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
  long int *ABC = new long int[256];
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
	unsigned char count = 0;
    unsigned int count_simvol = 0;
    count = fgetc(input);
    if (!feof(input))
    {
       count_simvol =(unsigned int) count;
    }

    unsigned char c = 0;

    for (int i = 0; i < count_simvol; i++)
    {
        c = fgetc(input);
        if (!feof(input))
        {
            fread(reinterpret_cast<char*>(&ABC[c]), sizeof(long int), 1, input);
        }
        else
        {
            cout<<"Распаковка файла не произошла.Ошибка!";
		exit(0);
        }
    }

    priority_queue<Node, vector<Node>, Node> htree;
    for (int i = 0; i < 256; i++)
    {
        if (ABC[i] != 0)
        {
            string s(1, static_cast<char>(i));

            Node newhtree(s, ABC[i]);
            htree.push(newhtree);
        }
    }
    c = 0;
    Node *t = BuildTree(htree);

    FILE* output = fopen("output.txt", "w+");
    Node *nodes = t;
    unsigned char simvol = 0;
    while (!feof(input))
    {  
        c = fgetc(input);
        if (!feof(input))
        {
            for (int i = 7; i > -1; i--)
            {
                if (((c >> i) & 1) == 1) 
                {
                    if (nodes->right == NULL)
                    {
                        simvol = nodes->key[0];
                        if (ABC[simvol] > 0)
                        {
                            ABC[simvol]--;
                            fputc(simvol, output);
                            nodes = t->right;
                        }
                    }
                    else
                    {
                        nodes = nodes->right;
                    }
                }
                else if (((c >> i) & 1) == 0)
                {
                    if (nodes->left == NULL)
                    {
                        simvol = nodes->key[0];
                        if (ABC[simvol] > 0)
                        {
                            fputc(simvol, output);
                            nodes = t->left;
                            ABC[simvol]--;
                        }
                    }
                    else
                    {
                        nodes = nodes->left;
                    }
                }
            }
       }
    }

    fclose(input);
    fclose(output);
}

int main(){
	DecodingHuffman()
}
