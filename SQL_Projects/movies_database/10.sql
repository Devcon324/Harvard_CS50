--list the names of all people who have directed a movie that received a rating of at least 9.0.
SELECT DISTINCT name
FROM people
JOIN ratings ON ratings.movie_id = directors.movie_id
JOIN directors ON directors.person_id = people.id
WHERE rating >= 9.0;