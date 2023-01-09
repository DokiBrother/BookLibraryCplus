#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>

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
    static const int MAX_BOOKS = 1000;
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
            cout << "\t\tBook added to the library." << endl;
        } else {
            cout << "\t\tError: The library is full. Cannot add more books." << endl;
        }
    }

    // Function to check out a book
    void checkOutBook(string ISBN) {
        bool found = false;
        for (int i = 0; i <= NUM_BOOKS; i++) {
            if (availableBooks[i].ISBN == ISBN && !availableBooks[i].checkedOut) {
                availableBooks[i].checkedOut = true;
                checkedOutBooks.push(availableBooks[i]);
                cout << "\t\tBook checked out." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "\t\tBook not found or already checked out." << endl;
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
        }
        if (!found) {
            cout << "\t\tSorry, that book is not checked out." << endl;
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
        cout << "\t\tBooks sorted by title." << endl;
    }

    void sortCheckedOutBooksByTitle() {
        // Use a bubble sort algorithm to sort the books
        bool sorted = false;
        while (!sorted) {
            sorted = true;
            int numBooks = checkedOutBooks.size();
            for (int i = 0; i < numBooks - 1; i++) {
                Book book1 = checkedOutBooks.front();
                checkedOutBooks.pop();
                Book book2 = checkedOutBooks.front();
                checkedOutBooks.pop();
                // If book1 comes after book2 alphabetically, swap their order in the queue
                if (book1.title > book2.title) {
                    checkedOutBooks.push(book1);
                    checkedOutBooks.push(book2);
                    sorted = false;
                } else {
                    checkedOutBooks.push(book2);
                    checkedOutBooks.push(book1);
                }
            }
        }
        cout << "\t\tBooks checked out sorted by title." << endl;
    }

    void sortCheckedOutBooksByAuthor() {
        // Use a bubble sort algorithm to sort the books
        bool sorted = false;
        while (!sorted) {
            sorted = true;
            int numBooks = checkedOutBooks.size();
            for (int i = 0; i < numBooks - 1; i++) {
                Book book1 = checkedOutBooks.front();
                checkedOutBooks.pop();
                Book book2 = checkedOutBooks.front();
                checkedOutBooks.pop();
                // If book1 comes after book2 alphabetically, swap their order in the queue
                if (book1.author > book2.author) {
                    checkedOutBooks.push(book1);
                    checkedOutBooks.push(book2);
                    sorted = false;
                } else {
                    checkedOutBooks.push(book2);
                    checkedOutBooks.push(book1);
                }
            }
        }
        cout << "\t\tBooks checked out sorted by author." << endl;
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
        cout << "\t\tBooks sorted by author." << endl;
    }

//  Function to update a book's information
    void updateBook(string ISBN, string newTitle, string newAuthor) {
        bool found = false;
        for (int i = 0; i < NUM_BOOKS; i++) {
            if (availableBooks[i].ISBN == ISBN) {
                found = true;
                availableBooks[i].title = newTitle;
                availableBooks[i].author = newAuthor;
                cout << "\t\tBook information updated." << endl;
                break;
            }
        }
        if (!found) {
            cout << "\t\tSorry, that book was not found." << endl;
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
                cout << "\t\tBook deleted." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "\t\tBook not found." << endl;
        }
    }

    const char Aseparator='=';
    const char separator=' ';
    void displayAllBooks() {
        cout << right<<setw(43)<<setfill(Aseparator)<<"AVAILABLE BOOKS"
             << right<<setw(31)<<setfill(Aseparator)<<""<< endl;
        cout<<"The maximum number of books a library can contain: 1000 books"<<endl;
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
//    void readFromFile(string fileName) {
//        ifstream inFile;
//        inFile.open(fileName);
//        if (!inFile) {
//            cout << "Error opening file." << endl;
//            return;
//        }
//
//        queue<Book> tempBooks;
//        string title, author, ISBN;
//        while (inFile >> title >> author >> ISBN) {
//            Book b(title, author, ISBN);
//            tempBooks.push(b);
//        }
//        inFile.close();
//
//        while (!tempBooks.empty()) {
//            addBook(tempBooks.front());
//            tempBooks.pop();
//        }
//    }
    void readFromFile(string fileName) {
        ifstream inFile;
        inFile.open(fileName);
        if (!inFile) {
            cout << "\t\tError opening file." << endl;
            return;
        }

        queue<Book> tempBooks;
        string line, title, author, ISBN;
        while (getline(inFile, line)) {
            // Use a stringstream to split the line into individual values
            stringstream ss(line);
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, ISBN);
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
            outFile << b.title << "," << b.author << "," << b.ISBN << endl;
            temp.push(b);
            checkedOutBooks.pop();
        }
        while (!temp.empty()) {
            checkedOutBooks.push(temp.front());
            temp.pop();
        }
        outFile.close();
        cout << "\t\tChecked out books written to file." << endl;
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
            cout << "\t\tSorry, no books with that title are checked out." << endl;
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
            cout << "\t\tSorry, no books by that author are available or checked out." << endl;
        }
    }
    void intro()
    {
        cout<<"\t\t   created by "<<endl;
        cout<<"\tTRAN VAN DUAT           19071591"<<endl;
        cout<<"\tNGUYEN THI NGOC GIAO    20070704"<<endl;
        cout<<"\tPHAM TIEN PHU           19071623"<<endl;
        cout<<"\tDO CONG TUAN            19071639"<<endl;
    }
    void clear()
    {
    	cout<<"\n";
        cout<<"\t\t";
        system("PAUSE");
	}
};

int main() {
    Library library;
    queue<Book> checkedOutBooks;

    int choice = 0;
    while (choice != 15) {
    	system("cls");
    	library.intro();
        cout<<"\n\t\t***********---------- LIBRARY MANAGEMENT SYSTEM --------*********"<<endl;
    	cout<<"\t\t**********---------------------------------------------**********\n\n";
		cout<<"\t\t-----------------------------WELCOME-----------------------------\n\n";
        cout << "\t\tPress 1.  Add a book to the library" << endl;
        cout << "\t\tPress 2.  Check out a book" << endl;
        cout << "\t\tPress 3.  Return a book" << endl;
        cout << "\t\tPress 4.  Sort books by title" << endl;
        cout << "\t\tPress 5.  Sort books by author" << endl;
        cout << "\t\tPress 6. Sort Checked Out Books By Title" << endl;
        cout << "\t\tPress 7. Sort Checked Out Books By Author" << endl;
        cout << "\t\tPress 8.  Update a book" << endl;
        cout << "\t\tPress 9.  Delete a book" << endl;
        cout << "\t\tPress 10. Search for a book by title" << endl;
        cout << "\t\tPress 11. Search for a book by author" << endl;
        cout << "\t\tPress 12. Display all books" << endl;
        cout << "\t\tPress 13. Read books from a file" << endl;
        cout << "\t\tPress 14. Write books to a file" << endl;
        cout << "\t\tPress 15. Quit" << endl;
        cout<<"\n\t\tEnter your choice: ";
        cin >> choice;

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
                library.clear();
                break;
            }
            case 2: {
                string ISBN;
                cout << "Enter the ISBN of the book you want to check out: ";
                cin.ignore();
                getline(cin, ISBN);
                library.checkOutBook(ISBN);
                library.clear();
                break;
            }
            case 3: {
                string ISBN;
                cout << "Enter the ISBN of the book you want to return: ";
                cin.ignore();
                getline(cin, ISBN);
                library.returnBook(ISBN);
                library.writeToFile(""); // Write the updated list of available books to the file
                library.clear();
                break;
            }
            case 4: {
                library.sortByTitle();
                library.clear();
                break;
            }
            case 5: {
                library.sortByAuthor();
                library.clear();
                break;
            }
            case 6:{
                library.sortCheckedOutBooksByTitle();
                library.clear();
                break;
            }
            case 7:{
                library.sortCheckedOutBooksByAuthor();
                library.clear();
                break;
            }
            case 8:{
                string title, author, ISBN;
                cout << "Enter the ISBN of the book you want to update: ";
                cin.ignore();
                getline(cin, ISBN);
                cout << "Enter the new title of the book: ";
                getline(cin, title);
                cout << "Enter the new author of the book: ";
                getline(cin, author);
                library.updateBook(ISBN, title, author);
                library.clear();
                break;
            }
            case 9: {
                string ISBN;
                cout << "Enter the ISBN of the book you want to delete: ";
                cin.ignore();
                getline(cin, ISBN);
                library.deleteBook(ISBN);
                library.clear();
                break;
            }
            case 10:{
                string title;
                cout << "Enter the title of the book you want to search for: ";
                cin.ignore();
                getline(cin, title);
                library.searchByTitle(title);
                library.clear();
                break;
            }
            case 11:{
                string author;
                cout << "Enter the author of the book you want to search for: ";
                cin.ignore();
                getline(cin, author);
                library.searchByAuthor(author);
                library.clear();
                break;
            }
            case 12: {
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 13: {
                string fileName;
                cout << "Enter the name of the file you want to read from: ";
                cin.ignore();
                getline(cin, fileName);
                library.readFromFile(fileName);
                library.clear();
                break;
            }
            case 14: {
                string fileName;
                cout << "Enter the name of the file you want to write to: ";
                cin.ignore();
                getline(cin, fileName);
                library.writeToFile(fileName);
                library.clear();
                break;
            }
            case 15: {
                cout << "Thank you for using the library. Goodbye!" << endl;
                library.clear();
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                system("PAUSE");
                break;
            }
        }
    }

    return 0;
}
