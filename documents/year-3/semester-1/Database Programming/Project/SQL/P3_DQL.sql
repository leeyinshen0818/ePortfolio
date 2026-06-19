-- C. Data Retrieval (DQL/SELECT)

-- 1.Filtering
SELECT pet_id, pet_name, species, breed, weight
FROM pet
WHERE species = 'Dog' AND weight BETWEEN 27.00 AND 45.00;

-- 2.Sorting
SELECT pet_name, species, birthdate
FROM pet
ORDER BY birthdate LIMIT 8;

-- 3.Aggregation (+ Grouping)
SELECT species,
	COUNT(pet_id) AS Total,
    SUM(weight) AS Total_Weight,
	ROUND(AVG(weight), 2) AS Average_Weight,
    MIN(weight) AS Min_Weight,
	MAX(weight) AS Max_Weight
FROM pet
GROUP BY species;

-- 4.Grouping and filtering groups
SELECT vet_id,
	COUNT(appointment_id) AS Total_Appointments
FROM appointment
GROUP BY vet_id
HAVING COUNT(appointment_id) >2;

-- 5. Numeric and string functions
SELECT pet_id, pet_name,
	LENGTH(pet_name) AS Name_Length,
    species,
	CONCAT(UPPER(SUBSTR(species, 1, 3)),'-', pet_id) AS Pet_Code
FROM pet;

-- 6.Conditional logic (CASE WHEN).
SELECT pet_name, breed, weight,
	CASE 
		WHEN weight >= 45 THEN 'Giant'
        WHEN weight >= 27 THEN 'Large'
        WHEN weight >= 11 THEN 'Medium'
        ELSE 'Small'
	END AS Size
FROM pet
WHERE species = 'DOG';
        

-- 7. Subqueries
-- Single-row
SELECT pet_name
FROM pet
WHERE weight = (
	SELECT MAX(weight)
	 FROM pet
);     

-- multiple_row
SELECT owner_name
FROM owner
WHERE owner_id IN (
    SELECT owner_id
    FROM Pet
    WHERE species = 'Cat' AND weight >= 4
);

-- correlated at NOT EXISTS EXAMPLE

-- 8.Set Operation
-- UNION
SELECT owner_name AS Name, 'Owner' AS Role, phone_num, email
FROM owner
UNION (
	SELECT vet_name AS Vet_Name, 'Vet' AS Role, phone_num, email
	FROM vet)
ORDER BY Role;

-- NOT EXISTS (correlated)
SELECT p.pet_name, p.species
FROM pet p
WHERE NOT EXISTS(
	SELECT *
    FROM medical_record m
    WHERE m.pet_id = p.pet_id AND m.diagnosis = 'Healthy'
);

-- 9.Joins
SELECT a.appointment_date, v.vet_name, p.pet_name, o.owner_name, o.phone_num
FROM appointment a
INNER JOIN vet v ON v.vet_id = a.vet_id
INNER JOIN pet p ON p.pet_id = a.pet_id
INNER JOIN owner o ON p.owner_id = o.owner_id
WHERE a.appointment_date BETWEEN '2025-06-01' AND '2025-11-30'
ORDER BY a.appointment_date;

SELECT o.owner_name, p.pet_name, p.species, p.weight, m.diagnosis, m.record_date
FROM owner o
LEFT JOIN pet p ON p.owner_id = o.owner_id
LEFT JOIN medical_record m ON m.pet_id = p.pet_id
ORDER BY m.record_id;