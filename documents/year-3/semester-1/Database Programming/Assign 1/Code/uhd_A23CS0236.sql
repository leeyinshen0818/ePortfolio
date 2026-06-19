-- Name: LEE YIN SHEN
-- Matric no: A23CS0236
-- Task: Assignment 1
-- No Team Member

-- Task 1: Database Creation and Integrity Constraints (CLO1)

-- Create database ‘hostel_mgmt_lee’ using CREATE DATABASE
CREATE DATABASE IF NOT EXISTS hostel_mgmt_lee ;

-- Select database
USE hostel_mgmt_lee ;

-- Create table
-- Create table ‘room_types’ using CREATE TABLE, then set primary key as type_id.
CREATE TABLE IF NOT EXISTS room_types(
    type_id INT AUTO_INCREMENT,
    type_name VARCHAR(30) UNIQUE NOT NULL,
    rent DECIMAL(10, 2) NOT NULL,
    deposit DECIMAL(10, 2) NOT NULL,
    capacity INT NOT NULL,
    
    PRIMARY KEY(type_id)
);

-- Create table ‘rooms’ using CREATE TABLE, then set primary key as room_id, type_id as foreign key, reference to room_types table. 
CREATE TABLE IF NOT EXISTS rooms(
    room_id INT AUTO_INCREMENT,
    room_no VARCHAR(5) UNIQUE NOT NULL,
    floor_no INT NOT NULL,
    is_occupied BOOLEAN NOT NULL DEFAULT FALSE,
    type_id INT NOT NULL,

	PRIMARY KEY(room_id),
    CONSTRAINT fk_rooms_room_types FOREIGN KEY(type_id)
    REFERENCES room_types(type_id)
);

-- Create table ‘students’ using CREATE TABLE, then set primary key as student_id, foreign key as room_id, reference to rooms table. 
CREATE TABLE IF NOT EXISTS students(
    student_id INT AUTO_INCREMENT,
    fname VARCHAR(50) NOT NULL,
    lname VARCHAR(20) NOT NULL,
    status ENUM('ACTIVE', 'NON_ACTIVE') NOT NULL,
    checkin_date DATE,
    room_id INT NULL,
    
	PRIMARY KEY(student_id),
    CONSTRAINT fk_students_rooms FOREIGN KEY(room_id)
    REFERENCES rooms(room_id)
);

-- Create table ‘maintenance’ using CREATE TABLE, then set primary key as maint_id, foreign key as room_id, reference to rooms table.
CREATE TABLE IF NOT EXISTS maintenance(
    maint_id INT AUTO_INCREMENT,
    issue_desc TEXT NOT NULL,
    severity ENUM('LOW', 'MEDIUM', 'HIGH') NOT NULL,
    status ENUM('OPEN', 'RESOLVED') NOT NULL,
    reported_on DATE NOT NULL,
    resolved_on DATE NULL,
    room_id INT NOT NULL,
    
	PRIMARY KEY(maint_id),
    CONSTRAINT fk_maintenance_rooms FOREIGN KEY(room_id)
    REFERENCES rooms(room_id)
);

-- Create table ‘payments’ using CREATE TABLE, set primary key as payment_id, foreign key as student_id, reference to students table.
CREATE TABLE IF NOT EXISTS payments(
    payment_id INT AUTO_INCREMENT,
    amount DECIMAL(10, 2) NOT NULL,
    paid_on DATE NOT NULL,
    method ENUM('CASH', 'FPX', 'CARD', 'TNG') NOT NULL,
    note TEXT NULL,
	student_id INT NOT NULL,
    
    PRIMARY KEY(payment_id),
    CONSTRAINT fk_payments_students FOREiGN KEY(student_id)
    REFERENCES students(student_id)
);

-- Alter table

-- Add ‘email’ column into students table using ALTER TABLE, then set as Unique.
ALTER TABLE students
ADD COLUMN email VARCHAR(30) UNIQUE ;

-- Create a temporary testing table using CREATE TABLE, then drop it using DROP TABLE.
CREATE TABLE temp_test_table(
    temp_id INT PRIMARY KEY
);
DROP TABLE IF EXISTS temp_test_table ;


-- Task 2: Data Manipulation and Filtering (CLO2)

-- Insert data
-- Insert data into room_types table using INSERT INTO … VALUES
INSERT INTO room_types (type_name, rent, deposit, capacity) VALUES
('Single A', 450.00, 250.00, 1),
('Single B', 550.00, 300.00, 1),
('Single C', 650.00, 500.00, 1),
('Double A', 700.00, 400.00, 2),
('Double B', 850.00, 500.00, 2),
('Double C', 600.00, 350.00, 2),
('Premium A', 950.00, 500.00, 1),
('Premium B', 1200.00, 600.00, 2),
('Family A', 1600.00, 800.00, 4),
('Family B', 2000.00, 1300.00, 3) ;

-- Insert data into rooms table using INSERT INTO … VALUES
INSERT INTO rooms (room_no, floor_no, type_id) VALUES
('A101', 1, 1),
('A102', 1, 1),
('A103', 1, 1),
('B201', 2, 3),
('B202', 2, 3),
('B203', 2, 3),
('C301', 3, 5),
('C302', 3, 5),
('D401', 4, 7),
('D402', 4, 7);

-- Insert data into students table using INSERT INTO … VALUES
INSERT INTO students (fname, lname, status, checkin_date, room_id, email) VALUES
('Ahmad', 'Zaki', 'ACTIVE', '2025-10-01', 1, 'ahmad.zaki@graduate.utm.my'),
('Siti', 'Nurhaliza', 'ACTIVE', '2025-10-01', 2, 'siti.nurhaliza@graduate.utm.my'),
('Amin', 'Yusof', 'ACTIVE', '2025-10-02', 4, 'amin.yusof@graduate.utm.my'),
('Tan', 'Wei Ling', 'ACTIVE', '2025-10-02', 7, 'tan.weiling@graduate.utm.my'),
('Kumar', 'Rao', 'ACTIVE', '2025-10-03', 7, 'kumar.rao@graduate.utm.my'),
('David', 'Lim', 'ACTIVE', '2025-10-05', 8, 'david.lim@graduate.utm.my'),
('Chong', 'Ee Von', 'ACTIVE', '2025-10-05', 8, 'chong.eevon@graduate.utm.my'),
('Alice', 'Gomez', 'ACTIVE', '2025-10-06', 9, 'alice.gomez@graduate.utm.my'),
('Farah', 'Lee', 'ACTIVE', '2025-10-08', 10, 'farah.lee@graduate.utm.my'),
('Zainab', 'Ali', 'NON_ACTIVE', '2024-09-15', 3, 'zainab.ali@graduate.utm.my'),
('Michael', 'Tan', 'NON_ACTIVE', '2024-08-20', NULL, 'michael.tan@graduate.utm.my') ;

-- Insert data into maintenance table using INSERT INTO … VALUES
INSERT INTO maintenance (room_id, issue_desc, severity, status, reported_on, resolved_on) VALUES
(1, 'Water leakage in bathroom', 'MEDIUM', 'OPEN', '2025-10-10', NULL),
(2, 'Window latch broken', 'MEDIUM', 'RESOLVED', '2025-10-01', '2025-10-03'),
(4, 'Air-con not cooling', 'HIGH', 'OPEN', '2025-10-11', NULL),
(7, 'Study chair broken', 'LOW', 'RESOLVED', '2025-10-05', '2025-10-05'),
(8, 'Wifi slow', 'LOW', 'OPEN', '2025-10-12', NULL),
(9, 'Shower head leaking', 'LOW', 'OPEN', '2025-10-13', NULL),
(6, 'Keycard not working', 'HIGH', 'RESOLVED', '2025-10-07', '2025-10-07'),
(2, 'Bunk bed ladder loose', 'MEDIUM', 'OPEN', '2025-10-14', NULL),
(1, 'Sink clogged', 'LOW', 'OPEN', '2025-10-15', NULL) ; 

-- Insert data into payments table using INSERT INTO … VALUES
INSERT INTO payments (amount, paid_on, method, note, student_id) VALUES
(700.00, '2025-10-01', 'FPX', 'Deposit + Oct Rent', 1),
(700.00, '2025-10-01', 'CARD', 'Deposit + Oct Rent', 2),
(1150.00, '2025-10-02', 'FPX', 'Deposit + Oct Rent', 3),
(1250.00, '2025-10-02', 'TNG', 'Deposit + Oct Rent', 4),
(1350.00, '2025-10-03', 'CARD', 'Deposit + Oct Rent', 5),
(1350.00, '2025-10-05', 'FPX', 'Deposit + Oct Rent', 6),
(1350.00, '2025-10-05', 'CASH', 'Deposit + Oct Rent', 7),
(1450.00, '2025-10-06', 'FPX', 'Deposit + Oct Rent', 8),
(450.00, '2025-11-01', 'FPX', 'Nov Rent', 1),
(450.00, '2025-11-01', 'CARD', 'Nov Rent', 2);

-- update room
-- UPDATE 'is_occupied' to TRUE for rooms with active students using SET, if not set to FALSE. 
-- The condition filtering is done by using SELECT, FROM, WHERE. 
-- true
UPDATE rooms
SET is_occupied = TRUE
WHERE room_id IN (
    SELECT DISTINCT room_id
    FROM students
    WHERE status = 'ACTIVE' AND room_id IS NOT NULL
);
-- false
UPDATE rooms
SET is_occupied = FALSE
WHERE room_id NOT IN (
    SELECT DISTINCT room_id
    FROM students
    WHERE status = 'ACTIVE' AND room_id IS NOT NULL
);

-- Delete old maintenance records that older than 60 days using DELETE FROM. The condition filtering is done by WHERE … AND. I use < DATE_SUB(NOW(), INTERVAL 60 DAY) to identify whether the reported already resolved over 60 days or not.
DELETE FROM maintenance
WHERE status = 'RESOLVED' 
AND reported_on < DATE_SUB(NOW(), INTERVAL 60 DAY) ;

-- Filtering Query using SELECT, FROM, WHERE and BETWEEN
SELECT type_name, rent
FROM room_types
WHERE rent BETWEEN 400.00 AND 800.00 ;

-- Filtering Query using SELECT, FROM, WHERE and LIKE
SELECT fname, lname, status
FROM students
WHERE fname LIKE 'A%';

-- Filtering Query using SELECT, FROM, WHERE and IN
SELECT student_id, amount, paid_on, method
FROM payments
WHERE method IN ('FPX', 'CARD') ;

-- Filtering Query using SELECT, FROM, WHERE and combination of AND and OR
SELECT room_id, issue_desc, severity, status
FROM maintenance
WHERE status = 'OPEN' 
	AND (severity = 'HIGH' OR severity = 'MEDIUM') ;

-- Use aggregate function COUNT(*) to calculate total active students
SELECT COUNT(*) AS total_active_students
FROM students
WHERE status = 'ACTIVE' ;

-- Use string function CONCAT to combine student’s name
SELECT 
    CONCAT(fname, ' ', lname) AS full_name,
    status
FROM students ;

-- Use string function UPPER to show uppercase room type
SELECT 
    UPPER(type_name) AS room_type_uppercase,
    rent
FROM room_types ;



-- Task 3: Reporting and Aggregation (CLO2)
-- Create view 'v_room_status' using CREATE VIEW … AS. 
-- then use LEFT JOIN to join three tables which include room_types, students and maintenances to make sure all rooms included, even if they have no students and no issues. Then filter the joins to only count students who are 'ACTIVE' and issues that are 'OPEN'.
CREATE VIEW v_room_status AS
SELECT 
	r.room_no,
    rt.type_name,
    rt.rent,
    r.floor_no,
    rt.capacity,
	COUNT(DISTINCT s.student_id) AS n_occupants,
	COUNT(DISTINCT m.maint_id) AS pending_issues,
	CASE 
        WHEN COUNT(DISTINCT s.student_id) = 0 THEN TRUE
        ELSE FALSE
    END AS is_vacant
FROM rooms r

LEFT JOIN 
    room_types rt ON r.type_id = rt.type_id
LEFT JOIN 
    students s ON r.room_id = s.room_id AND s.status = 'ACTIVE'
LEFT JOIN 
    maintenance m ON r.room_id = m.room_id AND m.status = 'OPEN'
GROUP BY 
    r.room_no, rt.type_name, rt.rent, r.floor_no, rt.capacity ;

-- Use INNER JOIN to joins the room_types, rooms, and students tables together. 
-- Then filter to find only the 'ACTIVE' students, then GROUP BY room type to COUNT how many active students live in each room type.
SELECT 
    rt.type_name,
    COUNT(s.student_id) AS total_active_students
FROM 
    room_types rt
INNER JOIN 
    rooms r ON rt.type_id = r.type_id
INNER JOIN 
    students s ON r.room_id = s.room_id
WHERE 
    s.status = 'ACTIVE'
GROUP BY 
    rt.type_name ;

-- Use ROUND, AVG, and SUM on the room_types table. 
-- Then GROUP BY type_name to calculate the average rent and total deposit for each room type.
SELECT 
    type_name,
    ROUND(AVG(rent), 2) AS avr_rent,
    ROUND(SUM(deposit), 2) AS total_deposit
FROM 
    room_types
GROUP BY 
    type_name ;

-- Use YEAR, MONTH, and SUM on the payments table. 
-- Then GROUP BY both year and month to find the total payment for each period.
SELECT 
    YEAR(paid_on) AS payment_year,
    MONTH(paid_on) AS payment_month,
    SUM(amount) AS total_payments
FROM 
    payments
GROUP BY 
    YEAR(paid_on), MONTH(paid_on) ;


-- Use INNER JOIN to join rooms and maintenance tables. 
-- Then use WHERE to filter for 'OPEN' issues, then GROUP BY floor_no to COUNT the issues on each floor. Then use HAVING to show only floors with more than 2 issues.
SELECT 
    r.floor_no,
    COUNT(m.maint_id) AS oi_count
FROM 
    rooms r
INNER JOIN 
    maintenance m ON r.room_id = m.room_id
WHERE 
    m.status = 'OPEN'
GROUP BY 
    r.floor_no
HAVING 
    oi_count > 2 ;

-- SQL functions

-- Use ROUND, AVG and SUM function to show average rent and total deposit for each room type.
SELECT 
    type_name,
    ROUND(AVG(rent), 2) AS avr_rent,
    ROUND(SUM(deposit), 2) AS total_deposit
FROM 
    room_types
GROUP BY 
    type_name ;
    
-- Use UPPER to show uppercase full name.
SELECT 
    UPPER(fname) AS firs_upper,
    UPPER(lname) AS last_upper
FROM 
    students
WHERE 
    status = 'ACTIVE' ;

-- Use CONCAT to combine first and last name to show full name.
SELECT 
    CONCAT(fname, ' ', lname) AS full_name,
    email
FROM 
    students ;

-- Use CASE with conditions to create new column and assign the column with new label. 
SELECT 
    type_name,
    rent,
    CASE 
        WHEN rent < 600.00 THEN 'LOW'
        WHEN rent <= 900.00 THEN 'MEDIUM'
        ELSE 'HIGH'
    END AS rent_category
FROM 
    room_types
ORDER BY 
    rent ;