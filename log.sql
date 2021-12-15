.table
.schema crime_scene_reports

SELECT description FROM crime_scene_reports WHERE yar = 2020 AND day = 28 AND month = 7 AND street = "Chamberlin Street";

-- Each interviewee mentions the court house 

.table
.schema interviews

SELECT name, transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;
--Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse --parking lot, you might want to look for cars that left the parking lot in that time frame.
--Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw --the thief there withdrawing some money.
--Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take --the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

--RUTH 
.table
.schema courthouse_security_logs
SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND  day = 28 AND hour = 10 AND activity = "exit" AND minute <= 25 AND minute >= 15;

-- .schema

SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND  day = 28 AND hour = 10 AND activity = "exit" AND minute <= 25 AND minute >= 15);

-- Eugene
.table
.schema atm_transactions

SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";

-- .schema 

SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw");

-- .schmea

SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));


-- MIX RUTH AND EUGENES NAMES - 4 PEOPLE 
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw")) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND  day = 28 AND hour = 10 AND activity = "exit" AND minute <= 25 AND minute >= 15);


-- Raymond 
.table
.schema phone_calls

SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

-- 2 names 
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw")) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND  day = 28 AND hour = 10 AND activity = "exit" AND minute <= 25 AND minute >= 15) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);

SELECT passport_number FROM people where name IN ("Russell", "Ernest");

SELECT origin_airport_id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 and hour = 8;

-- earliest flight out of fiftyville was to london 
SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 and hour = 8);

-- id of the flight 
SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 and hour = 8;

SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 and hour = 8);

Ernest took the earliest flight out of fiftyville
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw")) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND  day = 28 AND hour = 10 AND activity = "exit" AND minute <= 25 AND minute >= 15) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 and hour = 8));


-- Berthold bought the flight ticket for ernest to escape 
SELECT phone_number FROM people WHERE name = "Ernest";
SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE name = "Ernest");
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE name = "Ernest"));