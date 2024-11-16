-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on July 28, 2023 and that it took place on Humphrey Street.

-- Find crime scene description:
SELECT * FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street = 'Humphrey Street';
-- Extracted info after checking the crime scene reports:
---- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
---- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

SELECT * FROM interviews
WHERE year = 2023
AND month = 7
AND day = 28;
-- By checking the interviews data from that day, we got this informations from witnesses:

--- Ruth: "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
---If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame."
                                                        |
--- Eugene: "I don't know the thief's name, but it was someone I recognized.
--- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money."

--- Raymond: "As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--- The thief then asked the person on the other end of the phone to purchase the flight ticket."

 SELECT * FROM people
 WHERE license_plate IN (
      SELECT license_plate
      FROM bakery_security_logs
      WHERE activity = "exit"
      AND year = 2023
      AND month = 7
      AND day = 28
      AND hour = 10
      AND minute BETWEEN 15 AND 30)
 AND phone_number IN (
      SELECT caller
      FROM phone_calls
      WHERE year = 2023
      AND month = 7
      AND day = 28 AND duration < 60)
 AND people.id IN (
      SELECT person_id
      FROM bank_accounts
      WHERE bank_accounts.account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE year = 2023
            AND month = 7
            AND day = 28
            AND atm_location = "Leggett Street"
            AND transaction_type = "withdraw"));
-- After checking the leads about the bakery parking and ATM withdrawal and the call, we get back 2 suspects:
--- Diana (770) 555-1861 and Bruce (367) 555-5533

SELECT * FROM people
WHERE phone_number IN (
     SELECT receiver
     FROM phone_calls
     WHERE year = 2023
     AND month = 7
     AND day = 28
     AND duration < 60
     AND caller IN ('(770) 555-1861', '(367) 555-5533'));

-- After checking the receivers of the phonecalls against two suspects phone numbers, we get two names that might be the accomplices:
--- Philip (725) 555-3243 and Robin (375) 555-8161

SELECT * FROM phone_calls
WHERE year = 2023
AND month = 7 AND day = 28
AND duration < 60 AND caller IN ('(770) 555-1861','(367) 555-5533')
    AND receiver IN ('(725) 555-3243', '(375) 555-8161');

-- Knowing the names of possible suspects and accomplices we can check who call who:
--- Bruce called Robin and Diana called Philip

SELECT * FROM flights
JOIN airports
ON airports.id = flights.origin_airport_id
WHERE flights.year = 2023
AND flights.month = 7
AND flights.day = 29
AND flights.hour
BETWEEN 00
AND 12
AND airports.city = "Fiftyville"
ORDER BY flights.hour, flights.minute;

-- After checking info that the thief said he wants to leave as early as possible tomorrow, checked all options before noon, we get back 3 flights with destination_airport_id 4,1,11

SELECT full_name, city
FROM airports
WHERE id IN (4, 1, 11);

-- Those 3 flights destinations are :
---- Chicago at 9:30 AM
---- New York City at 8:20 AM
---- San Francisco at 12:15 PM

SELECT name, passport_number
FROM people
WHERE people.name IN ('Bruce', 'Diana', 'Philip', 'Robin')
    AND passport_number IN (
    SELECT passport_number
    FROM passengers
    JOIN flights
    ON flights.id = passengers.flight_id
    JOIN airports
    ON airports.id = flights.origin_airport_id
    WHERE flights.year = 2023
    AND flights.month = 7
    AND flights.day = 29
    AND flights.hour
    BETWEEN 00
    AND 12
    AND flights.origin_airport_id IN (
        SELECT airports.id
        FROM airports
        WHERE airports.city = 'Fiftyville')
    AND flights.destination_airport_id IN (
        SELECT airports.id
        FROM airports
        WHERE airports.city
        IN ('New York City', 'Chicago', 'San Francisco')));

-- From the two suspects, Bruce flew on the 29th on one of three flights to 3 flights destinations, which make him a thief and because Bruce called Robin during a previous check, which implicates Robin as his accomplice.

-- Find the city the thief escaped to.
SELECT DISTINCT airports.city
FROM flights
JOIN airports
ON airports.id = (
     SELECT flights.destination_airport_id
     FROM people
     JOIN passengers
     ON people.passport_number = passengers.passport_number
     JOIN flights
     ON passengers.flight_id = flights.id
     WHERE flights.year = 2023
     AND flights.month = 7
     AND flights.day = 29
     AND people.name = 'Bruce');

-- The city Bruce escaped to is New York City.






