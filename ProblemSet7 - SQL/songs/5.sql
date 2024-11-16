-- In 5.sql, write a SQL query that returns the average energy of all the songs.
-- Your query should output a table with a single column and a single row containing the average energy.
SELECT AVG(energy)
FROM songs;

-- SELECT ROUND(AVG(energy), 2) FROM songs;
