USE smart_library;

-- ==========================================
-- JOIN QUERIES
-- ==========================================

-- 1. Books with author names
SELECT
    books.title,
    authors.author_name
FROM books
INNER JOIN authors
    ON books.author_id = authors.author_id;


-- 2. Books with categories
SELECT
    books.title,
    categories.category_name
FROM books
INNER JOIN categories
    ON books.category_id = categories.category_id;


-- 3. Books with author and category
SELECT
    books.title,
    authors.author_name,
    categories.category_name
FROM books
INNER JOIN authors
    ON books.author_id = authors.author_id
INNER JOIN categories
    ON books.category_id = categories.category_id;


-- 4. Issued books with student names
SELECT
    students.student_name,
    books.title,
    book_issues.issue_date,
    book_issues.due_date
FROM book_issues
INNER JOIN students
    ON book_issues.student_id = students.student_id
INNER JOIN books
    ON book_issues.book_id = books.book_id;


-- 5. Issued books with student and librarian names
SELECT
    students.student_name,
    books.title,
    librarians.librarian_name,
    book_issues.issue_date,
    book_issues.due_date
FROM book_issues
INNER JOIN students
    ON book_issues.student_id = students.student_id
INNER JOIN books
    ON book_issues.book_id = books.book_id
INNER JOIN librarians
    ON book_issues.librarian_id = librarians.librarian_id;


-- 6. All books with author names
SELECT
    books.book_id,
    books.title,
    authors.author_name,
    books.total_copies,
    books.available_copies
FROM books
LEFT JOIN authors
    ON books.author_id = authors.author_id;


-- 7. Students who have issued books
SELECT DISTINCT
    students.student_id,
    students.student_name,
    students.department
FROM students
INNER JOIN book_issues
    ON students.student_id = book_issues.student_id;


-- 8. Currently issued books
SELECT
    students.student_name,
    books.title,
    book_issues.issue_date,
    book_issues.due_date
FROM book_issues
INNER JOIN students
    ON book_issues.student_id = students.student_id
INNER JOIN books
    ON book_issues.book_id = books.book_id
WHERE book_issues.return_date IS NULL;