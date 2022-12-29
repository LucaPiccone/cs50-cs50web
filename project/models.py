# CREATE DATABASE lcpecommerce

# CREATE TABLE users(
#     id serial PRIMARY KEY,
#     fname VARCHAR(255) NOT NULL, 
#     lname VARCHAR(255) NOT NULL,
#     email VARCHAR(255) NOT NULL, 
#     password VARCHAR(255) NOT NULL, 
#     confirmation_token VARCHAR(255) DEFAULT 1 NOT NULL, 
#     country VARCHAR(255),
#     province_state VARCHAR(255),
#     city VARCHAR(255),
#     postal_zip VARCHAR(50),
#     street_name VARCHAR(255),
#     street_number VARCHAR(20), 
#     APT_NUMBER VARCHAR(20),
#     PHONE_NUMBER VARCHAR(60),
#     date TIMESTAMP
# );

# CREATE TABLE products(
#     id SERIAL, 
#     admin_id INT,
#     name VARCHAR(255) NOT NULL,
#     image VARCHAR(255),
#     brand VARCHAR(255),
#     category VARCHAR(255),
#     description VARCHAR(255),
#     date TIMESTAMP,
#     PRIMARY KEY(id),
#     FOREIGN KEY(admin_id) REFERENCES admins(id)
# );

# CREATE TABLE admins (
#     id serial PRIMARY KEY,
#     fname VARCHAR(255) NOT NULL, 
#     lname VARCHAR(255) NOT NULL,
#     email VARCHAR(255) NOT NULL, 
#     password VARCHAR(255) NOT NULL, 
#     confirmation_token VARCHAR(255) DEFAULT 1 NOT NULL, 
#     country VARCHAR(255),
#     province_state VARCHAR(255),
#     city VARCHAR(255),
#     postal_zip VARCHAR(50),
#     street_name VARCHAR(255),
#     street_number VARCHAR(20), 
#     APT_NUMBER VARCHAR(20),
#     PHONE_NUMBER VARCHAR(60),
#     date TIMESTAMP 
# );

# CREATE TABLE transactions (

# );