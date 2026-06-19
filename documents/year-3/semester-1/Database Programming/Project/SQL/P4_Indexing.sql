-- D. Indexing and Optimization

-- BTREE Index
EXPLAIN SELECT * FROM appointment
WHERE appointment_date BETWEEN '2025-01-01' AND '2025-06-30';

CREATE INDEX idx_appt_date ON Appointment(appointment_date);

EXPLAIN SELECT * FROM appointment
WHERE appointment_date BETWEEN '2025-01-01' AND '2025-06-30';

-- FULLTEXT Index
EXPLAIN SELECT * FROM Medical_Record
WHERE diagnosis LIKE '%vaccination%' OR note LIKE '%vaccination%';

CREATE FULLTEXT INDEX idx_medical_text 
ON Medical_Record(diagnosis, treatment, note);

EXPLAIN SELECT * FROM Medical_Record
WHERE MATCH(diagnosis, treatment, note) AGAINST('vaccination');
