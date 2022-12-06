//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------
// Default constructor. Sets root to NULL
//
// @param: none
// @retrun: none
ProfBST::ProfBST()
{
    root = NULL; // set root equal to NULL
}

//-----------------------------------------------------------------------------
// Helper function to detroy professor catalog
//
// @param: pointer to professor object
// @retrun: none
void destroyCatalog(Professor *current)
{
    if(current) // loop thorugh each node, delete
    {
    destroyCatalog(current->right);
    destroyCatalog(current->left);
    delete current;
    current = NULL;
    }
}

//-----------------------------------------------------------------------------
// Default destructor. Destorys tree, frees memory
//
// @param: none
// @retrun: none
ProfBST::~ProfBST()
{
    destroyCatalog(root); // call helper

}

//-----------------------------------------------------------------------------
// Creates instance of professor object
//
// @param: professor id, professor name
// @retrun: pointer ot professor object
Professor* createprof(string profId, string profName)
{
    Professor *prof = new Professor(profId, profName); // fills in attributes of prof obj
    prof->profId = profId;
    prof->profName = profName;
    prof->right = NULL;
    prof->left = NULL;
    return prof;
}


//-----------------------------------------------------------------------------
// helper function to add professor into the correct spot in BST
//
// @param: Professor pointer, professor id, professor name
// @retrun: professor pointer
Professor* addprofhelper(Professor* current, string profId, string profName)
{
    //cout << "addhelper run" << endl;
    if(current == NULL) // make new prof if one doesn't exist
    {
        return createprof(profId, profName);
    }
    else if(current->profId > profId) // insert into correct spot
    {
        current->left = addprofhelper(current->left, profId, profName);
    }
    else if(current->profId < profId)
    {
        current->right = addprofhelper(current->right, profId, profName);
    }
    return current;
}

//-----------------------------------------------------------------------------
// adds professor to tree. Calls helper function to do so
//
// @param: professor id, professor name
// @retrun: none
void ProfBST::addProfessor(string profId, string profName)
{
    root = addprofhelper(root, profId, profName); // call helper
    return;
}

//-----------------------------------------------------------------------------
// helper fucntion for search, searches BST for professor
//
// @param: professor pointer, professor id
// @retrun: none
Professor* search(Professor* current, string profId)
{
    // inorder traversal to find matching prof
    if(current == NULL)
    {
        return NULL;
    }

    if (current->profId == profId)
    {
        return current;
    }
    if(current->profId > profId)
    {
        return search(current->left, profId);
    }
    return search(current->right, profId);
}

//-----------------------------------------------------------------------------
// fucntion to search BST for professor, calls helper fucntion
//
// @param: professor id
// @retrun: professor pointer
Professor* ProfBST::searchProfessor(string profId)
{
    Professor* temp = search(root, profId); // returns professor pointer
    if(temp)
    {
        return temp;
    }
    //cout << "Not found" << endl;
    return NULL;
    
}


//-----------------------------------------------------------------------------
// public search professor function. Searches for professor in BST, calls helper
// function
//
// @param: professor id
// @retrun: none
void ProfBST::publicSearchProfessor(string profId)
{
    // call display info of searched course
    displayProfessorInfo(searchProfessor(profId));
    return;
}

//-----------------------------------------------------------------------------
// Displays professors info
//
// @param: professor object pointer
// @retrun: none
void ProfBST::displayProfessorInfo(Professor* p)
{
    // display req'd info
    Course *c;
    if(p)
    {
        cout << "Name: " << p->profName << endl;
        for (int i=0; i < p->coursesTaught.size();i++)
        {
            c = p->coursesTaught[i];
            cout << "- " << c->courseNum << ": " << c->courseName << ", " << c->year << endl;
        }
    }
}
