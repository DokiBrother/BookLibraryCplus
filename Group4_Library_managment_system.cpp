//
// Created by duatt on 1/1/2023.
//
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Book class to store book data
class Book {
public:
    string title;
    string author;
    string ISBN;
    bool checkedOut;

    // Constructor
    Book(string t, string a, string i) {
        title = t;
        author = a;
        ISBN = i;
        checkedOut = false;
    }

    // Default constructor
    Book() {
        title = "";
        author = "";
        ISBN = "";
        checkedOut = false;
    }


    // Set and get functions
    void setTitle(string t) {
        title = t;
    }
    string getTitle() {
        return title;
    }
    void setAuthor(string a) {
        author = a;
    }
    string getAuthor() {
        return author;
    }
    void setISBN(string i) {
        ISBN = i;
    }
    string getISBN() {
        return ISBN;
    }
};

class Library {
private:
    static const int MAX_BOOKS = 100;
    Book availableBooks[MAX_BOOKS];
    int NUM_BOOKS = 0;
    queue<Book> checkedOutBooks;

public:
    // Default constructor
    Library() {
        NUM_BOOKS = 0;
        while(!checkedOutBooks.empty()) {
            checkedOutBooks.pop();
        }
        for (int i = 0; i < MAX_BOOKS; i++) {
            availableBooks[i] = Book();
        }
    }

    // Add a book to the library
    void addBook(const Book &book) {
        if (NUM_BOOKS < MAX_BOOKS) {
            availableBooks[NUM_BOOKS] = book;
            NUM_BOOKS++;
            cout << "Book added to the library." << endl;
        } else {
            cout << "Error: The library is full. Cannot add more books." << endl;
        }
    }

    // Function to check out a book
    void checkOutBook(string ISBN) {
        bool found = false;
        for (int i = 0; i < NUM_BOOKS; i++) {
            if (availableBooks[i].ISBN == ISBN && !availableBooks[i].checkedOut) {
                availableBooks[i].checkedOut = true;
                checkedOutBooks.push(availableBooks[i]);
                cout << "Book checked out." << endl;
                found = true;
                NUM_BOOKS--;
                break;
            }
        }
        if (!found) {
            cout << "Book not found or already checked out." << endl;
        }
    }

    // Function to return a book
    void returnBook(string ISBN) {
        queue<Book> temp;
        bool found = false;
        while (!checkedOutBooks.empty()) {
            if (checkedOutBooks.front().ISBN == ISBN) {
                found = true;
                checkedOutBooks.front().checkedOut = false;
                // Add the returned book back to the available books list
                availableBooks[NUM_BOOKS] = checkedOutBooks.front();
                NUM_BOOKS++;
                checkedOutBooks.pop();
                break;
            }
            temp.push(checkedOutBooks.front());
            checkedOutBooks.pop();
        }
        while (!temp.empty()) {
            checkedOutBooks.push(temp.front());
            temp.pop();
            NUM_BOOKS++;
        }
        if (!found) {
            cout << "Sorry, that book is not checked out." << endl;
        }
    }

    // Function to sort books by title
    void sortByTitle() {
        bool sorted = false;
        while (!sorted) {
            sorted = true;
            for (int i = 0; i < NUM_BOOKS - 1; i++) {
                if (availableBooks[i].title > availableBooks[i + 1].title) {
                    swap(availableBooks[i], availableBooks[i + 1]);
                    sorted = false;
                }
            }
        }
        cout << "Books sorted by title." << endl;
    }

// Function to sort books by author
    void sortByAuthor() {
        for (int i = 0; i < NUM_BOOKS; i++) {
            for (int j = i + 1; j < NUM_BOOKS; j++) {
                if (availableBooks[i].author > availableBooks[j].author) {
                    Book temp = availableBooks[i];
                    availableBooks[i] = availableBooks[j];
                    availableBooks[j] = temp;
                }
            }
        }
        cout << "Books sorted by author." << endl;
    }

//  Function to update a book's information
    void updateBook(string ISBN, string newTitle, string newAuthor) {
        bool found = false;
        for (int i = 0; i < NUM_BOOKS; i++) {
            if (availableBooks[i].ISBN == ISBN) {
                found = true;
                availableBooks[i].title = newTitle;
                availableBooks[i].author = newAuthor;
                cout << "Book information updated." << endl;
                break;
            }
        }
        if (!found) {
            cout << "Sorry, that book was not found." << endl;
        }
    }

// Function to delete a book
    void deleteBook(string ISBN) {
        bool found = false;
        for (int i = 0; i < NUM_BOOKS; i++) {
            if (availableBooks[i].ISBN == ISBN) {
                // Shift all books after the one to be deleted to the left
                for (int j = i; j < NUM_BOOKS - 1; j++) {
                    availableBooks[j] = availableBooks[j + 1];
                }
                NUM_BOOKS--;
                cout << "Book deleted." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found." << endl;
        }
    }

    const char Aseparator='=';
    const char separator=' ';
    void displayAllBooks() {
        if(NUM_BOOKS!=0){
            cout << right<<setw(43)<<setfill(Aseparator)<<"AVAILABLE BOOKS"
                 << right<<setw(31)<<setfill(Aseparator)<<""<< endl;
            cout<<"Total book of library: "<<NUM_BOOKS<<endl;
            cout<<left<<setw(25)<<setfill(Aseparator)<<"Title"
                <<left<<setw(25)<<setfill(Aseparator)<<"Author"
                <<left<<setw(25)<<setfill(Aseparator)<<"ISBN"
                <<endl;
            for (int i = 0; i < NUM_BOOKS; i++) {
	            if (!availableBooks[i].checkedOut) {
	                cout<<left<<setw(25)<<setfill(separator)<<availableBooks[i].title
	                    <<left<<setw(25)<<setfill(separator)<<availableBooks[i].author
	                    <<left<<setw(25)<<setfill(separator)<<availableBooks[i].ISBN
	                    <<endl;
	            }
	        }
        }
        int size = checkedOutBooks.size();
        if(NUM_BOOKS!=0){
            cout << endl<<right<<setw(47)<<setfill(Aseparator)<<"CHECKED OUT BOOKS"
                 << right<<setw(27)<<setfill(Aseparator)<<""<< endl;
            cout<<"Total book of library: "<<size<<endl;
            cout<<left<<setw(25)<<setfill(Aseparator)<<"Title"
                <<left<<setw(25)<<setfill(Aseparator)<<"Author"
                <<left<<setw(25)<<setfill(Aseparator)<<"ISBN"
                <<endl;
        }

        for (int i = 0; i < size; i++) {
            Book book = checkedOutBooks.front();
            cout<<left<<setw(25)<<setfill(separator)<<book.title
                <<left<<setw(25)<<setfill(separator)<<book.author
                <<left<<setw(25)<<setfill(separator)<<book.ISBN
                <<endl;
            checkedOutBooks.pop();
            checkedOutBooks.push(book);
        }
    }

// Function to read data from a file and populate the library
    void readFromFile(string fileName) {
        ifstream inFile;
        inFile.open(fileName);
        if (!inFile) {
            cout << "Error opening file." << endl;
            return;
        }

        queue<Book> tempBooks;
        string title, author, ISBN;
        while (inFile >> title >> author >> ISBN) {
            Book b(title, author, ISBN);
            tempBooks.push(b);
        }
        inFile.close();

        while (!tempBooks.empty()) {
            addBook(tempBooks.front());
            tempBooks.pop();
        }
    }

    void writeToFile(string fileName) {
        ofstream outFile;
        outFile.open(fileName);

        queue<Book> temp;
        while (!checkedOutBooks.empty()) {
            Book b = checkedOutBooks.front();
            outFile << b.title << " " << b.author << " " << b.ISBN << endl;
            temp.push(b);
            checkedOutBooks.pop();
        }
        while (!temp.empty()) {
            checkedOutBooks.push(temp.front());
            temp.pop();
        }
        outFile.close();
        cout << "Checked out books written to file." << endl;
    }

    void searchByTitle(string title) {
        bool found = false;
        queue<Book> temp;
        while (!checkedOutBooks.empty()) {
            if (checkedOutBooks.front().title == title) {
                cout << "Title   : " << checkedOutBooks.front().title << endl;
                cout << "Author  : " << checkedOutBooks.front().author << endl;
                cout << "ISBN    : " << checkedOutBooks.front().ISBN << endl;
                found = true;
                break;
            }
            temp.push(checkedOutBooks.front());
            checkedOutBooks.pop();
        }
        while (!temp.empty()) {
            checkedOutBooks.push(temp.front());
            temp.pop();
        }
        // Search through available books
        for (int i = 0; i < NUM_BOOKS; i++) {
            if (availableBooks[i].title == title && !availableBooks[i].checkedOut) {
                cout << "Title   : " << availableBooks[i].title << endl;
                cout << "Author  : " << availableBooks[i].author << endl;
                cout << "ISBN    : " << availableBooks[i].ISBN << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Sorry, no books with that title are checked out." << endl;
        }
    }


    // Function to search for a book by author
    void searchByAuthor(string author) {
        bool found = false;
        // Search through available books
        for (int i = 0; i < NUM_BOOKS; i++) {
            if (availableBooks[i].author == author && !availableBooks[i].checkedOut) {
                cout << "Title   : " << availableBooks[i].title << endl;
                cout << "Author  : " << availableBooks[i].author << endl;
                cout << "ISBN    : " << availableBooks[i].ISBN << endl;
                found = true;
            }
        }
        // Search through checked out books
        queue<Book> temp;
        while (!checkedOutBooks.empty()) {
            if (checkedOutBooks.front().author == author) {
                cout << "Title   : " << checkedOutBooks.front().title << endl;
                cout << "Author  : " << checkedOutBooks.front().author << endl;
                cout << "ISBN    : " << checkedOutBooks.front().ISBN << endl;
                found = true;
            }
            temp.push(checkedOutBooks.front());
            checkedOutBooks.pop();
        }
        // Re-add books to checkedOutBooks queue
        while (!temp.empty()) {
            checkedOutBooks.push(temp.front());
            temp.pop();
        }
        if (!found) {
            cout << "Sorry, no books by that author are available or checked out." << endl;
        }
    }
    void intro()
    {
        cout<<"   LIBRARY MANAGEMENT SYSTEM "<<endl;
        cout<<"Group Members:           "<<endl;
        cout<<"NGUYEN THI NGOC GIAO    20070704"<<endl;
        cout<<"TRAN VAN DUAT           19071591"<<endl;
        cout<<"PHAM TIEN PHU           19071623"<<endl;
        cout<<"DO CONG TUAN            19071639"<<endl;
    }
};

int main() {
    Library library;
    queue<Book> checkedOutBooks;
    cout << endl << endl;

    int choice = 0;
    while (choice != 13) {
    	system("cls");
    	library.intro();
        cout << "\nWelcome to the library. What would you like to do?" << endl;
        cout << "Press 1.  Add a book to the library" << endl;
        cout << "Press 2.  Check out a book" << endl;
        cout << "Press 3.  Return a book" << endl;
        cout << "Press 4.  Sort books by title" << endl;
        cout << "Press 5.  Sort books by author" << endl;
        cout << "Press 6.  Update a book" << endl;
        cout << "Press 7.  Delete a book" << endl;
        cout << "Press 8.  Search for a book by title" << endl;
        cout << "Press 9.  Search for a book by author" << endl;
        cout << "Press 10. Display all books" << endl;
        cout << "Press 11. Read books from a file" << endl;
        cout << "Press 12. Write books to a file" << endl;
        cout << "Press 13. Quit" << endl;
        cout<<"\nEnter your choice: ";
        cin >> choice;
        cout<<"\n";
        switch(choice) {
            case 1: {
                string title, author, ISBN;
                cout << "Enter the title of the book: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter the author of the book: ";
                getline(cin, author);
                cout << "Enter the ISBN of the book: ";
                getline(cin, ISBN);
                library.addBook(Book(title, author, ISBN));
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 2: {
                string ISBN;
                cout << "Enter the ISBN of the book you want to check out: ";
                cin.ignore();
                getline(cin, ISBN);
                library.checkOutBook(ISBN);
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 3: {
                string ISBN;
                cout << "Enter the ISBN of the book you want to return: ";
                cin.ignore();
                getline(cin, ISBN);
                library.returnBook(ISBN);
                library.writeToFile("books.txt"); // Write the updated list of available books to the file
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 4: {
                library.sortByTitle();
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 5: {
                library.sortByAuthor();
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 6:{
                string title, author, ISBN;
                cout << "Enter the ISBN of the book you want to update: ";
                cin.ignore();
                getline(cin, ISBN);
                cout << "Enter the new title of the book: ";
                getline(cin, title);
                cout << "Enter the new author of the book: ";
                getline(cin, author);
                library.updateBook(ISBN, title, author);
                cout << "\n" << endl;
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 7: {
                string ISBN;
                cout << "Enter the ISBN of the book you want to delete: ";
                cin.ignore();
                getline(cin, ISBN);
                library.deleteBook(ISBN);
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 8:{
                string title;
                cout << "Enter the title of the book you want to search for: ";
                cin.ignore();
                getline(cin, title);
                library.searchByTitle(title);
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 9:{
                string author;
                cout << "Enter the author of the book you want to search for: ";
                cin.ignore();
                getline(cin, author);
                library.searchByAuthor(author);
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 10: {
                library.displayAllBooks();
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 11: {
                string fileName;
                cout << "Enter the name of the file you want to read from: ";
                cin.ignore();
                getline(cin, fileName);
                library.readFromFile(fileName);
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 12: {
                string fileName;
                cout << "Enter the name of the file you want to write to: ";
                cin.ignore();
                getline(cin, fileName);
                library.writeToFile(fileName);
                cout<<"\n";
                system("PAUSE");
                break;
            }
            case 13: {
                cout << "Thank you for using the library. Goodbye!" << endl;
                cout<<"\n";
                system("PAUSE");
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                cout<<"\n";
                system("PAUSE");
                break;
            }
        }
    }

    return 0;
}
