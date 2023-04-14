/*
    library.cpp
    Description: Library search algorithm
    Author: ####
    SIDNumber: M00741238
    Created: 12.04.2021
    Updated: ####
*/

/* TODO:
- Rewrtite user choice loop 
- finish program from main


/* ##########Libraries & Classes & Global variables ########## */
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Book.h"
#include "AVL2.h"

/* ########## Global ########## */

//creating global database tree
AVL *dataTree = new AVL();

/* ########## Functions ########## */

//Adding node to selected tree
void addNode(AVL *currentTree, std::string title, std::string authors, long IBAN, int qty)
{
    std::cout << "Adding new node to the selected AVL tree\n";
    Node *nodeX;
    nodeX = new Node;
    nodeX->nodeBook.setTitle(title);
    nodeX->nodeBook.setAuthors(authors);
    nodeX->nodeBook.settISBN(IBAN);
    nodeX->nodeBook.setQty(qty);
    currentTree->insert(nodeX);
    //testing tree after insertion (printing)
    //currentTree->print(currentTree->root);
}

// deleting node from the tree
void delNode(AVL *currentTree, std::string key)
{   
    Node *nodeX;
    nodeX = currentTree->search(key);
    if (nodeX)
    {
        delete currentTree->remove(nodeX);
        std::cout << "deleting node with provided key\n";
        //testing deletion of node
        /* if (currentTree->root)
            currentTree->print(currentTree->root); */
        std::cout << "\n!!! Book deleted !!!";   
    }
    else
        std::cout << "\nthere is no position of this key\n";
}

// deleting node from the tree
void searchNode(AVL *currentTree, std::string key)
{
    std::cout << "searching database with provided title\n";
    Node *nodeX;
    nodeX = currentTree->search(key);
    if (nodeX)
    {
        std::cout << "\nBook found! \n";
        nodeX->nodeBook.printBook();
    }
    else
        std::cout << "\nthere is no position of this title\n";
}

//function for loading database file to vector
void loadDatabase(std::string database)
{
    std::fstream ioFile;
    std::string line;
    //Open file for creating vector of objects
    ioFile.open(database, std::ios::in | std::ios::out);
    if (ioFile.is_open())
    {
        std::cout << "Opening database...\n";
        //move file stream pointers to the beginning
        ioFile.seekg(0, ioFile.beg);
        //local variables for passing values to object
        std::string title;
        std::string authors;
        long ISBN;
        int qty;
        //loop goin line by line
        while (getline(ioFile, line))
        {
            std::istringstream iss(line);
            std::string substr;
            int column = 0;
            //starting scaning line for data
            while (getline(iss, substr, '\t'))
            {
                column++;
                //changing columns and getting data into variables
                switch (column)
                {
                case 1:
                    title = substr;
                    break;
                case 2:
                    authors = substr;
                    break;
                case 3:
                    ISBN = std::stol(substr);
                    break;
                case 4:
                    qty = std::stoi(substr);
                    // reseting column count
                    column = 0;
                    break;
                default:
                    std::cout << "\nError when reading database, check your file formatting and restart program";
                    exit(0);
                    break;
                }
            }
            //printing and testing scan
            //std::cout << title << " | " << authors << " | " << ISBN << " | " << qty << "\n";

            //adding object into avl as a node
            addNode(dataTree, title, authors, ISBN, qty);
        }
        //Reset fail bits for allowing write
        if (ioFile.fail())
        {
            std::cout << "\nEnd of file reached!\n";
            ioFile.clear();
        }
        ioFile.close();
        std::cout << "\nLoading Done!\n";
    }
    else
    {
        std::cout << "\nError unable to create or open file... please check argument (filename)\n";
        exit(0);
    }
}

//Printing menu
void printMenu()
{
    std::cout << "\n#### Library Search System ####\n";
    std::cout << "----------------------------\n";
    std::cout << "Select an option:\n\n"
              << "    0: Exit"
              << "\n"
              << "    1: Search by title"
              << "\n"
              << "    2: Add book"
              << "\n"
              << "    3: Remove book"
              << "\n";
    std::cout << "----------------------------\n";
}

//processing user input in cli 
//todo: split the loop dont call recursibvly like that
void userChoice()
{
    int choice = 0;
    int qty;
    long ISBN; 
    std::string searchTitle, authors, title;
    //asking user for input
    std::cout << "\nEnter your choice: ";
    std::cin >> choice;
    std::cout << "\nLoading...\n";
    //starting option loop for user input (stops program if user choose to quit)
    while (std::cin.get() == '\n')
    {
        switch (choice)
        {
        case 0:
            std::cout << "Ending program...\n \n";
            delete dataTree;
            exit(0);//
            break;
        case 1:
        // todo: function call for performing action
            std::cout << "\nPlease provide title (case sensitive):";
            getline(std::cin, searchTitle);
            searchNode(dataTree, searchTitle);
            printMenu();
            userChoice();
            break;
        case 2:
            std::cout << "\nPlease provide title (case sensitive):";
            getline(std::cin, title);
            std::cout << "\nPlease provide authors (case sensitive):";
            getline(std::cin, authors);
            std::cout << "\nPlease provide ISBN (long number):";
            std::cin >> ISBN;
            std::cout << "\nPlease provide QTY (numer of copies):";
            std::cin >> qty;
            //adding node to the tree from user input
            addNode(dataTree, title, authors, ISBN, qty);
            std::cout << "\n+++ Book added to database! +++\n\n";
            printMenu();
            userChoice();
            break;
        case 3:
            std::cout << "\nPlease provide title to delete (case sensitive):";
            getline(std::cin, title);
            delNode (dataTree , title);
            printMenu();
            userChoice();
            break;
        default:
            std::cout << "Wrong Selection!"
                      << "\n";
            printMenu();
            userChoice();
            break;
        }
    }
}

/* ########## Main program ########## */
int main(int argc, char *argv[])
{
    // checking for database file
    if (argc == 1)
    {
        //if there is no argument exit program
        std::cout << "\n\nNo Database - Please restart the program and provide "
                  << "filename of the database as argument \n\n";
        return 0;
    }
    else if (argc >= 3)
    {
        std::cout << "\n\nToo many arguments try again\n\n";
        return 0;
    }
    else
    {
        std::cout << "\nLoading Database into memory...\n";
        loadDatabase(argv[1]);
        //printing menu for user
        printMenu();
        userChoice();
    }
    return 0;
}
