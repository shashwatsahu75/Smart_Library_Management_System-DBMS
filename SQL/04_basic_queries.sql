USE smart_library;

-- ==========================================
-- BASIC SQL QUERIES
-- ==========================================

-- 1. Display all students
SELECT *
FROM students;


-- 2. Display student names and emails
SELECT student_name, email
FROM students;


-- 3. Find Rahul Sharma
SELECT *
FROM students
WHERE student_name = 'Rahul Sharma';


-- 4. Find Computer Science students
SELECT *
FROM students
WHERE department = 'Computer Science';


-- 5. Find students whose name starts with R
SELECT *
FROM students
WHERE student_name LIKE 'R%';


-- 6. Display students in ascending order
SELECT *
FROM students
ORDER BY student_name ASC;


-- 7. Display students in descending order
SELECT *
FROM students
ORDER BY student_name DESC;


-- 8. Count total students
SELECT COUNT(*) AS total_students
FROM students;


-- 9. Display unique departments
SELECT DISTINCT department
FROM students;


-- 10. Find students whose email contains example.com
SELECT *
FROM students
WHERE email LIKE '%example.com';


-- 11. Display first 5 students
SELECT *
FROM students
LIMIT 5;