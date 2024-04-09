; A numeric version of the domain
; Numeric facts are defined by funcitons not predicates 
; If I want multiple numeric facts of the same type I need to have a type associated 
; to the function thus we can associate different objects to that type. Forall only depends on the type 
; so we will need the objects broken up
(define (domain cube-world)
  (:requirements :typing :fluents)
  (:types nrow ncol row col scaffold)
  ; Ok here is another issue how do I set certain locations to have scaffold or another block
  ; Here is where I think I need to have these interact with predicates


  (:functions
    ; Indicate the agent location
    (agent-x)
    (agent-y)
    (agent-z)

  )

  (:action move-forward
    :parameters (?a - agent)
    :preconditon () 
    :effect (increment (x))
  )
  
  (:action move-backward
    :parameters (?a - agent)
    :preconditon () 
    :effect (decrement (x))
  )

  (:action move-right
    :parameters (?a - agent)
    :preconditon () 
    :effect (increment (y))
  )
  
  (:action move-left
    :parameters (?a - agent)
    :preconditon () 
    :effect (decrement (y))
  )
  

  (:action move-up
    :parameters (?a - agent)
    :preconditon () 
    :effect (increment (z))
  )
  
  (:action move-down
    :parameters (?a - agent)
    :preconditon () 
    :effect (decrement (z)
  )
)
