/*
    Book.cpp
    Description: Book class for database
    Author: ######
    SIDNumber: M00741238
    Created: 12.04.2021
    Updated:
*/  

#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
    //overloading operators for comparing book (by title)
    friend bool operator == (Book& nodeBook1,  Book& nodeBook2)
    {
        return nodeBook1.title == nodeBook2.title;
    }
    friend bool operator < (Book& nodeBook1,  Book& nodeBook2)
    {
        return nodeBook1.title < nodeBook2.title;
    }

    private:
        std::string title;
        std::string authors;
        long ISBN;
        int qty;
    public:
        Book();
        ~Book();
        Book(std::string title, std::string authors, long ISBN, int qty);
        std::string getTitle();
        std::string getAuthors();
        long getISBN();
        int getQty();
        void setTitle(std::string newTitle);    
        void setAuthors(std::string newAuthors);
        void settISBN(long newISBN);
        void setQty(int newQTY);
        void printBook();
        bool checkQty();
};

#endif
