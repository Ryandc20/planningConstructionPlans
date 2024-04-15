(define (problem 1)
	(:domain cubeworld)

	(:objects 
		p0_0_0 p0_0_1 p0_0_2 p0_0_3  - position
		p0_1_0 p0_1_1 p0_1_2 p0_1_3  - position
		p0_2_0 p0_2_1 p0_2_2 p0_2_3  - position
		p0_3_0 p0_3_1 p0_3_2 p0_3_3  - position
		p1_0_0 p1_0_1 p1_0_2 p1_0_3  - position
		p1_1_0 p1_1_1 p1_1_2 p1_1_3  - position
		p1_2_0 p1_2_1 p1_2_2 p1_2_3  - position
		p1_3_0 p1_3_1 p1_3_2 p1_3_3  - position
		p2_0_0 p2_0_1 p2_0_2 p2_0_3  - position
		p2_1_0 p2_1_1 p2_1_2 p2_1_3  - position
		p2_2_0 p2_2_1 p2_2_2 p2_2_3  - position
		p2_3_0 p2_3_1 p2_3_2 p2_3_3  - position
		p3_0_0 p3_0_1 p3_0_2 p3_0_3  - position
		p3_1_0 p3_1_1 p3_1_2 p3_1_3  - position
		p3_2_0 p3_2_1 p3_2_2 p3_2_3  - position
		p3_3_0 p3_3_1 p3_3_2 p3_3_3  - position
	)

	(:init
		(at-agent p0_3_3)
    (column p0_0_0 )
    (column p0_3_0 )
    (column p0_0_1 )
    (column p0_3_1 )
    (column p0_0_2 )
    (column p0_3_2 )
    (column p3_0_0 )
    (column p3_3_0 )
    (column p3_0_1 )
    (column p3_3_1 )
    (column p3_0_2 )
    (column p3_3_2 )
		(on-floor p0_0_0)
		(on-floor p0_1_0)
		(on-floor p0_2_0)
		(on-floor p0_3_0)
		(on-floor p1_0_0)
		(on-floor p1_1_0)
		(on-floor p1_2_0)
		(on-floor p1_3_0)
		(on-floor p2_0_0)
		(on-floor p2_1_0)
		(on-floor p2_2_0)
		(on-floor p2_3_0)
		(on-floor p3_0_0)
		(on-floor p3_1_0)
		(on-floor p3_2_0)
		(on-floor p3_3_0)
		(adjacent p0_0_0 p1_0_0)
		(adjacent p0_0_0 p0_1_0)
		(adjacent p0_0_0 p0_0_1)
		(adjacent p0_0_1 p1_0_1)
		(adjacent p0_0_1 p0_1_1)
		(adjacent p0_0_1 p0_0_0)
		(adjacent p0_0_1 p0_0_2)
		(adjacent p0_0_2 p1_0_2)
		(adjacent p0_0_2 p0_1_2)
		(adjacent p0_0_2 p0_0_1)
		(adjacent p0_0_2 p0_0_3)
		(adjacent p0_0_3 p1_0_3)
		(adjacent p0_0_3 p0_1_3)
		(adjacent p0_0_3 p0_0_2)
		(adjacent p0_1_0 p1_1_0)
		(adjacent p0_1_0 p0_0_0)
		(adjacent p0_1_0 p0_2_0)
		(adjacent p0_1_0 p0_1_1)
		(adjacent p0_1_1 p1_1_1)
		(adjacent p0_1_1 p0_0_1)
		(adjacent p0_1_1 p0_2_1)
		(adjacent p0_1_1 p0_1_0)
		(adjacent p0_1_1 p0_1_2)
		(adjacent p0_1_2 p1_1_2)
		(adjacent p0_1_2 p0_0_2)
		(adjacent p0_1_2 p0_2_2)
		(adjacent p0_1_2 p0_1_1)
		(adjacent p0_1_2 p0_1_3)
		(adjacent p0_1_3 p1_1_3)
		(adjacent p0_1_3 p0_0_3)
		(adjacent p0_1_3 p0_2_3)
		(adjacent p0_1_3 p0_1_2)
		(adjacent p0_2_0 p1_2_0)
		(adjacent p0_2_0 p0_1_0)
		(adjacent p0_2_0 p0_3_0)
		(adjacent p0_2_0 p0_2_1)
		(adjacent p0_2_1 p1_2_1)
		(adjacent p0_2_1 p0_1_1)
		(adjacent p0_2_1 p0_3_1)
		(adjacent p0_2_1 p0_2_0)
		(adjacent p0_2_1 p0_2_2)
		(adjacent p0_2_2 p1_2_2)
		(adjacent p0_2_2 p0_1_2)
		(adjacent p0_2_2 p0_3_2)
		(adjacent p0_2_2 p0_2_1)
		(adjacent p0_2_2 p0_2_3)
		(adjacent p0_2_3 p1_2_3)
		(adjacent p0_2_3 p0_1_3)
		(adjacent p0_2_3 p0_3_3)
		(adjacent p0_2_3 p0_2_2)
		(adjacent p0_3_0 p1_3_0)
		(adjacent p0_3_0 p0_2_0)
		(adjacent p0_3_0 p0_3_1)
		(adjacent p0_3_1 p1_3_1)
		(adjacent p0_3_1 p0_2_1)
		(adjacent p0_3_1 p0_3_0)
		(adjacent p0_3_1 p0_3_2)
		(adjacent p0_3_2 p1_3_2)
		(adjacent p0_3_2 p0_2_2)
		(adjacent p0_3_2 p0_3_1)
		(adjacent p0_3_2 p0_3_3)
		(adjacent p0_3_3 p1_3_3)
		(adjacent p0_3_3 p0_2_3)
		(adjacent p0_3_3 p0_3_2)
		(adjacent p1_0_0 p0_0_0)
		(adjacent p1_0_0 p2_0_0)
		(adjacent p1_0_0 p1_1_0)
		(adjacent p1_0_0 p1_0_1)
		(adjacent p1_0_1 p0_0_1)
		(adjacent p1_0_1 p2_0_1)
		(adjacent p1_0_1 p1_1_1)
		(adjacent p1_0_1 p1_0_0)
		(adjacent p1_0_1 p1_0_2)
		(adjacent p1_0_2 p0_0_2)
		(adjacent p1_0_2 p2_0_2)
		(adjacent p1_0_2 p1_1_2)
		(adjacent p1_0_2 p1_0_1)
		(adjacent p1_0_2 p1_0_3)
		(adjacent p1_0_3 p0_0_3)
		(adjacent p1_0_3 p2_0_3)
		(adjacent p1_0_3 p1_1_3)
		(adjacent p1_0_3 p1_0_2)
		(adjacent p1_1_0 p0_1_0)
		(adjacent p1_1_0 p2_1_0)
		(adjacent p1_1_0 p1_0_0)
		(adjacent p1_1_0 p1_2_0)
		(adjacent p1_1_0 p1_1_1)
		(adjacent p1_1_1 p0_1_1)
		(adjacent p1_1_1 p2_1_1)
		(adjacent p1_1_1 p1_0_1)
		(adjacent p1_1_1 p1_2_1)
		(adjacent p1_1_1 p1_1_0)
		(adjacent p1_1_1 p1_1_2)
		(adjacent p1_1_2 p0_1_2)
		(adjacent p1_1_2 p2_1_2)
		(adjacent p1_1_2 p1_0_2)
		(adjacent p1_1_2 p1_2_2)
		(adjacent p1_1_2 p1_1_1)
		(adjacent p1_1_2 p1_1_3)
		(adjacent p1_1_3 p0_1_3)
		(adjacent p1_1_3 p2_1_3)
		(adjacent p1_1_3 p1_0_3)
		(adjacent p1_1_3 p1_2_3)
		(adjacent p1_1_3 p1_1_2)
		(adjacent p1_2_0 p0_2_0)
		(adjacent p1_2_0 p2_2_0)
		(adjacent p1_2_0 p1_1_0)
		(adjacent p1_2_0 p1_3_0)
		(adjacent p1_2_0 p1_2_1)
		(adjacent p1_2_1 p0_2_1)
		(adjacent p1_2_1 p2_2_1)
		(adjacent p1_2_1 p1_1_1)
		(adjacent p1_2_1 p1_3_1)
		(adjacent p1_2_1 p1_2_0)
		(adjacent p1_2_1 p1_2_2)
		(adjacent p1_2_2 p0_2_2)
		(adjacent p1_2_2 p2_2_2)
		(adjacent p1_2_2 p1_1_2)
		(adjacent p1_2_2 p1_3_2)
		(adjacent p1_2_2 p1_2_1)
		(adjacent p1_2_2 p1_2_3)
		(adjacent p1_2_3 p0_2_3)
		(adjacent p1_2_3 p2_2_3)
		(adjacent p1_2_3 p1_1_3)
		(adjacent p1_2_3 p1_3_3)
		(adjacent p1_2_3 p1_2_2)
		(adjacent p1_3_0 p0_3_0)
		(adjacent p1_3_0 p2_3_0)
		(adjacent p1_3_0 p1_2_0)
		(adjacent p1_3_0 p1_3_1)
		(adjacent p1_3_1 p0_3_1)
		(adjacent p1_3_1 p2_3_1)
		(adjacent p1_3_1 p1_2_1)
		(adjacent p1_3_1 p1_3_0)
		(adjacent p1_3_1 p1_3_2)
		(adjacent p1_3_2 p0_3_2)
		(adjacent p1_3_2 p2_3_2)
		(adjacent p1_3_2 p1_2_2)
		(adjacent p1_3_2 p1_3_1)
		(adjacent p1_3_2 p1_3_3)
		(adjacent p1_3_3 p0_3_3)
		(adjacent p1_3_3 p2_3_3)
		(adjacent p1_3_3 p1_2_3)
		(adjacent p1_3_3 p1_3_2)
		(adjacent p2_0_0 p1_0_0)
		(adjacent p2_0_0 p3_0_0)
		(adjacent p2_0_0 p2_1_0)
		(adjacent p2_0_0 p2_0_1)
		(adjacent p2_0_1 p1_0_1)
		(adjacent p2_0_1 p3_0_1)
		(adjacent p2_0_1 p2_1_1)
		(adjacent p2_0_1 p2_0_0)
		(adjacent p2_0_1 p2_0_2)
		(adjacent p2_0_2 p1_0_2)
		(adjacent p2_0_2 p3_0_2)
		(adjacent p2_0_2 p2_1_2)
		(adjacent p2_0_2 p2_0_1)
		(adjacent p2_0_2 p2_0_3)
		(adjacent p2_0_3 p1_0_3)
		(adjacent p2_0_3 p3_0_3)
		(adjacent p2_0_3 p2_1_3)
		(adjacent p2_0_3 p2_0_2)
		(adjacent p2_1_0 p1_1_0)
		(adjacent p2_1_0 p3_1_0)
		(adjacent p2_1_0 p2_0_0)
		(adjacent p2_1_0 p2_2_0)
		(adjacent p2_1_0 p2_1_1)
		(adjacent p2_1_1 p1_1_1)
		(adjacent p2_1_1 p3_1_1)
		(adjacent p2_1_1 p2_0_1)
		(adjacent p2_1_1 p2_2_1)
		(adjacent p2_1_1 p2_1_0)
		(adjacent p2_1_1 p2_1_2)
		(adjacent p2_1_2 p1_1_2)
		(adjacent p2_1_2 p3_1_2)
		(adjacent p2_1_2 p2_0_2)
		(adjacent p2_1_2 p2_2_2)
		(adjacent p2_1_2 p2_1_1)
		(adjacent p2_1_2 p2_1_3)
		(adjacent p2_1_3 p1_1_3)
		(adjacent p2_1_3 p3_1_3)
		(adjacent p2_1_3 p2_0_3)
		(adjacent p2_1_3 p2_2_3)
		(adjacent p2_1_3 p2_1_2)
		(adjacent p2_2_0 p1_2_0)
		(adjacent p2_2_0 p3_2_0)
		(adjacent p2_2_0 p2_1_0)
		(adjacent p2_2_0 p2_3_0)
		(adjacent p2_2_0 p2_2_1)
		(adjacent p2_2_1 p1_2_1)
		(adjacent p2_2_1 p3_2_1)
		(adjacent p2_2_1 p2_1_1)
		(adjacent p2_2_1 p2_3_1)
		(adjacent p2_2_1 p2_2_0)
		(adjacent p2_2_1 p2_2_2)
		(adjacent p2_2_2 p1_2_2)
		(adjacent p2_2_2 p3_2_2)
		(adjacent p2_2_2 p2_1_2)
		(adjacent p2_2_2 p2_3_2)
		(adjacent p2_2_2 p2_2_1)
		(adjacent p2_2_2 p2_2_3)
		(adjacent p2_2_3 p1_2_3)
		(adjacent p2_2_3 p3_2_3)
		(adjacent p2_2_3 p2_1_3)
		(adjacent p2_2_3 p2_3_3)
		(adjacent p2_2_3 p2_2_2)
		(adjacent p2_3_0 p1_3_0)
		(adjacent p2_3_0 p3_3_0)
		(adjacent p2_3_0 p2_2_0)
		(adjacent p2_3_0 p2_3_1)
		(adjacent p2_3_1 p1_3_1)
		(adjacent p2_3_1 p3_3_1)
		(adjacent p2_3_1 p2_2_1)
		(adjacent p2_3_1 p2_3_0)
		(adjacent p2_3_1 p2_3_2)
		(adjacent p2_3_2 p1_3_2)
		(adjacent p2_3_2 p3_3_2)
		(adjacent p2_3_2 p2_2_2)
		(adjacent p2_3_2 p2_3_1)
		(adjacent p2_3_2 p2_3_3)
		(adjacent p2_3_3 p1_3_3)
		(adjacent p2_3_3 p3_3_3)
		(adjacent p2_3_3 p2_2_3)
		(adjacent p2_3_3 p2_3_2)
		(adjacent p3_0_0 p2_0_0)
		(adjacent p3_0_0 p3_1_0)
		(adjacent p3_0_0 p3_0_1)
		(adjacent p3_0_1 p2_0_1)
		(adjacent p3_0_1 p3_1_1)
		(adjacent p3_0_1 p3_0_0)
		(adjacent p3_0_1 p3_0_2)
		(adjacent p3_0_2 p2_0_2)
		(adjacent p3_0_2 p3_1_2)
		(adjacent p3_0_2 p3_0_1)
		(adjacent p3_0_2 p3_0_3)
		(adjacent p3_0_3 p2_0_3)
		(adjacent p3_0_3 p3_1_3)
		(adjacent p3_0_3 p3_0_2)
		(adjacent p3_1_0 p2_1_0)
		(adjacent p3_1_0 p3_0_0)
		(adjacent p3_1_0 p3_2_0)
		(adjacent p3_1_0 p3_1_1)
		(adjacent p3_1_1 p2_1_1)
		(adjacent p3_1_1 p3_0_1)
		(adjacent p3_1_1 p3_2_1)
		(adjacent p3_1_1 p3_1_0)
		(adjacent p3_1_1 p3_1_2)
		(adjacent p3_1_2 p2_1_2)
		(adjacent p3_1_2 p3_0_2)
		(adjacent p3_1_2 p3_2_2)
		(adjacent p3_1_2 p3_1_1)
		(adjacent p3_1_2 p3_1_3)
		(adjacent p3_1_3 p2_1_3)
		(adjacent p3_1_3 p3_0_3)
		(adjacent p3_1_3 p3_2_3)
		(adjacent p3_1_3 p3_1_2)
		(adjacent p3_2_0 p2_2_0)
		(adjacent p3_2_0 p3_1_0)
		(adjacent p3_2_0 p3_3_0)
		(adjacent p3_2_0 p3_2_1)
		(adjacent p3_2_1 p2_2_1)
		(adjacent p3_2_1 p3_1_1)
		(adjacent p3_2_1 p3_3_1)
		(adjacent p3_2_1 p3_2_0)
		(adjacent p3_2_1 p3_2_2)
		(adjacent p3_2_2 p2_2_2)
		(adjacent p3_2_2 p3_1_2)
		(adjacent p3_2_2 p3_3_2)
		(adjacent p3_2_2 p3_2_1)
		(adjacent p3_2_2 p3_2_3)
		(adjacent p3_2_3 p2_2_3)
		(adjacent p3_2_3 p3_1_3)
		(adjacent p3_2_3 p3_3_3)
		(adjacent p3_2_3 p3_2_2)
		(adjacent p3_3_0 p2_3_0)
		(adjacent p3_3_0 p3_2_0)
		(adjacent p3_3_0 p3_3_1)
		(adjacent p3_3_1 p2_3_1)
		(adjacent p3_3_1 p3_2_1)
		(adjacent p3_3_1 p3_3_0)
		(adjacent p3_3_1 p3_3_2)
		(adjacent p3_3_2 p2_3_2)
		(adjacent p3_3_2 p3_2_2)
		(adjacent p3_3_2 p3_3_1)
		(adjacent p3_3_2 p3_3_3)
		(adjacent p3_3_3 p2_3_3)
		(adjacent p3_3_3 p3_2_3)
		(adjacent p3_3_3 p3_3_2)
		(nbeam p0_0_3)
		(nbeam p0_1_3)
		(nbeam p0_2_3)
		(nbeam p0_3_3)
		(nbeam p1_0_3)
		(nbeam p1_3_3)
		(nbeam p2_0_3)
		(nbeam p2_3_3)
		(nbeam p3_0_3)
		(nbeam p3_1_3)
		(nbeam p3_2_3)
		(nbeam p3_3_3)
)
	(:goal
		(and
      (beam p0_0_3)
      (beam p0_1_3)
      (beam p0_2_3)
      (beam p0_3_3)
      (beam p1_0_3)
      (beam p1_3_3)
      (beam p2_0_3)
      (beam p2_3_3)
      (beam p3_0_3)
      (beam p3_1_3)
      (beam p3_2_3)
      (beam p3_3_3)
		)
	)
)
