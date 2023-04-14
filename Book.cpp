/*
    Book.cpp
    Description: Book class for database
    Author: ######
    SIDNumber: M00741238
    Created: 12.04.2021
    Updated:
*/  

#include "Book.h"

//constructors
Book::Book(){}
Book::~Book(){}
Book::Book(std::string title, std::string authors, long ISBN, int qty){
            this->title = title;
            this->authors = authors;
            this->ISBN = ISBN;
            this->qty = qty;  
        }
//getters
std::string Book::getTitle(){
    return title;
}
std::string Book::getAuthors(){
    return authors;
}
long Book::getISBN(){
    return ISBN;
} 
int Book::getQty(){
    return qty;
}

//setters
void Book::setTitle(std::string newTitle){
    title = newTitle;
}
void Book::setAuthors(std::string newAuthors){
    authors = newAuthors;
}
void Book::settISBN(long newISBN){
    ISBN = newISBN;
} 
void Book::setQty(int newQTY){
    qty = newQTY;
}

// printing book to cli
void Book::printBook () {
    std::cout << "Book details: \n" 
    "Title:   " << getTitle() << " \n" 
    "Authors:   "<< getAuthors() << " \n" 
    "ISBN:   "<< getISBN()  << " \n" 
    "QTY:   "<< getQty() << " \n";
}

//checking if is there any books left
bool Book::checkQty () {
    if ( this->getQty() > 0){
        return true;
    } else {
        return false;
    }
}
