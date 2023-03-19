#include "makepuzzle.hpp"


using namespace std;

int main()
{
    Puzzle p(4);
    
    p.createPuzzle();
    // int numz = 3;
    // int numarray[] = {1,2,3};
    // int xcoord[] = {1,2,3};
    // int ycoord[] = {1,2,3};
    int numz = 5;
    int numarray[] = {2,3,1,4,3};
    int xcoord[] = {1,1,2,3,4};
    int ycoord[] = {1,3,1,3,4};
    for(int i = 0; i < numz; i++)
    {
        Node temp;
        temp.key = numarray[i];
        temp.x = xcoord[i];
        temp.y = ycoord[i];
        p.insertNumbers(temp);
    }
    cout << "Original: " << endl;
    p.printPuzzle();
    p.Solve();
}