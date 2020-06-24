SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name in ('Johnny Depp', 'Helena Bonham Carter')
GROUP BY title
HAVING COUNT(movies.id) > 1
/* Code referenced from Stack Overflow */