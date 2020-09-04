#include "huffman_encoder.h"

// Default Constructors:
huffman_encoder::huffman_encoder(){}



huffman_encoder::huffman_encoder(const frequency_table &table)
{
     // Constructs a huffman_encoder object. 
     // This should build a Huffman tree using all the non-zero entries of the table (i.e. do not make leaves or generates codes for characters which are not present in the table or have a frequency of 0 in the table)

     frequency_table frequency;
     node* left;
     node* right;
     node* top;
     
     // Creates the nodes for the tree and places them in the priority queue
     for(auto i = table.frequencyTable.begin(); i != table.frequencyTable.end(); i++)
     {
          if(i->second > 0)
          {
               priority.push(new node(i->first, i->second));
          }
     }

     // Creates a large tree of the nodes
     while (priority.size() != 1)
     {
          left = priority.top();
          priority.pop();

          right = priority.top();
          priority.pop();

          top = new node("NULL", left->frequency + right->frequency);
          top->left = left;
          top->right = right;
          
          priority.push(top);
     }

     // Makes an unordered map of codes.
     node* root = priority.top();
     getCodes(root, "");
}


huffman_encoder::~huffman_encoder()
{
     // Destructs the huffman_encoder object. 
     // Should free any dynamically allocated memory. C
     // Can be left empty if no memory is dynamically allocated for the object

     node* root = priority.top();
     destructorHelper(root);
}
void huffman_encoder::destructorHelper(node* root)
{
     if(root != nullptr)
     {
          if(root->left != nullptr)
          {
               destructorHelper(root->left);
          }
          if(root->right != nullptr)
          {
               destructorHelper(root->right);
          }
          delete root;
     }
}




string huffman_encoder::get_character_code(char character) const 
{
     // Returns the binary code representation of the character c as a string of binary digits. 
     // Returns an empty string if c is not present in the tree.

     string letter = "";
     letter.push_back(character);
     string code = codes.at(letter);
     return code;
}


void huffman_encoder::getCodes(node* root, string code)
{
     int i = 0;
     if(root == nullptr)
     {
          return;
     }
     if(root->left == nullptr && root->right == nullptr)
     {
          if (i == 0)
          {
               codes.emplace(root->key, code);
               return;
          }
          else
          {
               codes.emplace(root->key, code);
          }
     } 
     getCodes(root->left, code + "0");
     getCodes(root->right, code + "1");
}


string huffman_encoder::encode(const string &file_name) const 
{
     // Encodes the contents of the file given by file_name by converting each character to its character code and concatenating them. 
     // If the file contains a letter not present in the tree, return an empty string.

     int occurrence = 0;
     char c;
     string fileCodes = "";

     ifstream file;
     file.open(file_name);
     if(file.is_open())
     {
          while(file.get(c))
          {
               occurrence++;
               string letter = "";
               letter.push_back(c);

               auto got = codes.find(letter);
               if(got == codes.end())
               {
                    return "";
               }
               else
               {
                    string temp = codes.at(letter);
                    for(unsigned int i= 0; i < temp.length(); i++)
                    {
                         fileCodes.push_back(temp[i]);
                    }               
               }
          }
     }
     if(occurrence == 1)
     {
          fileCodes += '0';
     }
     return fileCodes;
}



string huffman_encoder::decode(const string &string_to_decode) const {
     //Decodes string_to_decode by converting each character code to it’s ASCII character representation. 
     //If the file does not contain a valid Huffman encoding (i.e. characters other than ‘0’ or ‘1’) return an empty string.

     node* root = priority.top();
     node* temp = priority.top();
     string decoded = "";

     if(string_to_decode.length() == 1)
     {
          decoded += root->key;
     }
     else
     {
          for(unsigned int i = 0; i < string_to_decode.length(); i++)
          {
               //Improper encoding
               if (string_to_decode[i] != '0' && string_to_decode[i] != '1')
               {
                    return "";
               }
               if (string_to_decode[i] == '0')
               {
                    root = root->left;
               }
               if(string_to_decode[i] == '1')
               {
                    root = root->right;
               }
               // If node is a Leaf
               if(root->left == nullptr && root->right == nullptr)
               {
                    decoded += root->key;
                    root = temp;
               }          
          }    
     }
     return decoded;
}