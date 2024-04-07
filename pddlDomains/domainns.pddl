; The cube world domain but with no need for scaffold
(define (domain cubeworld)
  (:types
    position 
  )

  (:predicates
    ? Where the heck is are agent
    (at-agent ?pos - position) 
    ? Is the location on the floor 
    (on-floor ?pos - position)
    ; Do we need a column here ? 
    (ncolumn ?pos - position)
    ; Do we need a beam here ? 
    (nbeam ?pos -position)
    ; A column is here.
    (column ?pos - position)
    ;A beam is here.
    (beam ?pos - position)
    ; These positions are adjacent  
    (adjacent ?pos1 ?pos2 - position) 
    ; The columns have been completed and can start working on beams   
    (columns-completed)
  )

  (:action move-agent
    :parameters (?from ?to - position)
    ; Make sure the agent is trying to move to an adjacent position and that the position is not empty
    :precondition (and (at-agent ?from) (adjacent ?from ?to) (not (beam ?to)) (not (column ?to))) 
    :effect (and (not (at-agent ?from)) (at-agent ?to))
  )

  (:action place-column
    :parameters (?pos - position)
    :precondition (and (at-agent ?pos) (not (column ?pos)) 
      ; Make sure the column is either on a floor or there exits a adjacent block so it is not floating
      (or (on-floor ?pos) (exists (?pos1 - position) (and (column ?pos1)(adjacent ?pos ?pos1))))
      )
    :effect (column ?pos)
  )

   
  (:action place-beam
    :parameters (?pos - position)
    :precondition (and (at-agent ?pos) (columns-complete) 
      ; Make sure this location actually needs a beam 
      (ncolumn ?pos)
      ; Make sure there exists a adjacent position that contains a block and is not floating
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
