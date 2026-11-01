USE smart_library;

-- ==========================================
-- STUDENTS TABLE
-- ==========================================

CREATE TABLE IF NOT EXISTS students (
    student_id INT AUTO_INCREMENT PRIMARY KEY,
    student_name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    phone VARCHAR(15),
    department VARCHAR(100)
);


-- ==========================================
-- AUTHORS TABLE
-- ==========================================

CREATE TABLE IF NOT EXISTS authors (
    author_id INT AUTO_INCREMENT PRIMARY KEY,
    author_name VARCHAR(100) NOT NULL
);


-- ==========================================
-- CATEGORIES TABLE
-- ==========================================

CREATE TABLE IF NOT EXISTS categories (
    category_id INT AUTO_INCREMENT PRIMARY KEY,
    category_name VARCHAR(100) NOT NULL
);


-- ==========================================
-- BOOKS TABLE
-- ==========================================

CREATE TABLE IF NOT EXISTS books (
    book_id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    author_id INT,
    category_id INT,
    isbn VARCHAR(20) UNIQUE,
    total_copies INT NOT NULL,
    available_copies INT NOT NULL,

    FOREIGN KEY (author_id)
        REFERENCES authors(author_id),

    FOREIGN KEY (category_id)
        REFERENCES categories(category_id)
);


-- ==========================================
-- LIBRARIANS TABLE
-- ==========================================

CREATE TABLE IF NOT EXISTS librarians (
    librarian_id INT AUTO_INCREMENT PRIMARY KEY,
    librarian_name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE
);


-- ==========================================
-- BOOK ISSUES TABLE
-- ==========================================

CREATE TABLE IF NOT EXISTS book_issues (
    issue_id INT AUTO_INCREMENT PRIMARY KEY,
    book_id INT NOT NULL,
    student_id INT NOT NULL,
    librarian_id INT NOT NULL,
    issue_date DATE NOT NULL,
    due_date DATE NOT NULL,
    return_date DATE,

    FOREIGN KEY (book_id)
        REFERENCES books(book_id),

    FOREIGN KEY (student_id)
        REFERENCES students(student_id),

    FOREIGN KEY (librarian_id)
        REFERENCES librarians(librarian_id)
);