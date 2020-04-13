#pragma once
#include <queue>
#include "frequency_table.h"

// struct for the nodes of the tree?
struct node
{
    string key;
    int frequency;
    node* left;
    node*right;

    node(string key, int frequency);

};

struct compare
{
    bool operator()(node* left, node* right)
    {
        return (left->frequency > right->frequency);
    }
};

struct huffman_encoder 
{
    priority_queue<node*, vector<node*>, compare> priority;
    //New map for codes
    unordered_map<string, string> codes;
    

    public:
        //Default Constructors
        huffman_encoder();

        huffman_encoder(const frequency_table &table);
        ~huffman_encoder();

        string get_character_code(char character) const;
        string getCodeHelper(char character, node* root) const;
        
        string encode(const std::string &file_name) const;
        string decode(const std::string &file_name) const;


        // Other Functions:
        unordered_map<string, string> inOrderTrav();
};