; The cube world domain but with no need for scaffold
(define (domain cubeworld)
  (:requirements :strips :typing :quantified-preconditions )
  (:types position)

  (:predicates
    ; Where the heck is are agent
    (at-agent ?pos - position) 
    ; Is the location on the floor 
    (on-floor ?pos - position)
    ; Do we need a column here ? 
    (ncolumn ?pos - position)
    ; Do we need a beam here ? 
    (nbeam ?pos - position)
    ; A column is here.
    (column ?pos - position)
    ;A beam is here.
    (beam ?pos - position)
    ; These positions are adjacent  
    (adjacent ?pos1 ?pos2 - position) 
  )

  (:functions
    ; The current number of columns that exist
    (num-col)
    ; The total number of columns that need to be placed 
    (total-col)
    ; The current number of beams that exist
    (num-beam)
    ; The total number of beams that need to be placed
    (total-beam)
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
    :effect (and (column ?pos) (increase (num-col) 1))
  )

  (:action place-beam
    :parameters (?pos - position)
    :precondition (and 
      (at-agent ?pos) 
      ; Make sure this location actually needs a beam 
      (ncolumn ?pos)
      ; Make sure there exists a adjacent position that contains a block and is not floating
      (exists (?pos1 - position) (and (or (column ?pos1) (beam ?pos1)) (adjacent ?pos ?pos1)))

      ; Make sure that all columns have been placed
      (= (num-col) (total-col))
      )
    :effect (and (beam ?pos) (increase (num-beam) 1))
  )
)
