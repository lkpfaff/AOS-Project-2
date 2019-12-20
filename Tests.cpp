//
// Created by liam on 12/16/19.
//

#include "Tests.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include "Trie.h"
#include "SplayTree.h"
#include <map>
#include <string>

using namespace std;
struct TrieNode
{
    map<char,TrieNode*> children;
    int prefixes;
    bool endofword;
    TrieNode()
    {
        prefixes=0;
        endofword=false;
    }
};
void insert(TrieNode *root,string word)
{
    TrieNode *current=root;
    for(int i=0;i<word.size();i++)
    {
        char ch=word[i];
        TrieNode *node=current->children[ch];
        if(!node)
        {
            node=new TrieNode();
            current->children[word[i]]=node;
        }
        current=node;
        current->prefixes++;
    }
    current->endofword=true;
}
bool search(TrieNode *root,string word)
{
    TrieNode *current=root;
    for(int i=0;i<word.size();i++)
    {
        char ch=word[i];
        TrieNode *node=current->children[ch];
        if(!node)
            return false;
        current=node;
    }
    return current->endofword;
}
int count_prefix(TrieNode *root,string word)
{
    TrieNode *current=root;
    for(int i=0;i<word.size();i++)
    {
        char ch=word[i];
        TrieNode *node=current->children[ch];
        if(!node)
        {
            return 0;
        }
        current=node;
    }
    return current->prefixes;
}

string* getStructureData(){
    string line;
    static string dataArray[1000];
    ifstream infile;
    infile.open("structureData.txt");
    int index = 0;
    while(getline(infile, line)){
        //cout << line << "\n";
        dataArray[index] = line;
        //cout << dataArray[index] << "\n";
        index++;
    }
    infile.close();
    return dataArray;
}
string* getTestData(){
    string line;
    static string dataArray[1000600];
    ifstream infile;
    infile.open("data.txt");
    int index = 0;
    while(getline(infile, line)){
        //cout << line << "\n";
        dataArray[index] = line;
        //cout << dataArray[index] << "\n";
        index++;
    }
    infile.close();
    return dataArray;
}
string* arrayFromDataFile1(string filename, int size){
    string line;
    string* dataArray = new string[size];
    ifstream infile;
    infile.open(filename);
    int index = 0;
    while(index < size && getline(infile, line)){
        dataArray[index] = line;
        //cout << dataArray[index] << "\n";
        index++;
    }
    return dataArray;
}

void trieDataRandom() {
    //Get testing data
    string* dataArray = getTestData();
    //Fill trie
    TrieNode *root = new TrieNode();
    string* structureArray = getStructureData();
    for (int i = 0; i < 1000; ++i) {
        insert(root, structureArray[i]);
//        search(root, dataArray[i])? cout << "yes\n" :
//        cout << "no\n";
    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        search(root, dataArray[j]);

    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        search(root, dataArray[j]);

    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "50K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            search(root, dataArray[j]);

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }

}

void trieRepeat(){
//Fill trie
    //Get testing data
    string* dataArray = getTestData();
    //Fill trie
    TrieNode *root = new TrieNode();
    string* structureArray = getStructureData();
    for (int i = 0; i < 1000; ++i) {
        insert(root, structureArray[i]);
//        search(root, dataArray[i])? cout << "yes\n" :
//        cout << "no\n";
    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        for (int i = 0; i < rand() % 5 + 1; ++i) {
            search(root, dataArray[j]);
        }

    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        for (int i = 0; i < rand() % 5 + 1; ++i) {
            search(root, dataArray[j]);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            for (int i = 0; i < rand() % 5 + 1; ++i) {
                search(root, dataArray[j]);
            }

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";
    }
}

void trieSearchEngine(){
//Fill trie
    //Get testing data
    string* dataArray = getTestData();
    //Fill trie
    TrieNode *root = new TrieNode();
    string* structureArray = getStructureData();
    for (int i = 0; i < 1000; ++i) {
        insert(root, structureArray[i]);
//        search(root, dataArray[i])? cout << "yes\n" :
//        cout << "no\n";
    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        search(root, "google.com");
        search(root, dataArray[j]);


    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        search(root, "google.com");
        search(root, dataArray[j]);

    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            search(root, "google.com");
            search(root, dataArray[j]);

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }
}

void hmapRandom() {
    //Get testing data
    string* dataArray = getTestData();
    //Fill trie
    string* structureArray = getStructureData();
    unordered_map<string, int> umap;
    for (int i = 0; i < 1000; ++i) {
        umap.insert(make_pair(structureArray[i], 2));

    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        umap.find(dataArray[j]);


    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        umap.find(dataArray[j]);

    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            umap.find(dataArray[j]);

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }

}

void hmapRepeat(){
//Get testing data
    string* dataArray = getTestData();
    //Fill trie
    string* structureArray = getStructureData();
    unordered_map<string, int> umap;
    for (int i = 0; i < 1000; ++i) {
        umap.insert(make_pair(structureArray[i], 2));
//        search(root, dataArray[i])? cout << "yes\n" :
//        cout << "no\n";
    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        for (int i = 0; i < rand() % 5 + 1; ++i) {
            umap.find(dataArray[j]);
        }

    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        for (int i = 0; i < rand() % 5 + 1; ++i) {
            umap.find(dataArray[j]);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            for (int i = 0; i < rand() % 5 + 1; ++i) {
                umap.find(dataArray[j]);
            }

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }
}

void hmapSearchEngine(){
    //Get testing data
    string* dataArray = getTestData();
    //Fill trie
    string* structureArray = getStructureData();
    unordered_map<string, int> umap;
    for (int i = 0; i < 1000; ++i) {
        umap[structureArray[i]] = rand() % 1000 + 1;
//        search(root, dataArray[i])? cout << "yes\n" :
//        cout << "no\n";
    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        umap.find("google.com");
        umap.find(dataArray[j]);


    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        umap.find("google.com");
        umap.find(dataArray[j]);

    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            umap.find("google.com");
            umap.find(dataArray[j]);

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }
}

void rbRandom() {
    //Get testing data
    string* dataArray = getTestData();
    //Fill trie
    string* structureArray = getStructureData();
    map<string, int> umap;

    for (int i = 0; i < 1000; ++i) {
        umap.insert(make_pair(structureArray[i], 2));

    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        umap.find(dataArray[j]);


    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        umap.find(dataArray[j]);

    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            umap.find(dataArray[j]);

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }

}

void rbRepeat(){
    //Get testing data
    string* dataArray = getTestData();
    //Fill trie
    string* structureArray = getStructureData();
    map<string, int> umap;

    for (int i = 0; i < 1000; ++i) {
        umap.insert(make_pair(structureArray[i], 2));
//        search(root, dataArray[i])? cout << "yes\n" :
//        cout << "no\n";
    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        for (int i = 0; i < rand() % 5 + 1; ++i) {
            umap.insert(make_pair(structureArray[i], 2));
        }

    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        for (int i = 0; i < rand() % 5 + 1; ++i) {
            umap.insert(make_pair(structureArray[i], 2));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            for (int i = 0; i < rand() % 5 + 1; ++i) {
                umap.insert(make_pair(structureArray[i], 2));
            }

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }
}

void rbSearchEngine(){
//Get testing data
    string* dataArray = getTestData();
    //Fill trie
    string* structureArray = getStructureData();
    map<string, int> umap;
    for (int i = 0; i < 1000; ++i) {
        umap.insert(make_pair(structureArray[i], 2));
//        search(root, dataArray[i])? cout << "yes\n" :
//        cout << "no\n";
    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        umap.find("google.com");
        umap.find(dataArray[j]);


    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        umap.find("google.com");
        umap.find(dataArray[j]);

    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            umap.find("google.com");
            umap.find(dataArray[j]);

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }
}

void splayRandom() {
    //Get testing data
    string* dataArray = getTestData();
    //Fill trie
    string* structureArray = getStructureData();
    SplayTree<string, int> a;

    for (int i = 0; i < 1000; ++i) {
        a.insert(structureArray[i], rand()% 1000 + 1);
    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        a.search(dataArray[j]);


    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        a.search(dataArray[j]);

    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            a.search(dataArray[j]);

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }

}

void splayRepeat(){
///Get testing data
    string* dataArray = getTestData();
    //Fill trie
    string* structureArray = getStructureData();
    SplayTree<string, int> a;
    for (int i = 0; i < 1000; ++i) {
        a.insert(structureArray[i], rand()% 1000 + 1);
//        search(root, dataArray[i])? cout << "yes\n" :
//        cout << "no\n";
    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        for (int i = 0; i < rand() % 5 + 1; ++i) {
            a.search(dataArray[j]);
        }

    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        for (int i = 0; i < rand() % 5 + 1; ++i) {
            a.search(dataArray[j]);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            for (int i = 0; i < rand() % 5 + 1; ++i) {
                a.search(dataArray[j]);
            }

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }
}

void splayEngine(){
    //Get testing data
    string* dataArray = getTestData();
    //Fill trie
    string* structureArray = getStructureData();
    SplayTree<string, int> a;
    for (int i = 0; i < 1000; ++i) {
        a.insert(structureArray[i], rand()% 1000 + 1);
//        search(root, dataArray[i])? cout << "yes\n" :
//        cout << "no\n";
    }
    //Search and time
    //10000
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j) {
        a.search("google.com");
        a.search(dataArray[j]);


    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //50000
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j) {
        a.search("google.com");
        a.search(dataArray[j]);

    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "10K total: " << totalTime << "\n";

    //100000-1mil
    for (int k = 100000; k < 1000001; k = k + 100000) {
        start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < k; ++j) {
            a.search("google.com");
            a.search(dataArray[j]);

        }
        end = std::chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << k/10 << "k total: " << totalTime << "\n";


    }
}



int main(){
    //arrayFromDataFile1("top-sites-text.txt");
    //Test Tries
    //trieDataRandom();
    //trieRepeat();
    //trieSearchEngine();

    //Hashmap
    //hmapRandom();
    //hmapRepeat();
    //hmapSearchEngine();

    //Red Black
    //rbRandom();
    //rbRepeat();
    //rbSearchEngine();

    //Splay Tree
    //splayRandom();
    //splayRepeat();
    splayEngine();
    return 0;
}