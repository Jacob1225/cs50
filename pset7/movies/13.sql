SELECT people.name
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE movies.title IN (SELECT title
                       FROM people
                       JOIN stars ON stars.person_id = people.id
                       JOIN movies ON stars.movie_id = movies.id
                       WHERE people.name = "Kevin Bacon" AND people.birth = 1958
                       ) AND people.name != "Kevin Bacon"
GROUP BY name