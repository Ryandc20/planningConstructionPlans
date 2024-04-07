; Example implementation of a problem for the no scaffolding domain
(define (problem ex)
  (:domain cubeworld)

  (objects: p0_0_0, p0_0_1 )

  (init: 

  )

  ; Checks if all columns and beams are complete
  (goal: (and 
    (forall (?pos - position) 
      (or (and (nbeam ?pos) (beam ?pos)) (and (not (nbeam ?pos)) (not (beam ?pos))))
    )
    (columns-completed)
  ))
)
