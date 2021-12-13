SELECT movies.title, ratings.rating FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE year = "2010" AND ratings.votes > 1 ORDER BY ratings.rating desc, movies.title
