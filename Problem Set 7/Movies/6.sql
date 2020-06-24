SELECT AVG(rating) AS "Average rating for films released in 2012"
FROM ratings
WHERE movie_id 
IN (SELECT id FROM movies WHERE year="2012")