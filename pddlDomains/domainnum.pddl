; A numeric version of the domain

(define (domain cube-world)
  (:requirements :typing :fluents)
  (:types agent position)

  (:functions
    (agent-x ?a - agent) 
    (agent-y ?a - agent) 
    (agent-z ?a - agent)
  )

  (:predicates
    (at ?a - agent ?x ?y - numeric) ; agent is at cell (x, y)
  )

  (:action move-up
    :parameters (?a - agent)
    :precondition (and 
      (at ?a ?x ?y) ; agent is at current position
      (> ?y 0) ; agent is not at the top boundary
    )
    :effect (and 
      (increase (agent-y ?a) -1) ; agent moves up
    )
  )
  
  (:action move-down
    :parameters (?a - agent)
    :precondition (and 
      (at ?a ?x ?y) ; agent is at current position
      (< ?y 4) ; agent is not at the bottom boundary
    )
    :effect (and 
      (increase (agent-y ?a) 1) ; agent moves down
    )
  )
  
  (:action move-left
    :parameters (?a - agent)
    :precondition (and 
      (at ?a ?x ?y) ; agent is at current position
      (> ?x 0) ; agent is not at the left boundary
    )
    :effect (and 
      (increase (agent-x ?a) -1) ; agent moves left
    )
  )
  
  (:action move-right
    :parameters (?a - agent)
    :precondition (and 
      (at ?a ?x ?y) ; agent is at current position
      (< ?x 4) ; agent is not at the right boundary
    )
    :effect (and 
      (increase (agent-x ?a) 1) ; agent moves right
    )
  )
)
