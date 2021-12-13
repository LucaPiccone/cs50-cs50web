sqlite> SELECT name FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id WHERE stars.person_id = (movies.id = (people.name = "Kevin Bacon"));
