USE smart_library;

-- ==========================================
-- INSERT STUDENTS
-- ==========================================

INSERT INTO students
(student_name, email, phone, department)
VALUES
('Rahul Sharma', 'rahul.sharma@example.com', '9876543210', 'Computer Science'),
('Priya Singh', 'priya.singh@example.com', '9876543211', 'Information Technology'),
('Aman Verma', 'aman.verma@example.com', '9876543212', 'Electronics'),
('Neha Gupta', 'neha.gupta@example.com', '9876543213', 'Computer Science'),
('Rohit Kumar', 'rohit.kumar@example.com', '9876543214', 'Mechanical');


-- ==========================================
-- INSERT AUTHORS
-- ==========================================

INSERT INTO authors
(author_name)
VALUES
('Robert C. Martin'),
('James Clear'),
('Andrew S. Tanenbaum'),
('Thomas H. Cormen'),
('J.K. Rowling');


-- ==========================================
-- INSERT CATEGORIES
-- ==========================================

INSERT INTO categories
(category_name)
VALUES
('Programming'),
('Self Development'),
('Computer Networks'),
('Algorithms'),
('Fiction');


-- ==========================================
-- INSERT BOOKS
-- ==========================================

INSERT INTO books
(title, author_id, category_id, isbn, total_copies, available_copies)
VALUES
('Clean Code', 1, 1, '9780132350884', 5, 4),
('Atomic Habits', 2, 2, '9780735211292', 4, 3),
('Computer Networks', 3, 3, '9780132126953', 6, 5),
('Introduction to Algorithms', 4, 4, '9780262046305', 5, 4),
('Harry Potter and the Philosopher Stone', 5, 5, '9780747532699', 3, 2);


-- ==========================================
-- INSERT LIBRARIANS
-- ==========================================

INSERT INTO librarians
(librarian_name, email)
VALUES
('Anita Sharma', 'anita.library@example.com'),
('Vikash Patel', 'vikash.library@example.com');


-- ==========================================
-- INSERT BOOK ISSUES
-- ==========================================

INSERT INTO book_issues
(book_id, student_id, librarian_id, issue_date, due_date, return_date)
VALUES
(1, 1, 1, '2026-08-01', '2026-08-15', NULL),
(2, 2, 1, '2026-08-02', '2026-08-16', NULL),
(3, 3, 2, '2026-08-03', '2026-08-17', '2026-08-10'),
(4, 4, 2, '2026-08-04', '2026-08-18', NULL),
(5, 5, 1, '2026-08-05', '2026-08-19', NULL);