#include<fstream>
#include<sstream>
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

#define EMPTY_STRING ""

struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};

Node *getNode(char ch, int freq, Node *left, Node *right)
{
    Node *node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp
{
    bool operator()(const Node *l, const Node *r) const
    {

        return l->freq > r->freq;
    }
};

bool isLeaf(Node *root)
{
    return root->left == nullptr && root->right == nullptr;
}

void encode(Node *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
    {
        return;
    }

    if (isLeaf(root))
    {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void buildHuffmanTree(string text)
{
    // base case: empty string
    if (text == EMPTY_STRING)
    {
        return;
    }

    unordered_map<char, int> freq;
    for (char ch : text)
    {
        freq[ch]++;
    }

    priority_queue<Node *, vector<Node *>, comp> pq;

    for (auto pair : freq)
    {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1)
    {

        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    Node *root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode);

    cout << "Huffman Codes are:\n"
         << endl;
    for (auto pair : huffmanCode)
    {
        cout << pair.first << " " << pair.second << endl;
    }

    cout << "\nThe original string is:\n"
         << text << endl;
    cout << "The Length of the Original text = " << text.length() << endl;
    int beforecompression = text.length() * 8;
    cout << "In bits = " << text.length() * 8 << endl;

    string str;
    for (char ch : text)
    {
        str += huffmanCode[ch];
    }

    cout << "\nThe encoded string is:\n"
         << str << endl;
    int aftercompression = str.length();
    cout << "The Length of the Encoded String = " << aftercompression << endl;

    cout << "Total Percentage of Compression = " << 100 - (double)aftercompression / beforecompression * 100 << "%" << endl;
    if (isLeaf(root))
    {

        while (root->freq--)
        {
            cout << root->ch;
        }
    }
}

int main()
{
    cout << "ICT Project by Jeremy & Joel" << endl;
    cout << "____________________________________" << endl;
    // string text = "Hello";
    // buildHuffmanTree(text);
    ifstream f("new.txt"); //taking file as inputstream
   string str;
   if(f) {
      ostringstream ss;
      ss << f.rdbuf(); // reading data
      str = ss.str();
   }
//    cout<<str;
    buildHuffmanTree(str);
    return 0;
}