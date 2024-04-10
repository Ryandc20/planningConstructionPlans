(define (problem 1)
	(:domain cubeworld)

	(:objects 
		p0_0_0 p0_0_1 p0_0_2  - position
		p0_1_0 p0_1_1 p0_1_2  - position
		p0_2_0 p0_2_1 p0_2_2  - position
		p1_0_0 p1_0_1 p1_0_2  - position
		p1_1_0 p1_1_1 p1_1_2  - position
		p1_2_0 p1_2_1 p1_2_2  - position
		p2_0_0 p2_0_1 p2_0_2  - position
		p2_1_0 p2_1_1 p2_1_2  - position
		p2_2_0 p2_2_1 p2_2_2  - position
	)

	(:init
		(ncolumn p0_0_0)
)
	(:goal
		(and
      (column p0_0_0)
		)
	)
)
