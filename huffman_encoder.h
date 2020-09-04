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

    node(string key, int frequency)
    {
        this->key = key;
        this->frequency = frequency;
        this ->left = nullptr;
        this->right = nullptr;
    }
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
    unordered_map<string, string> codes;
    
    public:
        //Default Constructors
        huffman_encoder();

        huffman_encoder(const frequency_table &table);

        ~huffman_encoder();
        void destructorHelper(node* root);

        string get_character_code(char character) const;        
        string encode(const std::string &file_name) const;
        string decode(const std::string &file_name) const;

        // Extra Functions:
        void getCodes(node* root, string code);
};