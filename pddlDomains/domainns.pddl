; The cube world domain but with no need for scaffold
(define (domain cubeworld)
  (:types
    position 
  )

  (:predicates
    (at-agent ?pos - position) 
    (on-floor ?pos - position)
    (ncolumn ?pos - position)
    (nbeam ?pos -position)
    (column ?pos - position)
    (beam ?pos - position)
    (adjacent ?pos1 ?pos2 - position) 
    (columns-completed)
    (beams-finished)
  )

  (:action move-agent
    :parameters (?from ?to - position)
    :precondition (and (at-agent ?from) (adjacent ?from ?to) (not (beam ?to)) (not (column ?to))) 
    :effect (and (not (at-agent ?from)) (at-agent ?to))
  )

  (:action place-column
    :parameters (?pos - position)
    :precondition (and (at-agent ?pos) (not (column ?pos)) 
      (or (on-floor ?pos) (exists (?pos1 - position) (and (column ?pos1)(adjacent ?pos ?pos1))))
      )
    :effect (column ?pos)
  )

   
  (:action place-beam
    :parameters (?pos - position)
    :precondition (and (at-agent ?pos) (columns-complete) 
      (exists (?pos1 - position) (and (or (column ?pos1) (beam ?pos1)) (adjacent ?pos ?pos1)))
      )
    :effect (beam ?pos)
  )

  ; Sets the columns to be complete to allow beams to be placed
  (:action columns-complete
    :parameters ()
    :precondtion (forall (?pos - position) 
      (or (and (ncolumn ?pos) (column ?pos)) (and (not (ncolumn ?pos)) (not (column ?pos))))
      )
    :effect(columns-completed)
  )

)
