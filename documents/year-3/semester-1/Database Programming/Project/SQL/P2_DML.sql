-- B. Data Manipulation (DML)

INSERT INTO Owner (owner_id, owner_name, phone_num, email, address) VALUES
(1, 'Alice Tan', '+6012-1234567', 'alice.tan@example.com', '1, Jalan Pahlawan, 81300 Skudai, Johor'),
(2, 'Bob Lee', '+6013-2345678', 'bob.lee@example.com', '2, Jalan Merdeka, 80100 Johor Bahru, Johor'),
(3, 'Charlie Lim', '+6014-3456789', 'charlie.lim@example.com', '3, Jalan Setia, 79100 Iskandar Puteri, Johor'),
(4, 'David Chen', '+6016-4567890', 'david.chen@example.com', '4, Jalan Indah, 81100 Masai, Johor'),
(5, 'Emily Yong', '+6017-5678901', 'emily.yong@example.com', '5, Jalan Harmoni, 81750 Plentong, Johor'),
(6, 'Faridah Hassan', '+6018-6789012', 'faridah.h@example.com', '6, Jalan Bestari, 81300 Skudai, Johor'),
(7, 'Ganesh Raj', '+6019-7890123', 'ganesh.raj@example.com', '7, Jalan Mutiara, 81100 Johor Bahru, Johor'),
(8, 'Helen Woo', '+6011-8901234', 'helen.woo@example.com', '8, Jalan Sasa, 81700 Pasir Gudang, Johor'),
(9, 'Idris bin Saleh', '+6010-9012345', 'idris.saleh@example.com', '9, Jalan Ceria, 81300 Skudai, Johor'),
(10, 'Jasmine Kaur', '+6015-0123456', 'jasmine.k@example.com', '10, Jalan Perwira, 80400 Johor Bahru, Johor');

INSERT INTO Vet (vet_id, vet_name, phone_num, email) VALUES
(1, 'Dr. Sarah Chen', '+6012-1112222', 'sarah.chen@gmail.com'),
(2, 'Dr. Kumar Moorthy', '+6012-3334444', 'kumar.moorthy@gmail.com'),
(3, 'Dr. Aisha Ibrahim', '+6012-5556666', 'aisha.ibrahim@gmail.com'),
(4, 'Dr. Benjamin Low', '+6012-7778888', 'ben.low@gmail.com'),
(5, 'Dr. Felicia Ong', '+6012-9990000', 'felicia.ong@gmail.com'),
(6, 'Dr. Michael Tan', '+6013-1112222', 'michael.tan@gmail.com'),
(7, 'Dr. Rachel Lim', '+6013-3334444', 'rachel.lim@gmail.com'),
(8, 'Dr. Samuel David', '+6013-5556666', 'samuel.david@gmail.com'),
(9, 'Dr. Siti Nurhaliza', '+6013-7778888', 'siti.nurhaliza@gmail.com'),
(10, 'Dr. Ivan Petrov', '+6013-9990000', 'ivan.petrov@gmail.com');

INSERT INTO Pet (pet_id, owner_id, pet_name, breed, species, birthdate, weight) VALUES
(1, 1, 'Max', 'Golden Retriever', 'Dog', '2020-05-10', 30.50),
(2, 1, 'Whiskers', 'Siamese', 'Cat', '2019-01-15', 4.20),
(3, 2, 'Buddy', 'Labrador', 'Dog', '2022-03-01', 28.00),
(4, 3, 'Fluffy', 'Persian', 'Cat', '2021-11-20', 3.80),
(5, 4, 'Rocky', 'German Shepherd', 'Dog', '2018-07-30', 35.10),
(6, 5, 'Mittens', 'Domestic Shorthair', 'Cat', '2023-01-05', 3.00),
(7, 5, 'Squeaky', 'Syrian', 'Rodent', '2024-02-14', 0.15),
(8, 6, 'Goldie', 'Goldfish', 'Fish', '2023-05-10', 0.05),
(9, 7, 'Charlie', 'Poodle', 'Dog', '2021-06-12', 12.50),
(10, 8, 'Shadow', 'Bombay', 'Cat', '2020-08-08', 4.50),
(11, 8, 'Tweety', 'Canary', 'Bird', '2022-12-01', 0.10),
(12, 9, 'Spike', 'Bulldog', 'Dog', '2019-10-10', 24.00),
(13, 10, 'Luna', 'Maine Coon', 'Cat', '2021-02-28', 6.80),
(14, 1, 'Bella', 'Beagle', 'Dog', '2023-04-15', 10.20),
(15, 2, 'Nibbles', 'Lop-eared', 'Rabbit', '2022-11-01', 2.10);

INSERT INTO Appointment (appointment_id, pet_id, vet_id, appointment_date, reason) VALUES
(1, 1, 1, '2024-12-05', 'Annual Vaccination'),
(2, 2, 2, '2024-12-18', 'Skin rash check'),
(3, 3, 3, '2025-01-10', 'Limping'),
(4, 4, 4, '2025-01-25', 'Dental check'),
(5, 1, 1, '2025-02-05', 'Follow-up on vaccination'),
(6, 5, 5, '2025-02-20', 'General checkup'),
(7, 7, 6, '2025-03-12', 'Not eating'),
(8, 9, 7, '2025-03-28', 'Coughing'),
(9, 10, 8, '2025-04-15', 'Checkup'),
(10, 12, 9, '2025-05-02', 'Breathing issue'),
(11, 13, 10, '2025-05-30', 'Grooming query'),
(12, 14, 1, '2025-06-15', 'First puppy shots'),
(13, 2, 2, '2025-07-01', 'Skin rash follow-up'),
(14, 6, 3, '2025-07-22', 'Spaying procedure query'),
(15, 3, 4, '2025-08-10', 'Limping follow-up'),
(16, 8, 5, '2025-09-05', 'Fungus on scales'),
(17, 11, 6, '2025-09-25', 'Beak trimming'),
(18, 15, 7, '2025-10-15', 'Nail clipping'),
(19, 5, 8, '2025-11-01', 'Senior dog checkup'),
(20, 1, 9, '2025-11-15', 'Eating grass');

INSERT INTO Medical_Record (record_id, pet_id, vet_id, record_date, diagnosis, treatment, note) VALUES
(1, 1, 1, '2024-12-05', 'N/A (Vaccination)', 'Administered DAPPv, Rabies vaccine.', 'Pet healthy. No issues.'),
(2, 2, 2, '2024-12-18', 'Allergic Dermatitis', 'Prescribed antihistamine, medicated shampoo.', 'Follow-up in 4 weeks if no improvement.'),
(3, 3, 3, '2025-01-10', 'Minor Sprain (Left Hind Leg)', 'Prescribed rest and anti-inflammatory meds.', 'Re-check if no improvement in 1 week.'),
(4, 4, 4, '2025-01-25', 'Mild Tartar Buildup', 'Dental cleaning procedure performed.', 'Advised owner on dental treats and daily brushing.'),
(5, 1, 1, '2025-02-05', 'Post-Vaccination Check', 'No adverse reactions noted from vaccine.', 'Pet is clear. Next vaccination due in 1 year.'),
(6, 5, 5, '2025-02-20', 'Healthy', 'Full blood panel normal. All clear.', 'Advised weight management; pet is slightly overweight.'),
(7, 7, 6, '2025-03-12', 'Dental Malocclusion', 'Trimmed overgrown incisors.', 'Owner advised on proper diet and chew toys.'),
(8, 9, 7, '2025-03-28', 'Kennel Cough (Mild)', 'Prescribed antibiotics and cough suppressant.', 'Quarantine from other dogs for 14 days.'),
(9, 10, 8, '2025-04-15', 'Healthy', 'Annual checkup, all clear.', 'N/A'),
(10, 12, 9, '2025-05-02', 'Brachycephalic Airway Syndrome', 'Discussed surgical options with owner.', 'Owner to consider options. Prescribed temporary steroids.'),
(11, 13, 10, '2025-05-30', 'Matted Fur', 'Medical grooming, removed severe mats.', 'Owner advised on regular brushing schedule.'),
(12, 14, 1, '2025-06-15', 'First Vaccination Series', 'Administered first DAPPv shot.', 'Booster due in 3 weeks.'),
(13, 2, 2, '2025-07-01', 'Dermatitis improving', 'Continued antihistamines.', 'Swelling reduced. Re-check if rash returns.'),
(14, 6, 3, '2025-07-22', 'Pre-Spay Consultation', 'Discussed procedure and risks.', 'Scheduled spaying for 2025-08-10.'),
(15, 3, 4, '2025-08-10', 'Sprain Healed', 'Pet no longer limping.', 'Cleared for normal activity.');

UPDATE Owner
SET address = 'Balai Polis, 81310 Skudai, Johor',
    phone_num = '+6012-3456789'
WHERE owner_id = 1 ;

UPDATE Pet
SET weight = 31.20
WHERE pet_id = 1 ;

DELETE FROM Medical_Record
WHERE record_id = 15 ;

DELETE FROM Appointment
WHERE appointment_id = 7 ;

DELETE FROM Medical_Record
WHERE pet_id = 8;

DELETE FROM Appointment
WHERE pet_id = 8;

DELETE FROM Pet
WHERE pet_id = 8;
