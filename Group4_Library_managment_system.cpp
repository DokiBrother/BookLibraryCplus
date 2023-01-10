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

    void mergeAuthor(queue<Book>& books, int l, int m, int r) {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;
        // Create temporary queues to hold the subarrays
        queue<Book> L, R;
        for (i = 0; i < n1; i++) {
            L.push(books.front());
            books.pop();
        }
        for (j = 0; j < n2; j++) {
            R.push(books.front());
            books.pop();
        }

		// Merge the temp queues back into books[]
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (L.front().author <= R.front().author) {
                books.push(L.front());
                L.pop();
                i++;
            } else {
                books.push(R.front());
                R.pop();
                j++;
            }
            k++;
        }

		// Copy the remaining elements of L[], if there are any
        while (i < n1) {
            books.push(L.front());
            L.pop();
            i++;
            k++;
        }

		// Copy the remaining elements of R[], if there are any
        while (j < n2) {
            books.push(R.front());
            R.pop();
            j++;
            k++;
        }
    }

	// l is for left index and r is right index of the sub-array of books to be sorted
    void mergeSortAuthor(queue<Book>& books, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            // Sort first and second halves
            mergeSortAuthor(books, l, m);
            mergeSortAuthor(books, m + 1, r);

            mergeAuthor(books, l, m, r);
        }
    }

    void sortCheckedOutBooksByAuthor() {
        mergeSortAuthor(checkedOutBooks, 0, checkedOutBooks.size() - 1);
        cout << "\t\tBooks checked out sorted by author." << endl;
    }

    void mergeTitle(queue<Book>& books, int l, int m, int r) {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;
        // Create temporary queues to hold the subarrays
        queue<Book> L, R;
        for (i = 0; i < n1; i++) {
            L.push(books.front());
            books.pop();
        }
        for (j = 0; j < n2; j++) {
            R.push(books.front());
            books.pop();
        }

		// Merge the temp queues back into books[]
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (L.front().title <= R.front().title) {
                books.push(L.front());
                L.pop();
                i++;
            } else {
                books.push(R.front());
                R.pop();
                j++;
            }
            k++;
        }

		// Copy the remaining elements of L[], if there are any
        while (i < n1) {
            books.push(L.front());
            L.pop();
            i++;
            k++;
        }

		// Copy the remaining elements of R[], if there are any
        while (j < n2) {
            books.push(R.front());
            R.pop();
            j++;
            k++;
        }
    }

    void mergeSortTitle(queue<Book>& books, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            // Sort first and second halves
            mergeSortTitle(books, l, m);
            mergeSortTitle(books, m + 1, r);

            mergeTitle(books, l, m, r);
        }
    }

    void sortCheckedOutBooksByTitle() {
        mergeSortTitle(checkedOutBooks, 0, checkedOutBooks.size() - 1);
        cout << "\t\tBooks checked out sorted by Title." << endl;
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
    	cout<<"\t\t";
        cout << right<<setw(48)<<setfill(Aseparator)<<"AVAILABLE BOOKS"
             << right<<setw(36)<<setfill(Aseparator)<<""<< endl;
        cout<<"\t\tThe maximum number of books a library can contain: 1000 books"<<endl;
        cout<<"\t\t";
        cout<<left<<setw(35)<<setfill(Aseparator)<<"Title"
            <<left<<setw(35)<<setfill(Aseparator)<<"Author"
            <<left<<setw(14)<<setfill(Aseparator)<<"ISBN"
            <<endl<<endl;
        for (int i = 0; i < NUM_BOOKS; i++) {
            if (!availableBooks[i].checkedOut) {
				cout<<"\t\t";            	
                cout<<left<<setw(35)<<setfill(separator)<<availableBooks[i].title
                    <<left<<setw(35)<<setfill(separator)<<availableBooks[i].author
                    <<left<<setw(35)<<setfill(separator)<<availableBooks[i].ISBN
                    <<endl;
            }
        }
        
        cout<<endl;
		cout<<"\t\t";
        int size = checkedOutBooks.size();
        if(NUM_BOOKS!=0){
        	cout<<"\n\t\t";
            cout <<right<<setw(52)<<setfill(Aseparator)<<"CHECKED OUT BOOKS"
                 << right<<setw(32)<<setfill(Aseparator)<<""<< endl;
            cout<<"\t\t";
            cout<<"Total book of library: "<<size<<endl;
            cout<<"\t\t";
            cout<<left<<setw(35)<<setfill(Aseparator)<<"Title"
                <<left<<setw(35)<<setfill(Aseparator)<<"Author"
                <<left<<setw(14)<<setfill(Aseparator)<<"ISBN"
                <<endl<<endl;
        }
		
        for (int i = 0; i < size; i++) {
            Book book = checkedOutBooks.front();
            cout<<"\t\t";
            cout<<left<<setw(35)<<setfill(separator)<<book.title
                <<left<<setw(35)<<setfill(separator)<<book.author
                <<left<<setw(35)<<setfill(separator)<<book.ISBN
                <<endl;
            checkedOutBooks.pop();
            checkedOutBooks.push(book);
        }
    }

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

//    void writeToFile(string fileName) {
//        ofstream outFile;
//        outFile.open(fileName);
//
//        queue<Book> temp;
//        while (!checkedOutBooks.empty()) {
//            Book b = checkedOutBooks.front();
//            outFile << b.title << "," << b.author << "," << b.ISBN << endl;
//            temp.push(b);
//            checkedOutBooks.pop();
//        }
//        while (!temp.empty()) {
//            checkedOutBooks.push(temp.front());
//            temp.pop();
//        }
//        outFile.close();
//        cout << "Checked out books written to file." << endl;
//    }

    void writeToFile(const string &fileName) {
        ofstream outFile;
        outFile.open(fileName);
        if (outFile.is_open()) {
            outFile<<left<<setw(35)<<setfill(separator)<<""
                   <<left<<setw(35)<<setfill(separator)<<"LIBRARY MANAGEMENT SYSTEM"
                   <<endl<<endl;
            outFile<<"\t\tData about existing books and returned books go to"<<endl;
            outFile<<left<<setw(35)<<setfill(Aseparator)<<"Title"
                   <<left<<setw(35)<<setfill(Aseparator)<<"Author"
                   <<left<<setw(35)<<setfill(Aseparator)<<"ISBN"
                   <<endl;
            // Write the records of the available books to the file
            for (int i = 0; i < NUM_BOOKS; i++) {
                outFile<<left<<setw(35)<<setfill(separator)<<availableBooks[i].title
                       <<left<<setw(35)<<setfill(separator)<<availableBooks[i].author
                       <<left<<setw(35)<<setfill(separator)<<availableBooks[i].ISBN
                       <<endl;
                //outFile << availableBooks[i].title << "," << availableBooks[i].author << "," << availableBooks[i].ISBN << endl;
            }
            outFile<<endl<<endl;
            // Write the records of the checked out books to the file
            outFile<<"\t\tBook data is still being borrowed"<<endl;
            int size = checkedOutBooks.size();
            outFile<<"\t\tThe total number of books borrowed is:"<<" "<<size<<endl;
            outFile<<left<<setw(35)<<setfill(Aseparator)<<"Title"
                   <<left<<setw(35)<<setfill(Aseparator)<<"Author"
                   <<left<<setw(35)<<setfill(Aseparator)<<"ISBN"
                   <<endl;
            for (int i = 0; i < size; i++) {
                Book book = checkedOutBooks.front();
                outFile<<left<<setw(35)<<setfill(separator)<<book.title
                       <<left<<setw(35)<<setfill(separator)<<book.author
                       <<left<<setw(35)<<setfill(separator)<<book.ISBN
                       <<endl;
                //outFile << book.title << "," << book.author << "," << book.ISBN << endl;
                checkedOutBooks.pop();
                checkedOutBooks.push(book);
            }
            outFile.close();
            cout << "\t\tRecords written to file..." << endl;
        } else {
            cout << "\t\tError: Unable to open file." << endl;
        }
    }

    void writeToFile_Re_usable(const string &fileName) {
        ofstream outFile;
        outFile.open(fileName);
        if (outFile.is_open()) {
            // Write the records of the available books to the file
            for (int i = 0; i < NUM_BOOKS; i++) {
                outFile << availableBooks[i].title << "," << availableBooks[i].author << "," << availableBooks[i].ISBN << endl;
            }
            // Write the records of the checked out books to the file
            int size = checkedOutBooks.size();
            for (int i = 0; i < size; i++) {
                Book book = checkedOutBooks.front();
                outFile << book.title << "," << book.author << "," << book.ISBN << endl;
                checkedOutBooks.pop();
                checkedOutBooks.push(book);
            }
            outFile.close();
            cout << "\t\tRecords written to file." << endl;
        } else {
            cout << "\t\tError: Unable to open file." << endl;
        }
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
        cout<<endl;

        switch(choice) {
            case 1: {
                string title, author, ISBN;
                cout << "\t\tEnter the title of the book: ";
                cin.ignore();
                getline(cin, title);
                cout << "\t\tEnter the author of the book: ";
                getline(cin, author);
                cout << "\t\tEnter the ISBN of the book: ";
                getline(cin, ISBN);
                library.addBook(Book(title, author, ISBN));
                library.clear();
                break;
            }
            case 2: {
                string ISBN;
                cout << "\t\tEnter the ISBN of the book you want to check out: ";
                cin.ignore();
                getline(cin, ISBN);
                library.checkOutBook(ISBN);
                library.clear();
                break;
            }
            case 3: {
                string ISBN;
                cout << "\t\tEnter the ISBN of the book you want to return: ";
                cin.ignore();
                getline(cin, ISBN);
                library.returnBook(ISBN);
                library.clear();
                break;
            }
            case 4: {
                library.sortByTitle();
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 5: {
                library.sortByAuthor();
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 6:{
                library.sortCheckedOutBooksByTitle();
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 7:{
                library.sortCheckedOutBooksByAuthor();
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 8:{
                string title, author, ISBN;
                cout << "\t\tEnter the ISBN of the book you want to update: ";
                cin.ignore();
                getline(cin, ISBN);
                cout << "\t\tEnter the new title of the book: ";
                getline(cin, title);
                cout << "\t\tEnter the new author of the book: ";
                getline(cin, author);
                library.updateBook(ISBN, title, author);
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 9: {
                string ISBN;
                cout << "\t\tEnter the ISBN of the book you want to delete: ";
                cin.ignore();
                getline(cin, ISBN);
                library.deleteBook(ISBN);
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 10:{
                string title;
                cout << "\t\tEnter the title of the book you want to search for: ";
                cin.ignore();
                getline(cin, title);
                library.searchByTitle(title);
                library.clear();
                break;
            }
            case 11:{
                string author;
                cout << "\t\tEnter the author of the book you want to search for: ";
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
                cout << "\t\tEnter the name of the file you want to read from: ";
                cin.ignore();
                getline(cin, fileName);
                library.readFromFile(fileName);
                library.clear();
                break;
            }
            case 14: {
                string fileName;
                cout << "\t\tEnter the name of the file you want to write to: ";
                cin.ignore();
                getline(cin, fileName);
                library.writeToFile(fileName);
                library.clear();
                break;
            }
            case 15: {
                cout << "\t\tThank you for using the library. Goodbye!" << endl;
                library.writeToFile("BookInLibrary.txt");
                library.writeToFile_Re_usable("file_Re_Usable.txt");
                library.clear();
                break;
            }
            default: {
                cout << "\t\tInvalid choice. Please try again." << endl;
                library.writeToFile("BookInLibrary.txt");
                library.writeToFile_Re_usable("file_Re_Usable.txt");
                system("\t\tPAUSE");
                break;
            }
        }
    }

    return 0;
}
