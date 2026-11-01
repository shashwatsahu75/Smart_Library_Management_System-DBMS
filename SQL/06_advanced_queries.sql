USE smart_library;

-- ==========================================
-- ADVANCED SQL QUERIES
-- ==========================================

-- 1. Students who have issued at least one book
SELECT DISTINCT
    students.student_id,
    students.student_name,
    students.email
FROM students
INNER JOIN book_issues
    ON students.student_id = book_issues.student_id;


-- 2. Books that have never been issued
SELECT
    books.book_id,
    books.title
FROM books
LEFT JOIN book_issues
    ON books.book_id = book_issues.book_id
WHERE book_issues.issue_id IS NULL;


-- 3. Students who have issued more than one book
SELECT
    students.student_id,
    students.student_name,
    COUNT(book_issues.issue_id) AS total_issues
FROM students
INNER JOIN book_issues
    ON students.student_id = book_issues.student_id
GROUP BY students.student_id, students.student_name
HAVING COUNT(book_issues.issue_id) > 1;


-- 4. Books with available copies less than total copies
SELECT
    book_id,
    title,
    total_copies,
    available_copies
FROM books
WHERE available_copies < total_copies;


-- 5. Currently issued books
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


-- 6. Overdue books
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


-- 7. Student who has issued the most books
SELECT
    students.student_name,
    COUNT(book_issues.issue_id) AS total_issues
FROM students
INNER JOIN book_issues
    ON students.student_id = book_issues.student_id
GROUP BY students.student_id, students.student_name
ORDER BY total_issues DESC
LIMIT 1;


-- 8. Most issued book
SELECT
    books.title,
    COUNT(book_issues.issue_id) AS times_issued
FROM books
INNER JOIN book_issues
    ON books.book_id = book_issues.book_id
GROUP BY books.book_id, books.title
ORDER BY times_issued DESC
LIMIT 1;