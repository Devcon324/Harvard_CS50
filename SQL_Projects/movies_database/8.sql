--list the names of all people who starred in Toy Story.
SELECT name
FROM people
JOIN movies ON movies.id = stars.movie_id
JOIN stars ON stars.person_id = people.id
WHERE title = "Toy Story";