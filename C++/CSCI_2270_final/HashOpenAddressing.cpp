//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
// Purpose: Creates a hash table, inserts values from file using open addressing
// as the collison resolution method.
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"

using namespace std;

//-----------------------------------------------------------------------------
// Create hash table using, initializing every index to NULL
//
// @param: none
// @return: none
HashOpenAddressing::HashOpenAddressing(int size)
{
    this->hashTableSize = size; // set size
    // nums = 0;
    // numc = 0;
    hashTable = new Course*[hashTableSize]; // create table of double pointers
    for (int i =0; i < hashTableSize; i++)
    {
        hashTable[i] = NULL; // set everything to null
    }
}

//------------------------------------------------------------------------------
// default destructor, deletes table

// @param: none 
// @return: none
HashOpenAddressing::~HashOpenAddressing()
{
    for(int i = 0; i < hashTableSize; i++) // loop through and destory
    {
        delete hashTable[i];
    }
    delete[] hashTable;
    hashTable = NULL;
}

//------------------------------------------------------------------------------
// hash function. Uses modulo
//
// @param: none
// @return: newindex (hash value)
int HashOpenAddressing::hash(int courseNumber)
{
    
    return courseNumber % hashTableSize; // get hash value using modulo
}

//------------------------------------------------------------------------------
// bulk insert function for open addressing. Parses through each data point in file
// using a while loop, then adds professor to professor BST before hashing and 
// performing quadratic probing, if neccessary
//
// @param: file name
// @return: none
void HashOpenAddressing::bulkInsert(string filename)
{
    int numsearches = 0;
    int numcollisions = 0;
    string line;
    ifstream in(filename);
    int counter = 0;
    int i = 0;
    getline(in,line);
    int counter2 = 0;
    //ProfBST *tree = new ProfBST();
    
    while(getline(in, line) && counter2 < hashTableSize) // loop through each line and get data
    {
        
        Course *c = new Course;
        stringstream ss(line);
        string field;
        counter = 0;
        string profid;
        string profname;
        

        while(getline(ss,field,',')) // increment getline by the correct delimiters
        {
            if(counter == 0)
            {
                c->year = stoi(field);
                //cout << field << endl;
            }
            else if(counter == 1)
            {
                c->department = field;
            }
            else if(counter == 2)
            {
                c->courseNum = stoi(field);
            }else if(counter == 3)
            {
                c->courseName = field;
            }else if(counter == 4)
            {
                // Professor *prof = new Professor;
                profid = field;
                // c->prof = prof;
                // c->prof->profId = field;
            }
            else if(counter == 5)
            {
                profname = field;
                // c->prof->profName = field;
            }
            else if(counter == 6)
            {
                profname = profname + " " + field;
                
            }
            
            counter++;
        }
        
        Professor* temp = profDb.searchProfessor(profid); // check if prof is in tree already
        if(!temp)
        {
            profDb.addProfessor(profid, profname); // add if no
        }
        Professor* temp2 = profDb.searchProfessor(profid); 
        temp2->coursesTaught.push_back(c); // now add course
        c->prof = temp2;
        int index = hash(c->courseNum); // get inital hash value
        
        if(hashTable[index]) // check if spot is occupied
        {
            numcollisions++;
            int x = 0;
            while(hashTable[index]) // if yes, quadratic probe unitl we find an empty one
            {
                x++;
                //index = (index + x*x) % hashTableSize;
                index = (index + x*x) % hashTableSize;
                numsearches++;
            }
        }
        hashTable[index] = c;
        
        counter2++;  
    }
    cout << "[OPEN ADDRESSING] Hash table poulated" << endl;
    cout << "---------------------" << endl;
    cout << "Collisions using open addressing: " << numcollisions << endl;
    cout << "Search operations using open addressing: " << numsearches << endl;

}

//------------------------------------------------------------------------------
// Search fucntion. Searches hash table and associated linked lists for a course 
// with inputted properties
//
// @param: courseYear, courseNumber, profId
// @return: none
void HashOpenAddressing::search(int courseYear, int courseNumber, string profId)
{
    int nums = 0;
    int numc = 0;
    int i = 0;
    int newindex = hash(courseNumber);
    //nums++;
    if (newindex > hashTableSize) // check if index gets too big
    {
        cout << "too big" << endl;
        return;
    }
    // check if first value matches
    if(hashTable[newindex]->year == courseYear && hashTable[newindex]->prof->profId == profId && hashTable[newindex]->courseNum == courseNumber)
    {
        cout << "Search operations using open addressing: " << numc << endl;
        displayCourseInfo(hashTable[newindex]);
        return;
    }
    else  // quadratic probe until we find the right one
    {
        numc++;
        int z = 0;
        bool flag = true;
        while(flag)
        {
            
            z++;
            newindex = (newindex + z*z) % hashTableSize;
            if (!hashTable[newindex])
            {

                flag = false;
                displayCourseInfo(NULL);
                return;
            }
            nums++;
           
            if(hashTable[newindex]->year == courseYear && hashTable[newindex]->prof->profId == profId && hashTable[newindex]->courseNum == courseNumber)
            {
                cout << "Search operations using open addressing: " << nums << endl;
                displayCourseInfo(hashTable[newindex]);
                return;
            }
        }
    }
    displayCourseInfo(NULL);
    return;
}

//------------------------------------------------------------------------------
// displays all courses
//
// @param: none
// @return: none 
void HashOpenAddressing::displayAllCourses()
{
    cout << "[OPEN ADDRESSING] displayAllCourses()" << endl;
    cout << "-------------------" << endl;
    //Course *temp = new Course;
    {
    for(int i = 0; i < hashTableSize; i++) // loop through, diplay everything
    {
        Course *temp = new Course;
        temp = hashTable[i];
        displayCourseInfo(temp);
    }
    }
    
}

//------------------------------------------------------------------------------
// displays one course's info
//
// @param: Course pointer
// @return: none
void HashOpenAddressing::displayCourseInfo(Course* c)
{
    //display req'd stuff
	if(c)
    {
        cout << c->year << " " << c->courseName << " " << c->prof->profName << endl;
    }
    else{
        cout << "course NOT FOUND" << endl;
    }
}