//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
// Purpose: Fucntions to create, populate, and address collisons using chaining
// Called from main.
//-----------------------------------------------------------------------------

#include "HashChaining.h"

using namespace std;

//-----------------------------------------------------------------------------
// Create hash table using, initializing every index to NULL
//
// @param: none
// @return: none
HashChaining::HashChaining(int size)
{
    this->hashTableSize = size; // set size
    
    hashTable = new Course*[hashTableSize]; // create instance of table w/ double ptr
    for (int i =0; i < hashTableSize; i++)
    {
        hashTable[i] = NULL; // set each value to null
    }
}

//------------------------------------------------------------------------------
// Helper to delete the table and associated linked lists.

// @param course pointer
// @return -none
void deletehelper(Course* c)
{
    Course *current = c; // loop through, delete each course
    Course *temp = NULL;
    while(current != NULL)
    {
        temp = current->next;
        delete current;
        current = temp;
    }
}

//------------------------------------------------------------------------------
// default destructor, deletes table

// @param: none 
// @return: none
HashChaining::~HashChaining()
{
    for (int i =0; i < hashTableSize; i++) // loop through, call delete helper for each
    {
        Course *temp = hashTable[i];
        if(temp)
        {
            deletehelper(temp);
        }
    }
    delete[] hashTable;
}

//------------------------------------------------------------------------------
// hash function. Uses modulo
//
// @param: none
// @return: newindex (hash value)

int HashChaining::hash(int courseNumber)
{
    int i = 0; // calc hash value using modulo
    int newindex = (courseNumber + i * i)%hashTableSize;
    return newindex;
}

//------------------------------------------------------------------------------
// bulk insert. Inserts all values from the file into the hash table in one function.
// I used a while loop to read in each data point from the file before adding the professor
// into the tree and placing the course into its respective index and location in 
// linked list
//
// @param: filename
// @return: none
void HashChaining::bulkInsert(string filename)
{
    //initialize vars
    int nums = 0;
    int numc = 0;
    string line;
    ifstream in(filename);
    int counter = 0;
    int i = 0;
    getline(in,line);
    int counter2 = 0;
    
    while(getline(in, line) && counter2 < hashTableSize) // loop through each line, collect input, insert into BST, table
    {
        
        Course *c = new Course;
        stringstream ss(line);
        string field;
        counter = 0;
        string profid;
        string profname;
        

        while(getline(ss,field,',')) // parse through each comma/space to get correct input
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
            profDb.addProfessor(profid, profname); // add if prof is not in tree
        }
        Professor* temp2 = profDb.searchProfessor(profid); //get new obj, since there is one guaranteed 
        temp2->coursesTaught.push_back(c); // add course 
        c->prof = temp2; // add prof ptr to course
        int index = hash(c->courseNum); // hash, use chaining
        if(!hashTable[index])
        {
            hashTable[index] = c;
        }
        else{
            nums++;
            numc++;
            Course *temp = hashTable[index];
            while(temp->next) // keep searching while we are not at end
            {
                temp = temp->next;
                nums++;
            }
            temp->next = c;
            temp->next->previous = temp;
        }

        counter2++;
    }
    cout << "[CHAINING] Hash table poulated" << endl;
    cout << "---------------------" << endl;
    cout << "Collisions using chaining: " << numc << endl;
    cout << "Search operations using chaining: " << nums << endl;
}

//------------------------------------------------------------------------------
// Search fucntion. Searches hash table and associated linked lists for a course 
// with inputted properties
//
// @param: courseYear, courseNumber, profId
// @return: none
void HashChaining::search(int courseYear, int courseNumber, string profId)
{
    int numsearches = 0;
    int newindex = hash(courseNumber); // get index of bucket
    //numsearches++;
    if(newindex > hashTableSize) // if index gets to big
    {
        cout << "Search operations using chaining: " << numsearches << endl;
        cout << "input too big" << endl;
        displayCourseInfo(NULL);
        return;
    }
    //check if we got it first try
    if(hashTable[newindex]->year == courseYear && hashTable[newindex]->prof->profId == profId && hashTable[newindex]->courseNum == courseNumber)
    {
        cout << "Search operations using chaining: " << numsearches << endl;
        displayCourseInfo(hashTable[newindex]);
        return;
    }
    else 
    {        
        for(int z = 1; z < hashTableSize; z++) // loop through, check if index is too big 
        {
            if(newindex > hashTableSize)
            {
                break;
            }
            Course *temp = hashTable[newindex];
            while(temp->next != NULL) // check each node in linked list for correct 
            {
                temp = temp->next;
                numsearches++;
                if(temp->year == courseYear && temp->prof->profId == profId && temp->courseNum == courseNumber)
                {
                    cout << "Search operations using chaining: " << numsearches << endl;
                    displayCourseInfo(temp);
                    return;
                }
            }
    }
    cout << "Search operations using chaining: " << numsearches << endl;
    displayCourseInfo(NULL);
    return;
}
}

//------------------------------------------------------------------------------
// displays all courses
//
// @param: none
// @return: none 
void HashChaining::displayAllCourses()
{
    cout << "[Chaining] displayAllCourses()" << endl;
    cout << "-------------------" << endl;
    Course *c = new Course;
    for(int i = 0; i < hashTableSize; i++) // loop through everything, print
    {
        c = hashTable[i];
        while(c)
        {
            displayCourseInfo(c);
            //cout << c->year << " " << c->courseName << " " << c->prof->profName << endl;
            c = c->next;
        }
}
}

//------------------------------------------------------------------------------
// displays one course's info
//
// @param: Course pointer
// @return: none
void HashChaining::displayCourseInfo(Course* c)
{
    if(c)
    {
        cout << c->year << " " << c->courseName << " " << c->prof->profName << endl; // print req'd data
    }
    else{
        cout << "course NOT FOUND" << endl;
    }
}