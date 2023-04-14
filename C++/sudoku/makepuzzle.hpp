#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node
{
    int key;
    int x;
    int y;
    bool solved;
    int boxID;
    bool boxed;
    vector <int> possible;
};

struct Box
{
    int id;
    vector<int> numbers;
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
        void makeBoxes();
        void assignBoxes(int, int);
        void makeRow(int, int);
        void getNumsInBox();
        Node initTempPossible(Node);
        vector<int> findNums(int, int);

    private:
        int size;
        Node ** puzzle;
        vector<Box> boxes;
        int repCount;
};