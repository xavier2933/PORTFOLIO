#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int key;
    int x;
    int y;
    bool solved;
    vector <int> possible;
};

class Puzzle
{
    public: 
        Puzzle(int size= 0);
        void createPuzzle();
        void printPuzzle();
        void insertNumbers(Node);
        void Solve();
        bool checkSolved();
        void addElement();
        Node initTempPossible(Node);
        vector<int>  findNums(int, int);

    private:
        int size;
        Node ** puzzle;
        int repCount;
};