SELECT title, rating FROM movies, ratings WHERE id = movie_id and year = 2010 ORDER BY ratings.rating DESC, movies.title ASC