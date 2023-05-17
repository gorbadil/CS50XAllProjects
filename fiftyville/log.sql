-- Keep a log of any SQL queries you execute as you solve the mystery.

-- First Report
-- SELECT * FROM crime_scene_reports
-- WHERE street = 'Humphrey Street'
-- AND day = 28

-- Interview Reports
-- SELECT name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28

-- Security footage for car parking

-- Earlier morning at the ATM
-- SELECT account_number, transaction_type, amount FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2021 AND transaction_type = 'withdraw'

-- phone call for tomorrow earlier flight
-- SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021

-- SELECT name FROM people WHERE name = 'Eugene';
-- SELECT account_number, amount
--   FROM atm_transactions
--  WHERE year = 2021
--    AND month = 7
--    AND day = 28
--    AND atm_location = 'Leggett Street'
--    AND transaction_type = 'withdraw';"


-- SELECT name, atm_transactions.amount
--   FROM people
--   JOIN bank_accounts
--     ON people.id = bank_accounts.person_id
--   JOIN atm_transactions
--     ON bank_accounts.account_number = atm_transactions.account_number
--  WHERE atm_transactions.year = 2021
--    AND atm_transactions.month = 7
--    AND atm_transactions.day = 28
--    AND atm_transactions.atm_location = 'Leggett Street'
--    AND atm_transactions.transaction_type = 'withdraw';

-- SELECT flights.id, full_name, city, flights.hour, flights.minute
--   FROM airports
--   JOIN flights
--     ON airports.id = flights.destination_airport_id
--  WHERE flights.origin_airport_id =
--        (SELECT id
--           FROM airports
--          WHERE city = 'Fiftyville')
--    AND flights.year = 2021
--    AND flights.month = 7
--    AND flights.day = 29
--  ORDER BY flights.hour, flights.minute;

-- SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
--   FROM people
--   JOIN passengers
--     ON people.passport_number = passengers.passport_number
--   JOIN flights
--     ON passengers.flight_id = flights.id
--  WHERE flights.year = 2021
--    AND flights.month = 7
--    AND flights.day = 29
--    AND flights.hour = 8
--    AND flights.minute = 20
--  ORDER BY passengers.passport_number;

-- SELECT name, phone_calls.duration
--   FROM people
--   JOIN phone_calls
--     ON people.phone_number = phone_calls.caller
--  WHERE phone_calls.year = 2021
--    AND phone_calls.month = 7
--    AND phone_calls.day = 28
--    AND phone_calls.duration <= 60
--  ORDER BY phone_calls.duration;

-- SELECT name, phone_calls.duration
--   FROM people
--   JOIN phone_calls
--     ON people.phone_number = phone_calls.receiver
--  WHERE phone_calls.year = 2021
--    AND phone_calls.month = 7
--    AND phone_calls.day = 28
--    AND phone_calls.duration <= 60
--    ORDER BY phone_calls.duration;

SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
  FROM people
  JOIN bakery_security_logs
    ON people.license_plate = bakery_security_logs.license_plate
 WHERE bakery_security_logs.year = 2021
   AND bakery_security_logs.month = 7
   AND bakery_security_logs.day = 28
   AND bakery_security_logs.activity = 'exit'
   AND bakery_security_logs.hour = 10
   AND bakery_security_logs.minute >= 15
   AND bakery_security_logs.minute <= 25
 ORDER BY bakery_security_logs.minute;