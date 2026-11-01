USE smart_library;

-- ==========================================
-- LIBRARY REPORTS
-- ==========================================

-- 1. Available Books Report
SELECT
    books.book_id,
    books.title,
    authors.author_name,
    categories.category_name,
    books.total_copies,
    books.available_copies
FROM books
INNER JOIN authors
    ON books.author_id = authors.author_id
INNER JOIN categories
    ON books.category_id = categories.category_id
WHERE books.available_copies > 0;


-- 2. Issued Books Report
SELECT
    book_issues.issue_id,
    books.title,
    students.student_name,
    librarians.librarian_name,
    book_issues.issue_date,
    book_issues.due_date
FROM book_issues
INNER JOIN books
    ON book_issues.book_id = books.book_id
INNER JOIN students
    ON book_issues.student_id = students.student_id
INNER JOIN librarians
    ON book_issues.librarian_id = librarians.librarian_id;


-- 3. Currently Issued Books Report
SELECT
    books.title,
    students.student_name,
    book_issues.issue_date,
    book_issues.due_date
FROM book_issues
INNER JOIN books
    ON book_issues.book_id = books.book_id
INNER JOIN students
    ON book_issues.student_id = students.student_id
WHERE book_issues.return_date IS NULL;


-- 4. Returned Books Report
SELECT
    books.title,
    students.student_name,
    book_issues.issue_date,
    book_issues.return_date
FROM book_issues
INNER JOIN books
    ON book_issues.book_id = books.book_id
INNER JOIN students
    ON book_issues.student_id = students.student_id
WHERE book_issues.return_date IS NOT NULL;


-- 5. Student-wise Book Issue Report
SELECT
    students.student_name,
    COUNT(book_issues.issue_id) AS total_books_issued
FROM students
LEFT JOIN book_issues
    ON students.student_id = book_issues.student_id
GROUP BY students.student_id, students.student_name
ORDER BY total_books_issued DESC;


-- 6. Category-wise Book Report
SELECT
    categories.category_name,
    COUNT(books.book_id) AS total_books
FROM categories
LEFT JOIN books
    ON categories.category_id = books.category_id
GROUP BY categories.category_id, categories.category_name
ORDER BY total_books DESC;


-- 7. Author-wise Book Report
SELECT
    authors.author_name,
    COUNT(books.book_id) AS total_books
FROM authors
LEFT JOIN books
    ON authors.author_id = books.author_id
GROUP BY authors.author_id, authors.author_name
ORDER BY total_books DESC;


-- 8. Library Summary Report
SELECT
    (SELECT COUNT(*) FROM books) AS total_book_titles,
    (SELECT SUM(total_copies) FROM books) AS total_book_copies,
    (SELECT SUM(available_copies) FROM books) AS available_book_copies,
    (SELECT COUNT(*) FROM students) AS total_students,
    (SELECT COUNT(*) FROM librarians) AS total_librarians,
    (SELECT COUNT(*) FROM book_issues) AS total_issues;


-- 9. Overdue Books Report
SELECT
    books.title,
    students.student_name,
    book_issues.due_date
FROM book_issues
INNER JOIN books
    ON book_issues.book_id = books.book_id
INNER JOIN students
    ON book_issues.student_id = students.student_id
WHERE book_issues.return_date IS NULL
AND book_issues.due_date < CURDATE();


-- 10. Complete Library Report
SELECT
    books.title,
    authors.author_name,
    categories.category_name,
    books.total_copies,
    books.available_copies
FROM books
INNER JOIN authors
    ON books.author_id = authors.author_id
INNER JOIN categories
    ON books.category_id = categories.category_id
ORDER BY books.title;