#include <iostream>
#include <libzvbi.h>
#include <libnet.h>
#include <fstream>
#include <algorithm>
#include "RBTree.h"
#include "Tests.h"

#include "splay.h"
#include <chrono>
#include <time.h>
#include "Trie.h"

using namespace std;
//Functionality tests for trees
void treeTests(){
    RBTree tree;

    tree.insertValue(7);
    tree.insertValue(7);
    tree.insertValue(6);
    tree.insertValue(5);
    tree.insertValue(4);
    tree.insertValue(3);
    tree.insertValue(2);
    tree.insertValue(1);
    cout << "Finding 3 in tree: " << tree.findValue(3) << "\n";
    tree.deleteValue(6);
    tree.deleteValue(7);
    tree.deleteValue(5);
    tree.deleteValue(4);
    tree.deleteValue(3);
    tree.deleteValue(2);
    tree.deleteValue(1);
    tree.deleteValue(1);
    cout << "Deleting 6: " << "\n";

    cout << "Inoder Traversal of Created Tree\n";
    tree.inorder();


    cout << "\n\nTest of splay tree\n";

    splay* rootNode = NULL;
    rootNode = Insert(5, rootNode);
    rootNode = Insert(9, rootNode);
    rootNode = Insert(3, rootNode);
    rootNode = Insert(12, rootNode);
    rootNode = Insert(0, rootNode);
    rootNode = Insert(6, rootNode);
    cout << "Deleting -" << "\n";
    Delete(0, rootNode);
    InOrder(rootNode);

}

//Data collection function for RBTree
//void RBData(){

//}

int* arrayFromDataFile(string filename){
    string line;
    static int dataArray[1000000];
    ifstream infile;
    infile.open(filename);
    int index = 0;
    while(getline(infile, line)){
        dataArray[index] = stoi(line);
        index++;
    }
    return dataArray;
}

double splayRuntime(int size){
    //Run n insertions
     splay* rootNode = NULL;
    int* data = arrayFromDataFile("descendingNums.txt");
    int value;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        value = *(data + i);
        rootNode = Insert(value, rootNode);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return totalTime;
}

double SplaySearchRuntime(int size){
    //Fill tree with data
    splay* rootNode = NULL;
    int* data = arrayFromDataFile("descendingNums.txt");
    int value;
    for (int i = 0; i < size; ++i) {
        value = *(data + i);
        rootNode = Insert(value, rootNode);
    }
    //Search data from array
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        value = *(data + i);
        Search(value, rootNode);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return totalTime;
}

double SplayRemoveRuntime(int size){
    //Fill tree with data
    splay* rootNode = NULL;
    int* data = arrayFromDataFile("descendingNums.txt");
    int value;
    for (int i = 0; i < size; ++i) {
        value = *(data + i);
        rootNode = Insert(value, rootNode);
    }
    //Search data from array
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        value = *(data + i);
        Delete(value, rootNode);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return totalTime;
}

//Data collection function for splay tree
double splayData(){
    double result;
    //Run 10k, 50k, 100k, up to 1mil
    //Run each test 10 times and take average
    double average;
    cout << "Testing Splay Tree" << "\n";


    //10k average
    cout << "10k,";
    average = 0;
    for (int j = 0; j < 10; ++j) {
        //result = splayRuntime(10000);
        //result = SplaySearchRuntime(10000);
        result = SplayRemoveRuntime(10000);

        average = average + result;
    }
    cout << average/10 << "\n";

    //50k average
    cout << "50k,";
    average = 0;
    for (int j = 0; j < 10; ++j) {
        //result = splayRuntime(50000);
        result = SplayRemoveRuntime(50000);
        average = average + result;
    }
    cout << average/10 << "\n";

    //100-1mil averages
    for (int i = 100000; i < 1000001; i = i + 100000) {
        average = 0;
        for (int j = 0; j < 10; ++j) {
            //result = splayRuntime(i);
            //result = SplaySearchRuntime(i);
            result = SplayRemoveRuntime(i);
            average = average + result;
        }
        cout << i/1000 << "k," << average << "\n";
    }
}

double RBRuntime(int size){
    //Run n insertions
    RBTree tree;
    int* data = arrayFromDataFile("descendingNums.txt");
    int value;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        value = *(data + i);
        tree.insertValue(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return totalTime;
}

double RBSearchRuntime(int size){
    //Fill tree with data
    RBTree tree;
    int* data = arrayFromDataFile("descendingNums.txt");
    int value;
    for (int i = 0; i < size; ++i) {
        value = *(data + i);
        tree.insertValue(value);
    }
    //Search data from array
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        value = *(data + i);
        tree.findValue(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return totalTime;
}

double RBRemoveRuntime(int size){
    //Fill tree with data
    RBTree tree;
    int* data = arrayFromDataFile("descendingNums.txt");
    int value;
    for (int i = 0; i < size; ++i) {
        value = *(data + i);
        tree.insertValue(value);
    }
    //Remove Data from array
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        value = *(data + i);
        //cout << i << " : " << value << "\n";
        tree.deleteValue(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return totalTime;
}

//Data collection function for red black tree
double RBData(){
    double result;
    //Run 10k, 50k, 100k, up to 1mil
    //Run each test 10 times and take average
    double average;
    cout << "Testing Red Black Tree" << "\n";

    //10k average
    cout << "10k,";
    average = 0;
    for (int j = 0; j < 10; ++j) {
        //result = RBRuntime(10000);
        //result = RBSearchRuntime(10000);
        result = RBRemoveRuntime(10000);
        average = average + result;
    }
    cout << average/10 << "\n";

    //50k average
    cout << "50k,";
    average = 0;
    for (int j = 0; j < 10; ++j) {
        //result = RBRuntime(50000);
        //result = RBSearchRuntime(50000);
        result = RBRemoveRuntime(10000);
        average = average + result;
    }
    cout << average/10 << "\n";

    //100-1mil averages
    for (int i = 100000; i < 1000001; i = i + 100000) {
        average = 0;
        for (int j = 0; j < 10; ++j) {
            //result = RBRuntime(i);
            //result = RBSearchRuntime(i);
            result = RBRemoveRuntime(10000);
            average = average + result;
        }
        cout << i/1000 << "k," << average << "\n";
    }
}

void genData(){
    srand(time(NULL));
    //Generate random data
    ofstream randomFile;
    randomFile.open("randomNums.txt", ios::out);
    int randArray[1000001];

    for (int i = 0; i < 1000000; ++i) {
        int number = rand() % 1000 + 1;
        //cout << number << "\n";
        randomFile << number << "\n";
        randArray[i] = number;
    }
    randomFile.close();
    sort(randArray, randArray + 1000001);

    //Generate ascending data
    ofstream ascending;
    ascending.open("ascendingNums.txt", ios::out);
    for (int j = 0; j < 1000000; ++j) {
        ascending << randArray[j] << "\n";
    }
    ascending.close();

    //Generate descending data
    ofstream descending;
    descending.open("descendingNums.txt", ios::out);
    for (int k = 1000000; k > 0; --k) {
        descending << randArray[k] << "\n";
    }
    descending.close();
}

//int main()
//{
//    //genData();
//    //treeTests();
//    //RBData();
//    splayData();
//
//    return 0;
//}

//int main()
//{
//
//
//    // Input keys (use only 'a' through 'z'
//    // and lower case)
//    string keys[] = {"google.com", "facebook.com", "amazon.com"};
//    int n = sizeof(keys)/sizeof(keys[0]);
//
//    struct TrieNode *root = getNode();
//
//    // Construct trie
//    for (int i = 0; i < n; i++)
//        insert(root, keys[i]);
//
//    // Search for different keys
//    search(root, "1234")? cout << "Yes\n" :
//    cout << "No\n";
//    search(root, "1123")? cout << "Yes\n" :
//    cout << "No\n";
//    return 0;
//
//}

