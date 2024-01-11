#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <ctime> 

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

class StudentInfo {
    public:
    string studentID;
    string studentName;
    string ISBN;
    string borrowDate;

    StudentInfo(string id, string name, string borrow, string bDate) {
        studentID = id;
        studentName = name;
        ISBN = borrow;
        borrowDate = bDate;
    }

    StudentInfo() {
        studentID = "";
        studentName = "";
        ISBN = "";
        borrowDate = "";
    }

    void setStudentID(string id) {
        studentID = id;
    }
    string getStudentID() {
        return studentID;
    }
    void setStudentName(string name) {
        studentName = name;
    }
    string getStudentName() {
        return studentName;
    }
    void setStudentBorrow(string borrow) {
        ISBN = borrow;
    }
    string getStudentBorrow() {
        return ISBN;
    }
    void setBorrowDate(string bDate) {
        borrowDate = bDate;
    }
    string getBorrowDate() {
        return borrowDate;
    }
};

class Library {
private:
    static const int MAX_BOOKS = 1000;
    static const int MAX_STUDENTS = 1000;
    Book availableBooks[MAX_BOOKS];
    StudentInfo studentBorrow[MAX_STUDENTS];
    int NUM_BOOKS = 0;
    int NUM_STUDENTS = 0;
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
    
    void addBook(const Book &book) {
        if (NUM_BOOKS < MAX_BOOKS) {
            availableBooks[NUM_BOOKS] = book;
            NUM_BOOKS++;
            cout << "\t\tBook added to the library." << endl;
        } else {
            cout << "\t\tError: The library is full. Cannot add this book." << endl;
        }
    }

    void addStudent(const StudentInfo &student) {
        if (NUM_STUDENTS < MAX_STUDENTS) {
            studentBorrow[NUM_STUDENTS] = student;
            NUM_STUDENTS++;
        }
    }

    void avoidDuplicatedBook(string title, string author, string ISBN) {
        queue<Book> temp;
        bool foundAvail = false;
        bool foundChecked = false;
        bool added = false;
        string isOverWrited;
        for (int i=0; i < NUM_BOOKS; i++) {
            if (availableBooks[i].ISBN == ISBN && availableBooks[i].checkedOut == false) {
                foundAvail = true;
                break;
            }
        }

        while (!checkedOutBooks.empty()) {
            if (checkedOutBooks.front().ISBN == ISBN) {
                foundChecked = true;
                break;
            }
            temp.push(checkedOutBooks.front());
            checkedOutBooks.pop();
        }
        while (!temp.empty()) {
            checkedOutBooks.push(temp.front());
            temp.pop();
        }
        if (foundAvail == true) {
            cout << "This book with ISBN " << ISBN <<" exists!\n Do you want to overwrite? Yes(y) or No(n)?" << endl;
            cin >> isOverWrited;
            if (isOverWrited == "y") {
                updateBook(ISBN, title, author);
                clear();
            } else {
                cout << "Cancel!" << endl;
            }
        } else {
            Book b(title, author, ISBN);
            addBook(b);
            added = true;
        };
        if (foundChecked == true) {
            cout << "This book with ISBN " << ISBN <<" exists!\n Do you want to overwrite? Yes(y) or No(n)?" << endl;
            cin >> isOverWrited;
            if (isOverWrited == "y") {
                while (!checkedOutBooks.empty()) {
                    if (checkedOutBooks.front().ISBN == ISBN) {
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
                Book b(title, author, ISBN);
                addBook(b);
                checkOutBook(ISBN);
                clear();
            } else {
                cout << "Cancel!" << endl;
            };
        } else {
            if (added == false) {
                Book b(title, author, ISBN);
                addBook(b);
            }
        };
    }

    void studentCheckOut(string studentID, string studentName, string ISBN, string borrowDate) {
        bool found = false;
        for (int i = 0; i <= NUM_BOOKS; i++) {
            if (availableBooks[i].ISBN == ISBN && !availableBooks[i].checkedOut) {
                for (int j = 0; j <= NUM_STUDENTS; j++) {
                    if (studentBorrow[j].ISBN == ISBN) {
                        found = true;
                        studentBorrow[j].studentID = studentID;
                        studentBorrow[j].studentName = studentName;
                        studentBorrow[j].borrowDate = borrowDate;
                        break;
                    }
                }
            }
        }
        if (!found) {
            StudentInfo s(studentID, studentName, ISBN, borrowDate);
            addStudent(s);
        } else {

        }
    }
    
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
    void returnBook(string ISBN, string returnDate) {
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
        } else {
            cout << "\t\tThe book has been returned." << endl;
            for (int i = 0; i < NUM_STUDENTS; i++) {
                if (studentBorrow[i].ISBN == ISBN) {
                    CountDays(studentBorrow[i].borrowDate,returnDate);
                }
            }
        }
    }

    // Function to sort books by title (Selection Sort)
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

		// Copy the remaining elements of R[], if there has some left
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
        for (int i = 0; i < NUM_BOOKS; i++) {
            if (availableBooks[i].ISBN == ISBN) {
                // Shift all books after the one to be deleted to the left
                if (!availableBooks[i].checkedOut) {
                    for (int j = i; j < NUM_BOOKS - 1; j++) {
                        availableBooks[j] = availableBooks[j + 1];
                    }
                    NUM_BOOKS--;
                    cout << "\t\tBook deleted." << endl;
                } else {
                    cout << "\t\tBook not found or being checked out." << endl;
                }
                break;
            }
        }
    }
    void CountDays(string borrowDate, string returnDate) {
        struct std::tm borrowDate_Converted = {};
        istringstream ss(borrowDate);
        ss >> get_time(&borrowDate_Converted, "%d/%m/%Y");

        struct std::tm returnDate_Converted = {};
        istringstream ss2(returnDate);
        ss2 >> get_time(&returnDate_Converted, "%d/%m/%Y");

        std::time_t x = std::mktime(&borrowDate_Converted);
        std::time_t y = std::mktime(&returnDate_Converted);

        double difference = std::difftime(y, x) / (60 * 60 * 24);

        cout << "\t\tThe time student borrows book: " <<std::ctime(&x);
        cout << "\t\tThe time student returns book: " << std::ctime(&y);
        cout << "\t\tStudent returns book after " << difference << " day(s)" << std::endl;

        //31 là khoảng thời gian cho phép mỗi lần mượn tính từ ngày mượn
        //difference là chênh lệch thời gian (ngày trả - ngày mượn)
        //=> difference-31 là số ngày nộp muộn

        if (difference > 31) {
            cout << "\t\tStudent is " << difference-31 << " day(s) late in returning book!" << endl;
            if (difference-31<10) { 
                cout << "\t\tWrite a report and commit to returning the book on time" << endl;
            } else if (difference-31<20) {
                cout << "\t\tStudents pay fines for late return of book" << endl;
                    } else if (difference-31>100) {
                        cout << "\t\tThe student is considered to have not returned the book and must compensate 100% of the cover price" << endl;
                    }
        }
    }

    const char Aseparator='=';
    const char separator=' ';
    void displayAllBooks() {
        int numberOfCheckedOutBook = checkedOutBooks.size();
        int availableBookInLibrary = NUM_BOOKS - numberOfCheckedOutBook;
    	cout<<"\t\t";
        cout << right<<setw(48)<<setfill(Aseparator)<<"AVAILABLE BOOKS"
             << right<<setw(36)<<setfill(Aseparator)<<""<< endl;
        cout<<"\t\tThe list of available books in library: "<< availableBookInLibrary << "/1000 books"<<endl;
        cout<<"\t\t";
        cout<<left<<setw(35)<<setfill(Aseparator)<<" Title "
            <<left<<setw(35)<<setfill(Aseparator)<<" Author "
            <<left<<setw(14)<<setfill(Aseparator)<<" ISBN "
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
        
        if(NUM_BOOKS!=0){
        	cout<<"\n\t\t";
            cout <<right<<setw(70)<<setfill(Aseparator)<<"CHECKED OUT BOOKS"
                 << right<<setw(105)<<setfill(Aseparator)<<""<< endl;
            cout<<"\t\t";
            cout<<"Total checked out book(s): "<< numberOfCheckedOutBook <<endl;
            cout<<"\t\t";
            cout<<left<<setw(35)<<setfill(Aseparator)<<" Title "
                <<left<<setw(35)<<setfill(Aseparator)<<" Author "
                <<left<<setw(35)<<setfill(Aseparator)<<" ISBN "
                <<left<<setw(25)<<setfill(Aseparator)<<" Student ID "
                <<left<<setw(25)<<setfill(Aseparator)<<" Student Name "
                <<left<<setw(25)<<setfill(Aseparator)<<" Date Checking Out "
                <<endl<<endl;
        }
		
        for (int i = 0; i < numberOfCheckedOutBook; i++) {
            Book book = checkedOutBooks.front();
            cout<<"\t\t";
            cout<<left<<setw(35)<<setfill(separator)<<book.title;
            cout<<left<<setw(35)<<setfill(separator)<<book.author;
            cout<<left<<setw(35)<<setfill(separator)<<book.ISBN;
            for (int j = 0; j < NUM_STUDENTS; j++) {
                if (book.ISBN == studentBorrow[j].ISBN) {
                    cout<<left<<setw(25)<<setfill(separator)<<studentBorrow[j].studentID;
                    cout<<left<<setw(25)<<setfill(separator)<<studentBorrow[j].studentName;
                    cout<<left<<setw(25)<<setfill(separator)<<studentBorrow[j].borrowDate;
                }
            }
            cout<<endl;
            checkedOutBooks.pop();
            checkedOutBooks.push(book);
        }
    }

    void readFromFile_availableBook(string fileName) {
        ifstream availableFile;
        bool found = false;
        string overWrite;
        //Read the available book from a file
        availableFile.open(fileName);
        if (!availableFile) {
            cout << "\t\tError opening file for available books." << endl;
            return;
        }

        string line, title, author, ISBN;
        while (getline(availableFile, line)) {
            // Use a stringstream to split the line into individual values
            stringstream ss(line);
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, ISBN);

            //Check if ISBN is already in book list
            for (int i = 0; i < NUM_BOOKS; i++) {
                if (availableBooks[i].ISBN == ISBN) {
                    found = true;
                }
            }
            if (!found) {
                Book b(title, author, ISBN);
                addBook(b);
            } else {
                cout << "The book with ISBN " << ISBN << " already exists!\nDo you want to overwrite? Yes(y) or No(n)" << endl;
                cin >> overWrite;
                if (overWrite == "y") {
                    deleteBook(ISBN);
                    Book b(title, author, ISBN);
                    addBook(b);
                }
            }
        }
        availableFile.close();
    }

    void readFromFile_CheckedOutBook(string fileName) {
        ifstream checkedFile;
        queue<Book> temp;
        bool found = false;
        string overWrite;

        //Read the available book from a file
        checkedFile.open(fileName);
        if (!checkedFile) {
            cout << "\t\tError opening file for checked out books." << endl;
            return;
        }

        string line, title, author, ISBN, studentID, studentName, borrowDate;
        while (getline(checkedFile, line)) {
            // Use a stringstream to split the line into individual values
            stringstream ss(line);
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, ISBN, ',');
            getline(ss, studentID, ',');
            getline(ss, studentName, ',');
            getline(ss, borrowDate);

            //Check if ISBN is already in book list
            for (int i = 0; i < NUM_BOOKS; i++) {
                if (availableBooks[i].ISBN == ISBN) {
                    found = true;
                }
            }

            while (!checkedOutBooks.empty()) {
                if (checkedOutBooks.front().ISBN == ISBN) {
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

            if (!found) {
                Book b(title, author, ISBN);
                StudentInfo c(studentID, studentName, ISBN, borrowDate);
                addBook(b);
                studentCheckOut(studentID, studentName, ISBN, borrowDate);
                checkOutBook(ISBN);
            } else {
                cout << "The book with ISBN " << ISBN << " already exists!\nDo you want to overwrite? Yes(y) or No(n)" << endl;
                cin >> overWrite;
                if (overWrite == "y") {

                    while (!checkedOutBooks.empty()) {
                        if (checkedOutBooks.front().ISBN == ISBN) {
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

                    Book b(title, author, ISBN);
                    addBook(b);
                    checkOutBook(ISBN);
                }
            }
            
        }
        checkedFile.close();
    }

    void printToFile(const string &fileName) {
        ofstream outFile;
        outFile.open(fileName);
        if (outFile.is_open()) {
            outFile<<left<<setw(35)<<setfill(separator)<<""
                   <<left<<setw(35)<<setfill(separator)<<"LIBRARY MANAGEMENT SYSTEM"
                   <<endl<<endl;
            outFile<<"\t\tAvailable Book"<<endl;
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
            }
            outFile<<endl<<endl;
            // Write the records of the checked out books to the file
            outFile<<"\t\tBook(s) are checked out"<<endl;
            int size = checkedOutBooks.size();
            outFile<<"\t\tThe list of book(s) borrowed:"<<" "<<size<<endl;
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

    void writeToFile_Re_usable_availableBook(const string &fileName) {
        ofstream outFile;
        outFile.open(fileName);
        if (outFile.is_open()) {
            // Write the records of the available books to the file
            for (int i = 0; i < NUM_BOOKS; i++) {
                if (!availableBooks[i].checkedOut) {
                    outFile << availableBooks[i].title << "," << availableBooks[i].author << "," << availableBooks[i].ISBN << endl;
                }
            }
            outFile.close();
        } else {
            cout << "\t\tError: Unable to open file." << endl;
        }
    }

    void writeToFile_Re_usable_CheckedBook(const string &fileName) {
        ofstream outFile;
        outFile.open(fileName);
        if (outFile.is_open()) {
            int size = checkedOutBooks.size();
            for (int i = 0; i < size; i++) {
                Book book = checkedOutBooks.front();
                for (int j = 0; j < NUM_STUDENTS; j ++) {
                    if ( book.ISBN == studentBorrow[j].ISBN) {
                        cout<<"\t\t";
                        outFile << book.title << "," << book.author << "," << book.ISBN << "," << studentBorrow[j].studentID << "," << studentBorrow[j].studentName << "," << studentBorrow[j].borrowDate <<endl;
                        checkedOutBooks.pop();
                        checkedOutBooks.push(book);
                    }
                }

            }
            
            // Write the records of the available books to the file
            outFile.close();
        } else {
            cout << "\t\tError: Unable to open file." << endl;
        }
    }

    void searchByTitle(string title) {
        bool found = false;
        queue<Book> temp;
        
        // Search through available books
        for (int i = 0; i < NUM_BOOKS; i++) {
            if (availableBooks[i].title == title && !availableBooks[i].checkedOut) {
                cout << "Title   : " << availableBooks[i].title << endl;
                cout << "Author  : " << availableBooks[i].author << endl;
                cout << "ISBN    : " << availableBooks[i].ISBN << endl;
                found = true;
            }
        }

        // Search through checked out books
        while (!checkedOutBooks.empty()) {
            if (checkedOutBooks.front().title == title) {
                cout << "Title   : " << checkedOutBooks.front().title << endl;
                cout << "Author  : " << checkedOutBooks.front().author << endl;
                cout << "ISBN    : " << checkedOutBooks.front().ISBN << endl;
                cout << "This book is checked out by: " << endl;
                for (int i = 0; i < NUM_STUDENTS; i++) {
                    if (studentBorrow[i].ISBN == checkedOutBooks.front().ISBN) {
                        cout << "Student ID: "<< studentBorrow[i].studentID << "\tName: " << studentBorrow[i].studentName << endl;
                        cout << "On " << studentBorrow[i].borrowDate << endl;
                    }
                }
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
                cout << "This book is checked out by:" << endl;
                for (int i = 0; i < NUM_STUDENTS; i++) {
                    if (studentBorrow[i].ISBN == checkedOutBooks.front().ISBN) {
                        cout << "Student ID: "<< studentBorrow[i].studentID << "\tName: " << studentBorrow[i].studentName << endl;
                        cout << "On " << studentBorrow[i].borrowDate << endl;
                    }
                }
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
            cout << "\t\tCannot find out this author!" << endl;
        }
    }
    void intro()
    {
        cout<<"\t\tNGUYỄN NGỌC HƯNG - LEADER           21070167"<<endl;
        cout<<"\t\tTRẦN ĐẶNG MẠNH                      21070489"<<endl;
        cout<<"\t\tNGÔ DIỆU LINH                       20070948"<<endl;
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
    // library.readFromFile_availableBook("availableBookData.txt");
    // library.readFromFile_CheckedOutBook("checkedOutBookData.txt");
    
    while (choice != 14) {
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
        cout << "\t\tPress 6.  Update a book" << endl;
        cout << "\t\tPress 7.  Delete a book" << endl;
        cout << "\t\tPress 8.  Search for a book by title" << endl;
        cout << "\t\tPress 9.  Search for a book by author" << endl;
        cout << "\t\tPress 10. Display all books" << endl;
        cout << "\t\tPress 11. Read books from default files" << endl;
        cout << "\t\tPress 12. Read books from choosen files" << endl;
        cout << "\t\tPress 13. Print the list of books to a file" << endl;
        cout << "\t\tPress 14. Save to files & Quit" << endl;
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
                library.avoidDuplicatedBook(title, author, ISBN);
                library.clear();
                break;
            }
            case 2: {
                string studentID; string studentName; string ISBN; string borrowDate;
                library.displayAllBooks();
                cout << "\t\tEnter the ISBN of the book you want to check out: ";
                cin.ignore();
                getline(cin, ISBN);
                cout << "\n\t\tEnter Student ID: " << endl;
                cout << "\t\t";
                cin >> studentID;
                cout << "\n\t\tEnter Student Name: " << endl;
                cout << "\t\t";
                cin.ignore();
                getline(cin, studentName);
                cout << "\n\t\tEnter the day checking out (DD/MM/YYYY): " << endl;
                cout << "\t\t";
                cin >> borrowDate;
                library.studentCheckOut(studentID, studentName, ISBN, borrowDate);
                library.checkOutBook(ISBN);
                library.clear();
                break;
            }
            case 3: {
                string ISBN; string returnDate;
                library.displayAllBooks();
                cout << "\t\tEnter the ISBN of the book you want to return: ";
                cin.ignore();
                getline(cin, ISBN);
                cout << "\t\tEnter the day returning book: ";
                cin >> returnDate;
                library.returnBook(ISBN, returnDate);
                library.clear();
                break;
            }
            
            case 4: {
                library.sortByTitle();
                library.sortCheckedOutBooksByTitle();
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 5: {
                library.sortByAuthor();
                library.sortCheckedOutBooksByAuthor();
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 6:{
                string title, author, ISBN;
                library.displayAllBooks();
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
            case 7: {
                string ISBN;
                library.displayAllBooks();
                cout << "\t\tEnter the ISBN of the book you want to delete: ";
                cin.ignore();
                getline(cin, ISBN);
                library.deleteBook(ISBN);
                library.clear();
                break;
            }
            case 8:{
                string title;
                cout << "\t\tEnter the title of the book you want to search for: ";
                cin.ignore();
                getline(cin, title);
                library.searchByTitle(title);
                library.clear();
                break;
            }
            case 9:{
                string author;
                cout << "\t\tEnter the author of the book you want to search for: ";
                cin.ignore();
                getline(cin, author);
                library.searchByAuthor(author);
                library.clear();
                break;
            }
            case 10: {
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 11: {
                library.readFromFile_availableBook("availableBookData.txt");
                library.readFromFile_CheckedOutBook("checkedOutBookData.txt");
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 12: {
                string availableBookfile, checkedOutBookFile;
                
                cout << "\t\tEnter the name of the file you want to read from: ";
                cout << "\n\t\tAvailable book's file name: ";
                cin.ignore();
                getline(cin, availableBookfile);
                cout << "\t\tChecked out book's file name: ";
                
                getline(cin, checkedOutBookFile);
                library.readFromFile_availableBook(availableBookfile);
                library.readFromFile_CheckedOutBook(checkedOutBookFile);
                library.displayAllBooks();
                library.clear();
                break;
            }
            case 13: {
                string fileName;
                cout << "\t\tEnter the name of the file you want to write to: ";
                cin.ignore();
                getline(cin, fileName);
                library.printToFile(fileName);
                library.clear();
                break;
            }
            case 14: {
                string isSaved;
                string manualSavedAvailable;
                string manualSavedCheckedOut;
                do {
                    cout << "\n\t\tDo you want to save to defaut files? (y/n)\n" << endl;
                    cin.ignore();
                    cin >> isSaved;
                    if (isSaved == "y") {
                        library.writeToFile_Re_usable_availableBook("availableBookData.txt");
                        library.writeToFile_Re_usable_CheckedBook("checkedOutBookData.txt");
                        cout << "\t\tSaved to default file!" << endl;
                        library.clear();
                    }
                    if (isSaved == "n") {
                        cout << "\t\tPlease enter file name for available books:" << endl;
                        cin.ignore();
                        cin >> manualSavedAvailable;
                        library.writeToFile_Re_usable_availableBook(manualSavedAvailable);

                        cout << "\t\tPlease enter file name for checked out books:" << endl;
                        cin.ignore();
                        cin >> manualSavedCheckedOut;
                        library.writeToFile_Re_usable_CheckedBook(manualSavedCheckedOut);
                        cout << "\n\t\tSaved to " << manualSavedAvailable << " and " << manualSavedCheckedOut << " file!" << endl;
                    }
                } while (isSaved != "y" && isSaved != "n");
                cout << "\n\t\tThank you for using the library. See you later!" << endl;
                break;
            }
            default: {
                cout << "\t\tInvalid choice. Please try again." << endl;
                system("\t\tPAUSE");
                break;
            }
        }
    }

    return 0;
}
