#include "huffman_encoder.h"

node::node(string key, int frequency)
{
     this->key = key;
     this->frequency = frequency;
     this ->left = nullptr;
     this->right = nullptr;
}

// Default Constructors:
huffman_encoder::huffman_encoder()
{}



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
     while (!priority.empty())
     {
          left = priority.top();
          priority.pop();

          right = priority.top();
          priority.pop();

          top = new node("$", left->frequency + right->frequency);
          top->left = left;
          top->right = right;
          
          priority.push(top);
     }    
}


huffman_encoder::~huffman_encoder()
{
     // Destructs the huffman_encoder object. 
     // Should free any dynamically allocated memory. C
     // Can be left empty if no memory is dynamically allocated for the object
}




string huffman_encoder::get_character_code(char character) const 
{
     // Returns the binary code representation of the character c as a string of binary digits. 
     // Returns an empty string if c is not present in the tree.

     node* root = priority.top();

     string code = getCodeHelper(character, root);

     if(code == "")
     {
          return "";
     }
     else
     {
          return code;
     }   
}

string huffman_encoder::getCodeHelper(char character, node* root) const
{
     string charString = "";
     charString.push_back(character);

     frequency_table frequency;
     int charFrequency = frequency.get_frequency(character);


     //Move Left
     if(root == nullptr)
     {
          return "";
     }     
     if(charFrequency < root->frequency)
     {
          root = root->left;
          if(root->key == "$")
          {
               get_character_code(character);
          }
     }

     //Move Right
     if (charFrequency > root->frequency)
     {

     }
}





string huffman_encoder::encode(const string &file_name) const 
{
     // Encodes the contents of the file given by file_name by converting each character to its character code and concatenating them. 
     // If the file contains a letter not present in the tree, return an empty string.

     

     string temp = file_name;
     return temp;
}



string huffman_encoder::decode(const string &string_to_decode) const {
     //Decodes string_to_decode by converting each character code to it’s ASCII character representation. 
     //If the file does not contain a valid Huffman encoding (i.e. characters other than ‘0’ or ‘1’) return an empty string.
     string temp = string_to_decode;
     return temp;
}





