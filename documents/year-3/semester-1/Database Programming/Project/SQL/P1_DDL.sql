-- A. Database Creation (DDL)

CREATE DATABASE pet_hospital_system;

USE pet_hospital_system;

CREATE TABLE Owner (
	owner_id INT PRIMARY KEY,
    owner_name VARCHAR (255) NOT NULL,
    phone_num VARCHAR (255) UNIQUE,
    email VARCHAR (200) UNIQUE,
    address VARCHAR (255)
);

CREATE TABLE Pet (
	pet_id INT PRIMARY KEY,
    owner_id INT NOT NULL,
    pet_name VARCHAR (255) NOT NULL,
    breed VARCHAR (100) NOT NULL,
    species VARCHAR(50) NOT NULL,
    birthdate DATE,
    FOREIGN KEY (owner_id) REFERENCES Owner(owner_id)
);

CREATE TABLE Vet (
	vet_id INT PRIMARY KEY,
    vet_name VARCHAR (255) NOT NULL,
    phone_num VARCHAR (255) UNIQUE,
    email VARCHAR (200) UNIQUE
);

CREATE TABLE Appointment (
	appointment_id INT PRIMARY KEY,
    pet_id INT NOT NULL,
    vet_id INT NOT NULL,
    appointment_date DATE, 
    reason VARCHAR (255),
    FOREIGN KEY (pet_id) REFERENCES Pet(pet_id),
    FOREIGN KEY (vet_id) REFERENCES Vet(vet_id)
);

CREATE TABLE Medical_Record (
	record_id INT PRIMARY KEY,
    pet_id INT NOT NULL,
    vet_id INT NOT NULL,
    record_date DATE,
    diagnosis VARCHAR (255),
    treatment VARCHAR (255),
    note TEXT,
    FOREIGN KEY (pet_id) REFERENCES Pet(pet_id),
    FOREIGN KEY (vet_id) REFERENCES Vet(vet_id)
);

CREATE TABLE Pet_diseases_diagnos (
	diagnos_id INT PRIMARY KEY,
    type VARCHAR (255),
    reason_diagnos VARCHAR (255)
);


ALTER TABLE Pet 
ADD COLUMN weight DECIMAL (4,2);

DROP TABLE IF EXISTS Pet_diseases_diagnos;