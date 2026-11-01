#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

// MySQL connection details
const char* SERVER = "localhost";
const char* USER = "root";
const char* PASSWORD = "Ssahu@75#";
const char* DATABASE = "smart_library";
const unsigned int PORT = 3306;

// --------------------------------------------------
// Connect to MySQL
// --------------------------------------------------
MYSQL* connectDatabase()
{
    MYSQL* conn = mysql_init(NULL);

    if (conn == NULL)
    {
        cout << "\nMySQL initialization failed!\n";
        return NULL;
    }

    if (mysql_real_connect(
            conn,
            SERVER,
            USER,
            PASSWORD,
            DATABASE,
            PORT,
            NULL,
            0) == NULL)
    {
        cout << "\nMySQL connection failed!\n";
        cout << "Error: " << mysql_error(conn) << endl;

        mysql_close(conn);
        return NULL;
    }

    return conn;
}

// --------------------------------------------------
// Add Book
// --------------------------------------------------
void addBook(MYSQL* conn)
{
    string title, isbn;
    int authorId, categoryId, totalCopies;

    cout << "\n========== ADD BOOK ==========\n";

    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter author ID: ";
    cin >> authorId;

    cout << "Enter category ID: ";
    cin >> categoryId;

    cout << "Enter ISBN: ";
    cin >> isbn;

    cout << "Enter total copies: ";
    cin >> totalCopies;

    // Escape text input
    char escapedTitle[1000];
    char escapedISBN[500];

    mysql_real_escape_string(
        conn,
        escapedTitle,
        title.c_str(),
        title.length()
    );

    mysql_real_escape_string(
        conn,
        escapedISBN,
        isbn.c_str(),
        isbn.length()
    );

    string query =
        "INSERT INTO books "
        "(title, author_id, category_id, isbn, total_copies, available_copies) "
        "VALUES ('" +
        string(escapedTitle) + "', " +
        to_string(authorId) + ", " +
        to_string(categoryId) + ", '" +
        string(escapedISBN) + "', " +
        to_string(totalCopies) + ", " +
        to_string(totalCopies) + ")";

    if (mysql_query(conn, query.c_str()) == 0)
    {
        cout << "\nBook added successfully!\n";
    }
    else
    {
        cout << "\nFailed to add book.\n";
        cout << "Error: " << mysql_error(conn) << endl;
    }
}

// --------------------------------------------------
// View Books
// --------------------------------------------------
void viewBooks(MYSQL* conn)
{
    cout << "\n========== ALL BOOKS ==========\n";

    string query =
        "SELECT book_id, title, author_id, category_id, isbn, "
        "total_copies, available_copies FROM books";

    if (mysql_query(conn, query.c_str()) != 0)
    {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    if (result == NULL)
    {
        cout << "Unable to retrieve books.\n";
        return;
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        cout << "\nBook ID: " << row[0];
        cout << "\nTitle: " << row[1];
        cout << "\nAuthor ID: " << row[2];
        cout << "\nCategory ID: " << row[3];
        cout << "\nISBN: " << row[4];
        cout << "\nTotal Copies: " << row[5];
        cout << "\nAvailable Copies: " << row[6];
        cout << "\n-----------------------------";
    }

    mysql_free_result(result);
    cout << endl;
}

// --------------------------------------------------
// Search Book
// --------------------------------------------------
void searchBook(MYSQL* conn)
{
    string keyword;

    cout << "\n========== SEARCH BOOK ==========\n";

    cout << "Enter book title or ISBN: ";
    cin.ignore();
    getline(cin, keyword);

    char escapedKeyword[1000];

    mysql_real_escape_string(
        conn,
        escapedKeyword,
        keyword.c_str(),
        keyword.length()
    );

    string query =
        "SELECT book_id, title, isbn, total_copies, available_copies "
        "FROM books "
        "WHERE title LIKE '%" +
        string(escapedKeyword) +
        "%' OR isbn LIKE '%" +
        string(escapedKeyword) +
        "%'";

    if (mysql_query(conn, query.c_str()) != 0)
    {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    if (result == NULL)
    {
        cout << "No result found.\n";
        return;
    }

    MYSQL_ROW row;
    bool found = false;

    while ((row = mysql_fetch_row(result)))
    {
        found = true;

        cout << "\nBook ID: " << row[0];
        cout << "\nTitle: " << row[1];
        cout << "\nISBN: " << row[2];
        cout << "\nTotal Copies: " << row[3];
        cout << "\nAvailable Copies: " << row[4];
        cout << "\n-----------------------------";
    }

    if (!found)
    {
        cout << "\nNo book found.\n";
    }

    mysql_free_result(result);
    cout << endl;
}

// --------------------------------------------------
// Add Student
// --------------------------------------------------
void addStudent(MYSQL* conn)
{
    string name, email;

    cout << "\n========== ADD STUDENT ==========\n";

    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter student email: ";
    cin >> email;

    char escapedName[500];
    char escapedEmail[500];

    mysql_real_escape_string(
        conn,
        escapedName,
        name.c_str(),
        name.length()
    );

    mysql_real_escape_string(
        conn,
        escapedEmail,
        email.c_str(),
        email.length()
    );

    string query =
        "INSERT INTO students (student_name, email) VALUES ('" +
        string(escapedName) + "', '" +
        string(escapedEmail) + "')";

    if (mysql_query(conn, query.c_str()) == 0)
    {
        cout << "\nStudent added successfully!\n";
    }
    else
    {
        cout << "\nFailed to add student.\n";
        cout << "Error: " << mysql_error(conn) << endl;
    }
}

// --------------------------------------------------
// View Students
// --------------------------------------------------
void viewStudents(MYSQL* conn)
{
    cout << "\n========== ALL STUDENTS ==========\n";

    string query =
        "SELECT student_id, student_name, email FROM students";

    if (mysql_query(conn, query.c_str()) != 0)
    {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    if (result == NULL)
    {
        cout << "Unable to retrieve students.\n";
        return;
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        cout << "\nStudent ID: " << row[0];
        cout << "\nName: " << row[1];
        cout << "\nEmail: " << row[2];
        cout << "\n-----------------------------";
    }

    mysql_free_result(result);
    cout << endl;
}

// --------------------------------------------------
// Issue Book
// --------------------------------------------------
void issueBook(MYSQL* conn)
{
    int bookId, studentId, librarianId;

    cout << "\n========== ISSUE BOOK ==========\n";

    cout << "Enter book ID: ";
    cin >> bookId;

    cout << "Enter student ID: ";
    cin >> studentId;

    cout << "Enter librarian ID: ";
    cin >> librarianId;

    // Check book availability
    string checkQuery =
        "SELECT available_copies FROM books "
        "WHERE book_id = " +
        to_string(bookId);

    if (mysql_query(conn, checkQuery.c_str()) != 0)
    {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    if (result == NULL)
    {
        cout << "Book not found.\n";
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row == NULL)
    {
        cout << "\nBook not found.\n";
        mysql_free_result(result);
        return;
    }

    int availableCopies = stoi(row[0]);

    mysql_free_result(result);

    if (availableCopies <= 0)
    {
        cout << "\nBook is currently unavailable.\n";
        return;
    }

    // Insert issue record
    string issueQuery =
        "INSERT INTO book_issues "
        "(book_id, student_id, librarian_id, issue_date, due_date) "
        "VALUES (" +
        to_string(bookId) + ", " +
        to_string(studentId) + ", " +
        to_string(librarianId) +
        ", CURDATE(), DATE_ADD(CURDATE(), INTERVAL 14 DAY))";

    if (mysql_query(conn, issueQuery.c_str()) != 0)
    {
        cout << "\nFailed to issue book.\n";
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }

    // Decrease available copies
    string updateQuery =
        "UPDATE books "
        "SET available_copies = available_copies - 1 "
        "WHERE book_id = " +
        to_string(bookId);

    if (mysql_query(conn, updateQuery.c_str()) == 0)
    {
        cout << "\nBook issued successfully!\n";
        cout << "Due date: 14 days from today.\n";
    }
    else
    {
        cout << "\nBook issued but stock update failed.\n";
        cout << "Error: " << mysql_error(conn) << endl;
    }
}

// --------------------------------------------------
// Return Book
// --------------------------------------------------
void returnBook(MYSQL* conn)
{
    int issueId;

    cout << "\n========== RETURN BOOK ==========\n";

    cout << "Enter issue ID: ";
    cin >> issueId;

    // Find active issue
    string findQuery =
        "SELECT book_id FROM book_issues "
        "WHERE issue_id = " +
        to_string(issueId) +
        " AND return_date IS NULL";

    if (mysql_query(conn, findQuery.c_str()) != 0)
    {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    if (result == NULL)
    {
        cout << "Unable to find issue record.\n";
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row == NULL)
    {
        cout << "\nInvalid issue ID or book already returned.\n";
        mysql_free_result(result);
        return;
    }

    int bookId = stoi(row[0]);

    mysql_free_result(result);

    // Update return date
    string returnQuery =
        "UPDATE book_issues "
        "SET return_date = CURDATE() "
        "WHERE issue_id = " +
        to_string(issueId);

    if (mysql_query(conn, returnQuery.c_str()) != 0)
    {
        cout << "\nFailed to return book.\n";
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }

    // Increase available copies
    string updateQuery =
        "UPDATE books "
        "SET available_copies = available_copies + 1 "
        "WHERE book_id = " +
        to_string(bookId);

    if (mysql_query(conn, updateQuery.c_str()) == 0)
    {
        cout << "\nBook returned successfully!\n";
    }
    else
    {
        cout << "\nBook returned but stock update failed.\n";
        cout << "Error: " << mysql_error(conn) << endl;
    }
}

// --------------------------------------------------
// View Issued Books
// --------------------------------------------------
void viewIssuedBooks(MYSQL* conn)
{
    cout << "\n========== ISSUED BOOKS ==========\n";

    string query =
        "SELECT book_issues.issue_id, "
        "books.title, "
        "students.student_name, "
        "book_issues.issue_date, "
        "book_issues.due_date, "
        "book_issues.return_date "
        "FROM book_issues "
        "INNER JOIN books "
        "ON book_issues.book_id = books.book_id "
        "INNER JOIN students "
        "ON book_issues.student_id = students.student_id "
        "ORDER BY book_issues.issue_id DESC";

    if (mysql_query(conn, query.c_str()) != 0)
    {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    if (result == NULL)
    {
        cout << "Unable to retrieve issue records.\n";
        return;
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        cout << "\nIssue ID: " << row[0];
        cout << "\nBook: " << row[1];
        cout << "\nStudent: " << row[2];
        cout << "\nIssue Date: " << row[3];
        cout << "\nDue Date: " << row[4];
        cout << "\nReturn Date: "
             << (row[5] ? row[5] : "Not Returned");

        cout << "\n-----------------------------";
    }

    mysql_free_result(result);
    cout << endl;
}

// --------------------------------------------------
// Library Reports
// --------------------------------------------------
void libraryReports(MYSQL* conn)
{
    cout << "\n========== LIBRARY REPORTS ==========\n";

    // Total books
    string query1 =
        "SELECT COUNT(*) FROM books";

    if (mysql_query(conn, query1.c_str()) == 0)
    {
        MYSQL_RES* result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);

        if (row)
            cout << "\nTotal Book Titles: " << row[0];

        mysql_free_result(result);
    }

    // Total students
    string query2 =
        "SELECT COUNT(*) FROM students";

    if (mysql_query(conn, query2.c_str()) == 0)
    {
        MYSQL_RES* result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);

        if (row)
            cout << "\nTotal Students: " << row[0];

        mysql_free_result(result);
    }

    // Currently issued books
    string query3 =
        "SELECT COUNT(*) FROM book_issues "
        "WHERE return_date IS NULL";

    if (mysql_query(conn, query3.c_str()) == 0)
    {
        MYSQL_RES* result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);

        if (row)
            cout << "\nCurrently Issued Books: " << row[0];

        mysql_free_result(result);
    }

    // Available copies
    string query4 =
        "SELECT COALESCE(SUM(available_copies), 0) FROM books";

    if (mysql_query(conn, query4.c_str()) == 0)
    {
        MYSQL_RES* result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);

        if (row)
            cout << "\nAvailable Book Copies: " << row[0];

        mysql_free_result(result);
    }

    cout << "\n";
}

// --------------------------------------------------
// Main Function
// --------------------------------------------------
int main()
{
    cout << "========================================\n";
    cout << "       SMART LIBRARY MANAGEMENT SYSTEM\n";
    cout << "========================================\n";

    MYSQL* conn = connectDatabase();

    if (conn == NULL)
    {
        cout << "\nCould not connect to database.\n";
        cout << "Please check MySQL Server and password.\n";
        return 1;
    }

    cout << "\nMySQL Connected Successfully!\n";

    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "          SMART LIBRARY MENU\n";
        cout << "========================================\n";

        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Add Student\n";
        cout << "5. View Students\n";
        cout << "6. Issue Book\n";
        cout << "7. Return Book\n";
        cout << "8. View Issued Books\n";
        cout << "9. Library Reports\n";
        cout << "0. Exit\n";

        cout << "----------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addBook(conn);
                break;

            case 2:
                viewBooks(conn);
                break;

            case 3:
                searchBook(conn);
                break;

            case 4:
                addStudent(conn);
                break;

            case 5:
                viewStudents(conn);
                break;

            case 6:
                issueBook(conn);
                break;

            case 7:
                returnBook(conn);
                break;

            case 8:
                viewIssuedBooks(conn);
                break;

            case 9:
                libraryReports(conn);
                break;

            case 0:
                cout << "\nThank you for using Smart Library Management System!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);

    mysql_close(conn);

    return 0;
}