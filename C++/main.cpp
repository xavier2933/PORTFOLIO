//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
// Purpose: Produce UI, run required fucntions
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//-----------------------------------------------------------------------------
// create fucntion to display menu and collect info
//
// @param: none
// @return: users input (number)
int dispmenu()
{
    string input;
    cout << "=======Main Menu=======" << endl;
    cout << "1. Populate hash tables" << endl;
    cout << "2. Search for a course" << endl;
    cout << "3. Search for a professor" << endl; 
    cout << "4. Display all courses" << endl;
    cout << "5. Exit" << endl;
    cin >> input;
    cout << endl;
    int number = stoi(input);
    return number;
}

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage: ./<program name> <csv file> <hashTable size>" << endl;
        return 0;
    }
    string infile = argv[1];
    string size_string = argv[2];
    int size = 0;
    int input = 0;
    size = stoi(size_string);
    bool flag = true;
    HashOpenAddressing quad(size); //creates instances of each class to acess fucntions/variables
    HashChaining chain(size);
 

    while(flag) // while loop loops until 5 is called and bool is set to false
    {
        input = dispmenu(); // calls display menu fucntion, gets input
   
        if (input == 1)
        {
            quad.bulkInsert(infile); //insert into each table
            cout << endl;
            chain.bulkInsert(infile);
            cout << endl;
            continue;
        }
        else if (input == 2) //prompt user for input, call search fucntions for each table
        {
            string year_s, number, prof_id;
            cout << "Enter the course year (e.g. 2021):" << endl;
            cin >> year_s;
            cout << "Enter the course number (e.g. 2270):" << endl;
            cin >> number;
            cout << "Enter a Professor's ID (e.g. llytellf):" << endl;
            cin >> prof_id;
            int year = stoi(year_s);
            int number_int = stoi(number);
            cout << endl;

            
            cout << "[OPEN ADDRESSING] Search for a course" << endl;
            cout << "---------------------" << endl;
            quad.search(year,number_int,prof_id);
            cout << endl;
            cout << "[CHAINING] Search for a course" << endl;
            cout << "---------------------" << endl;
            chain.search(year,number_int,prof_id);
            cout << endl;
        }
        else if(input == 3) // prompt for input, search professor tree for prof, display courses taught
        {
            string prof_id;
            cout << "Enter a Professor's ID (e.g. nscollan0): " << endl;
            cin >> prof_id;
            cout << "[OPEN ADDRESSING] Search for a professor" << endl;
            cout << "-----------------------" << endl;
            quad.profDb.publicSearchProfessor(prof_id);
            cout << endl;
            cout << "[CHAINING] Search for a professor" << endl;
            cout << "-----------------------" << endl;
            chain.profDb.publicSearchProfessor(prof_id);
            cout << endl;

        }
        else if (input == 4) // Displays all courses for each table
        {
            string letter;
            cout << "Which hash table would you like to display the courses for (O=Open Addressing, C=Chaining)?" << endl;
            cin >> letter;
            if (letter == "O")
            {
                quad.displayAllCourses();
                cout << endl;
                
            }
            else if(letter == "C")
            {
                chain.displayAllCourses();
                cout << endl;
            }
            else{
                cout << "INVALID INPUT" << endl;\
                cout << endl;
                main(argc, argv);
            }
        }
        else if (input ==5) //exits
        {
            flag = false; // triggers condition to end loop
            cout << "EXITED" << endl;
            break;
        }
        else // tells user they put in invalid input
        {
            cout << "WRONG INPUT" << endl;
            main(argc, argv);
        }
        
} 
    return 0;
}