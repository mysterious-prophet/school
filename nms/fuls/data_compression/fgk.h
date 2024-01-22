#ifndef FGK_H
#define FGK_H

#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm>

using namespace std;



class fgk
{
    struct Node{
            char c;
            int weight;
            Node *parent;
            Node *left;
            Node *right;
        };

        Node *root;
        unordered_map<char, Node*> getNode;
        string inputfile, outputfile;

        vector<Node*> levelOrder();

        void update(char a);

        void binstr2file(string x);

        void code();

        void decode();

        public:
        fgk(string file1, string file2, bool mode);
};

#endif // FGK_H
