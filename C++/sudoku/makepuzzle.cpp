#include "makepuzzle.hpp"

// struct Node
// {
//     int key;
//     bool solved;
//     Node* next;
// };

// class Puzzle
// {
//     public: 
//         Puzzle(int size= 0);
//         void createPuzzle();
//         void printPuzzle();
//         void addNode();
//         void addEdge(Node*, Node*);

//     private:
//         int size;
//         int ** puzzle;
//         vector<Node*> Nodez;
// };

Puzzle::Puzzle(int size)
{
    this->size = size;
}

void Puzzle::makeBoxes()
{
    for (int i =0; i < size; i++)
    {
        Box temp;
        temp.id = i;
        temp.numbers.push_back(0);
        boxes.push_back(temp);
    }
}

void computeBounds(int size)
{
    int rows = sqrt(size);


}
void Puzzle::assignBoxes(int start, int end)
{
    for(int x = start; x < end; x++)
    {
        for(int i =start; i < end; i++)
        {
            
        }
    }
}

void Puzzle::createPuzzle()
{
    repCount = 0;
    if(!size){return;}
    puzzle = new Node*[size];
    for (int i=0; i<size; ++i)
    {
        puzzle[i] = new Node[size];
    }

    for ( int i = 0; i< size; ++i)
    {
        for (int j=0; j<size; ++j)
        {
            puzzle[i][j].key = 0;
            puzzle[i][j].x = i;
            puzzle[i][j].y = j;
            puzzle[i][j].solved = false;
            puzzle[i][j].boxID = -1;
        }
    }
    makeBoxes();
    for(int i = 0; i < size; i+=sqrt(size))
    {
        int start = i;
        int end = i+=sqrt(size);
        assignBoxes(start,end);
    }
    cout << "ID : " << boxes[puzzle[0][1].boxID].id << endl;
    return;
}


bool Puzzle::checkSolved()
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if (!puzzle[i][j].solved)
            {
                return false;
            }
        }
    }
    return true;
}


void Puzzle::printPuzzle()
{
    for(int i=0; i<size; ++i)
    {
        cout << " | ";
        for(int j=0; j<size; ++j)
        {
            cout << puzzle[i][j].key << " | ";
        }
        cout << endl;
    }
}

void Puzzle::insertNumbers(Node temp)
{
    puzzle[temp.x -1][temp.y-1].key = temp.key;
    puzzle[temp.x -1][temp.y-1].solved = true;
}

Node Puzzle::initTempPossible(Node temp)
{
    temp.possible.clear();
    for(int i = 1; i <= size; i++)
    {
        temp.possible.push_back(i);
    }
    return temp;
}

vector<int> Puzzle::findNums(int x, int y)
{
    Node temp = initTempPossible(puzzle[x][y]);
    
    vector<int> in;
    for(int i = 0; i < size; ++i)
    {
        if(puzzle[i][temp.y].key != 0)
        {
            in.push_back(puzzle[i][temp.y].key);
        }  
    }

    for(int j = 0; j < size; ++j)
    {
        if(puzzle[temp.x][j].key != 0)
        {
            in.push_back(puzzle[temp.x][j].key);
        }
    }
    sort(in.begin(), in.end());
    vector<int> result;
    set_difference(temp.possible.begin(), temp.possible.end(), in.begin(), in.end(), inserter(result, result.begin())); 
    return result;
}

void Puzzle::addElement()
{
    for(int i=0; i<size; ++i)
    {   
        for(int j=0; j<size; ++j)
        {
            if (puzzle[i][j].possible.size() == 1 && puzzle[i][j].solved == false)
            {
                puzzle[i][j].key = puzzle[i][j].possible[0];
                puzzle[i][j].possible.pop_back();
                if(puzzle[i][j].possible.size() == 0)
                {
                    puzzle[i][j].solved = true;
                }
                return;
            }
        }
    }
}

void Puzzle::Solve()
{
    for(int i=0; i<size; ++i)
    {   
        for(int j=0; j<size; ++j)
        {
            puzzle[i][j].possible.push_back(0);
            if (puzzle[i][j].key == 0)
            {
                puzzle[i][j].possible =findNums(i,j);
            }
        }
    }
    addElement();
    // cout << "test box" << boxes[0][0].elements[0][0].x << endl;

    if(!checkSolved())
    {
        if(repCount > 100)
        {
            cout << " cant be solved." << endl;
            exit(0);
        }
        // cout << "try " << endl;
        // printPuzzle();
        repCount++;
        Solve();
    }
    else{
        cout << endl << "Finished!" << repCount << endl;
        printPuzzle();
    }
}