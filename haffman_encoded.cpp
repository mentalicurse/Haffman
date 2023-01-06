#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

class Node		//класс Узел
{
	public:
	string key;
	int freq;
	Node *left, *right;
	 
bool operator () (const Node & x, const Node & y) //функция для упорядочения кучи
  {
	return x.freq >= y.freq;
  }
Node (const string& str = "", int count = 0, Node * L = NULL, Node * R = NULL) //построение узла
  {
	key = str;
	freq = count;
	left = L;
	right = R;
  }
  
Node *Unit (Node x)		//объединение узлов в один
  {
	return new Node (x.key + key, x.freq + freq, new Node (x), this);
  }
};

//кодирование символов
void CodingHuffman (Node * root, string code, unordered_map < string, string > *codetable)
{
  if (root == nullptr)
    {
      return;
    }
  if (root->left!=NULL) CodingHuffman (root->left, code + "0", codetable);
  if (root->right!=NULL) CodingHuffman (root->right, code + "1", codetable);

   if (root->left==NULL && root->right==NULL)   (*codetable)[root->key] = code;
}

//построение дерева
Node *BuildTree (priority_queue < Node, vector < Node >, Node > htree)
{
  while (htree.size () > 1)
    {
      Node *t = new Node (htree.top ());
      htree.pop ();
      htree.push (*t->Unit (*new Node (htree.top ())));
      htree.pop ();
    }
  return new Node (htree.top ());
}

void HUFFMAN () //функция кодирования
{
  int *ABC = new int[256];  //массив символов
  for (int i = 0; i < 256; i++)
    {
      ABC[i] = 0;
    }
  FILE *input = fopen ("input.txt", "r");
  if (input == nullptr)
    {
      cout<<"Файл не открывается.Исправьте ошибку!";
	  exit(0);
    }

  unsigned char c = 0;
  while (!feof (input)) //считывание символов и их частот, занесение в массив
    {
      c = fgetc (input);
      if (!feof (input))
	{
	  ABC[c]++;
	}
    }

  fclose (input);
cout<<"Частота:"<<endl;		
  priority_queue < Node, vector < Node >, Node > htree;
  for (int i = 0; i < 256; i++)	//занесение в очередь
    {	
      if (ABC[i] != 0)
	{
	  string s (1, static_cast < char >(i));

	  Node newhtree (s, ABC[i]);
	  cout << s << " := " << newhtree.freq << endl; //вывод символов и частот на экран
	  htree.push (newhtree);
	}
    }

  Node *Tree = BuildTree (htree); //построение дерева
  unordered_map < string, string > codetable;
  CodingHuffman (Tree, "", &codetable);//символы и их кодировки
	
unordered_map < string, string >::iterator it;
  cout << "Кодировка : " << endl;
    for(it=codetable.begin();it!=codetable.end();it++)
    {
      cout << it->first << " || " << it->second << endl;//вывод символа и его кодировки
    }
  c = 0;
  unsigned char k = 0;
  FILE *output = fopen ("encoded.txt", "w+");
  input = fopen ("input.txt", "r");
	
  unsigned int length = 0;
  unsigned char simvol = 0;
  unsigned int bit_length = 0;

  char count_simvol = htree.size();
  fputc(count_simvol, output);//вносим в файл количество символов
    
    for (int i = 0; i < 256; i++)
    {
        if (ABC[i] != 0)
        {
            fputc(static_cast<char>(i), output); 	//вносим символ
            fwrite(reinterpret_cast<const char*>(&ABC[i]), sizeof(long int), 1, output); //и их частоту
        }
    }
	
  while (!feof (input))//сжатие файла и запись закодированного текста
    {			
      c = fgetc (input);
      if (!feof (input))
	{
	  string s (1, c);
	  if (bit_length + codetable[s].length () <= 8)
	    {
	      for (int i = 0; i < codetable[s].length (); i++)
		{
		  simvol = simvol << 1 | (codetable[s][i]- '0');
		}
	      bit_length += codetable[s].length ();
	    }
	  else
	    {
	      for (int i = 0; i < 8 - bit_length; i++)
		{
		  simvol = simvol << 1 | (codetable[s][i] - '0');
		}
	      if (codetable[s].length () - 8 + bit_length >= 8)
		{
		  int i = 8 - bit_length;
		  while (i + 7 < codetable[s].length ())
		    {
		      k = 0;

		      for (int j = 0; j < 8; j++)
			{
			  k = k << 1 | (codetable[s][i + j] - '0');
			}

		      i += 8;
		      fputc (simvol, output);
		      simvol = k;
		    }

		  k = 0;
		  length = 0;

		  for (int j = i; j < codetable[s].length (); j++)
		    {
		      k = k << 1 | (codetable[s][j] - '0');
		      length++;
		    }
		}
	      else
		{
		  length = 0;
		  for (int i = 8 - bit_length; i < codetable[s].length (); i++)
		    {
		      k = k << 1 | (codetable[s][i] - '0');
		      length++;
		    }
		}

	      bit_length = 8;
	    }

	  if (bit_length == 8)
	    {
	      fputc (simvol, output);

	      simvol = k;
	      bit_length = length;
	      k = 0;
	      length = 0;
	    }
	}
      else if (bit_length < 8)
	{
	  simvol = simvol << (8 - bit_length);
	  fputc (simvol, output);
	}
    }

  fclose (input); //закрытие
  fclose (output);//файлов	
 
}


int main ()
{
HUFFMAN ();//функция кодирования
return 0;
}
