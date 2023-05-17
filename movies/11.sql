SELECT movies.title FROM movies, stars, ratings, people
WHERE movies.id = stars.movie_id
AND stars.person_id = people.id
AND ratings.movie_id = movies.id
AND people.name LIKE 'Chadwick Boseman'
LIMIT 5