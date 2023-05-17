SELECT title FROM movies WHERE id IN (SELECT JMOV FROM (SELECT stars.movie_id as JMOV FROM stars WHERE stars.person_id = (
    SELECT people.id FROM people WHERE people.name = 'Johnny Depp'))
    WHERE JMOV IN (SELECT stars.movie_id as HMOV FROM stars WHERE stars.person_id =(
        SELECT id FROM people WHERE people.name = 'Helena Bonham Carter'
    )))