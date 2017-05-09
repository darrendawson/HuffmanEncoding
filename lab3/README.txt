Darren Dawson, dwdawson@ucsc.edu
CMPS 12M, lab 3: dbgLab



Why was the segmentation fualt occuring?
-----------------------------------------
 - When findDistance() is called, it gets passed pointers to two cartesianCoordinate structs.
	It dereferences these pointers to get the appropriate X and Y coordinates so it can do the math.
	However, when it is called in the code, the pointers to firstPoint and secondPoint are 0. 
	You cannot have a pointer to memory address 0, so when the program tries to dereference it, a segfault occurs.

 - But why where the pointers for firstPoint and secondPoint pointing to nothing?
	Originally, the pointers for firstPoint/secondPoint where being created by function makePoint().
	makePoint() was supposed to declare the cartesianCoordinate, assign it values, and pass back the proper pointer to it.
	
	After doing some debugging, it was clear that while the function was properly assigning values to X and Y, it was doing so on
	a local variable cartesianCoordinate. Because it was in a local variable inside makePoint(), the variable cannot be accessed outside
	of that function. As a result, passing back a pointer to a local variable is useless: the "memory" it points to is on the stack,
	not in addressable memory. Thus, the line

		firstPoint = makePoint(x, y)

	will always return 0 (the pointer is addressing something that doesn't exist anymore). 

 - As a result, findDistance(firstPoint, secondPoint) will try to dereference something it shouldn't -> segfault



How did you fix it?
-------------------
 - The root problem was that firstPoint and secondPoint were never allocated proper memory. These pointers were allowed to be created locally
	I fixed this by using calloc to create firstPoint and secondPoint in memory before assigning X and Y values to them.
	I added the calloc step after the declaration step and before calling makePoint.

 - As a result, I changed makePoint to be a void function and gave it an extra argument of a cartesianCoordinate pointer.
	
		void makePoint(struct cartesianCoordinate* point, int x, int y)

	The function doesn't return anything and would dereference a point that actually exists in memory. 
	As a result, after calling makePoint(), the values assigned to the new point persist and the pointer exists.
	This way, when you call findDistance(), it can actually dereference the pointers, get the proper coordinates, and do the math.


Does it work now?
-----------------
 - Yes.

 - output: Distance Between Points: 2.24


Thank you for looking at my lab!
