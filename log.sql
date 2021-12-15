-- Keep a log of any SQL queries you execute as you solve the mystery.
-- july 28, 2020 at the chamberlin street courthouse
.schema;
.tables;
.schema crime_scene_reports;
SELECT * FROM crime_scene_reports LIMIT 5;
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
-- Duck was taken at 10:15am from the courthouse. Interviews were conducted with three witnesses who were present at the time. Each interviewee mentioned the courthouse
.tables
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 7 and day = 28;
-- mentions liscense plates and time of entrance / exit
SELECT id, name, transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%";
-- Ruth - within 10 min the theft left courthouse
-- Eugene - Theif withdrew money from the ATM on fifer steet
-- Raymond - Planning to take flight the next day, partner bought tickets
SELECT id, license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
--id | license_plate
--260 | 5P2BI95
--261 | 94KL13X
--262 | 6P58WS2
--263 | 4328GD8
--264 | G412CB7
--265 | L93JTIZ
--266 | 322W7JE
--267 | 0NTHK55
.schema
.schema atm_transactions
SELECT id, account_number, transaction_type FROM atm_transactions limit 5;
SELECT id, account_number, atm_location, transaction_type FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "%fifer%" AND transaction_type = "withdraw";
--id | atm_location | account_number
--246 | Fifer Street | 28500762
--264 | Fifer Street | 28296815
--266 | Fifer Street | 76054385
--267 | Fifer Street | 49610011
--269 | Fifer Street | 16153065
--288 | Fifer Street | 25506511
--313 | Fifer Street | 81061156
--336 | Fifer Street | 26013199
SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "%fifer%" AND transaction_type = "withdraw";
SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "%fifer%" AND transaction_type = "withdraw");
.schema
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "%fifer%" AND transaction_type = "withdraw");

SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "%fifer%" AND transaction_type = "withdraw"));
-- The list of people who withdrew money from the atm on fifth street july 28, 2020

SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "%fifer%" AND transaction_type = "withdraw")) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
-- This is the list of people who withdrew money on fifth street on july 28 and left the court house 10 minutes after the duck was stolen.

.schema

SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29);

SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "%fifer%" AND transaction_type = "withdraw")) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29));

.schema

SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28;

SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "%fifer%" AND transaction_type = "withdraw")) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29)) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28);

SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28;

SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "%fifer%" AND transaction_type = "withdraw")) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29)) AND phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28);
-- Danielle and russel
-- phone_number = received and called on the same day of the robbery
-- passport_number = Were on a flight the day after the robbery
-- liscense plate = left the courthouse 10 min after the robbery
-- id = withdrew money from their bank account on the day of the robbery on fifer street.


SELECT * FROM people WHERE name IN ("Danielle", "Russell");
SELECT passport_number FROM people WHERE name IN ("Danielle", "Russell");

SELECT full_name from airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE origin_airport_id = 'Fiftyville Regional Airport' AND year = 2020 AND month = 7 AND day = 29 AND id IN (SELECT flight_id FROM passengers WHERE passport_number IN (SELECT passport_number FROM people WHERE name IN ("Danielle", "Russell"))));


-- Heathrow Airport
-- Logan International Airport