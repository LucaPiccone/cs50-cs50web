-- Keep a log of any SQL queries you execute as you solve the mystery.

-- View all the tables I am working with.
.tables

-- View all the columns in crime scene reports
.schema crime_screne_reports

-- Find all the crime scene reports on july 28 2021 at Humphrey Street.
SELECT * FROM crime_scene_reports WHERE month = 28 AND day = 28 AND year = 2021 AND street = "Humphrey Street";

--
--  Theft of cs50 duct took place at 10:15 am at humphrey street bakery.
--  Interviews were conducted with three people present at the time.
--  Each interview mentions the bakery
--  Humphrey street - Littering took place at 16:36 no known witnesses.

-- Query interviews next
SELECT * FROM interviews WHERE month = 7 AND day = 28 AND year = 2021;

-- RUTH - "Sometime within ten minutes of the theft, I saw the theif get into a car in the bakery parking lot and drive away. If you have
--         security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame"

-- RAYMOND "As the theif was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the theif say
--         "That they were planning to take the earliest flight out of fiftyville tomorrow. The theif then asked the person on the other end of the phone
--         "To purchase the flight ticket.

-- EMMA    "I'm the bakery owner, and someone came in, suspciously whispering into a phone for about half an hour. They never bought anything.

-- EUGENE   "I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking
--          "by the ATM on leggett Street and saw the their there withdrawing some money.


-- INVESTIGATE RUTH'S INTERVIEW
    .tables

 -- Query bakery_security_logs.
.schema bakery_security_logs

-- FIND LICENSE PLATE OF CARS LEAVING THE BAKERY PARKING LOT 10 MIN AFTER THE THEFT.
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 14 AND minute < 26;


-- INVESTIGATE RAYMOND'S INTERVIEW
.tables

-- Query phone_calls
.schema phone_calls

-- FIND THE CALLER AND RECIEVER OF PHONE CALLS LASTING LESS THAN 60 SECONDS ON THE DAY OF THE THEFT
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28;
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- FIND THE EARLIES FLIGHT OUT OF FIFTYVILLE
SELECT * FROM airports WHERE city = "Fiftyville";
SELECT * FROM flights WHERE day = 29 AND year = 2021 AND month = 7 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville");
SELECT * FROM flights WHERE day = 29 AND year = 2021 and month = 7 and hour = 8 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville");

-- THE DESTINATION OF THE FLIGHT
SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE day = 29 AND month = 7 AND year = 2021 AND hour = 8 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville"));
-- +----+--------------+-------------------+---------------+
-- | id | abbreviation |     full_name     |     city      |
-- +----+--------------+-------------------+---------------+
-- | 4  | LGA          | LaGuardia Airport | New York City |
-- +----+--------------+-------------------+---------------+
SELECT * FROM flights WHERE day = 29 AND year = 2021 AND month = 7 AND hour = 8 AND origin_airport_id = 8 AND destination_airport_id = 4;

-- THE PASSENGERS ON THE EARLIEST FLIGHT OUT OF FIFTYVILLE ON THE DAY AFTER THE THEFT
SELECT * FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE day = 29 AND year = 2021 AND month = 7 AND hour = 8 AND origin_airport_id = 8 AND destination_airport_id = 4);


-- INVESTIGATE EUGENE'S INTERVIEW
.tables
-- QUERY ATM TRANSACTIONS
.schema atm_transactions

-- FIND THE PEOPLE WHO WITHDREW MONEY FROM THE ATM ON LEGGETT STREET THE DAY OF THE THEFT
SELECT * FROM atm_transactions WHERE year = 2021 AND transaction_type="withdraw" month = 7 AND day = 28 AND atm_location = "Leggett Street";


-- INVESTIGATE tables
.tables

-- QUERY bank_accounts
.schema bank_accounts

SELECT * FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE transaction_type = "withdraw" AND year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street");


-- INVESTIGATE schemas
.schema

-- FIND THE PEOPLE WHO FIT THE DESCRIPTIONS ABOVE.
.schema people

-- FIND the people who withdrew FROM THE atm.
SELECT * FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street"));
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449       |
-- +--------+---------+----------------+-----------------+---------------+

-- FIND THE PEOPLE WHO WITHDREW THE FROM THE ATM AND LEFT THE PARKING LOT
SELECT * FROM PEOPLE where id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street")) AND license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 14 AND minute < 26);
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+

-- FIND THE PEOPLE WHO WITHDREW FROM THE ATM, LEFT THE PARKING LOT AND MADE A PHONE CALL ON THE DAY OF THE THEFT FOR LESS THAN 60 SECONDS
SELECT * FROM PEOPLE where id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street")) AND license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 14 AND minute < 26) AND phone_number in (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+

-- FIND THE PEOPLE WHO WITHDREW FROM THE ATM, LEFT THE PARKING LOT, MADE A PHONE CALL ON THE DAY OF THE THEFT FOR LESS THAN 60 SECONDS and took the earliest flight out of fiftyville to LaGuardia
SELECT * FROM PEOPLE where id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street")) AND license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 14 AND minute < 26) AND phone_number in (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE day = 29 AND year = 2021 AND month = 7 AND hour = 8 AND origin_airport_id = 8 AND destination_airport_id = 4));
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+

-- BRUCE STOLE THE DUCK
-- WHO RECIEVED THE PHONE CALL FROM BRUCE ON THE DAY OF THE ROBBERY
SELECT * FROM people where phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = "Bruce"));
-- ROBIN HELPED