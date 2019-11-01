HOMEWORK 6: INVERSE WORD SEARCH


NAME:  Josephine Lyons


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Kyle Hackett, Zaire Wilson, John Farrell, Isaac Sibley, David May, cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  27


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?

My code, despite how ugly it works, seems to be running fast.  The order notation I got is:

O(r + f + w*h + r*w*h*((w*h)/l+l) + s*(r+f+s) + s)

The r + f comes from pushing back all of the good and bad words to their respective vector.
The w*h comes from the double for loop that makes the original empty grid.
The r*w*h*((w*h)/l+l) comes from making boards. In making boards there is a triple for loop of good words, rows, and columns.  That gets the r*w*h. The  ((w*h)/l+l) comes from what is inside that (which is why it is multiplied). The (w*h)/l comes from search for location, as it has a double for loop and recursion that decreases the time as the length of the word increases. The l comes from adding the word to the board and since they are on the same level, they are added together. 
The s*(r+f+s) comes from validating boards.  The first s comes from checking all of the current solutions.  The (r+f+s) comes from the three individual for loops within the function that go through all of the good words, bad words, and solution boards.
The s comes from the printing out of solutions.


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?
It seemed to run relatively quick (or at least quicker than I was expecting) on all of them. Ones that had "blank" spaces where any letter could go were slower than the rest. Also, bigger boards were slower than smaller boards usually.
Run times (all but the first are all_solutions):
	Puzzle 1: .032 seconds (one_solution) .025 seconds (all_solutions)
	Puzzle 2: .027 seconds
	Puzzle 3: .099 seconds
	Puzzle 4: .067 seconds
	Puzzle 5: .044 seconds
	Puzzle 6: .048 seconds
	Puzzle 7: .1 seconds
	Puzzle 8: 35.833 seconds (I did it a second time and got 36.079 seconds)
I made new test cases to check boundary conditions.
  -when more spaces than letters to fill grid (2x2 +to)
	Run time: 1.948 seconds
  -one word fills all (3x1 +cat)
	Run time: .028 seconds
  -empty/no words asked for (1x1 empty)
	Run time: .031 seconds
  -all allowed words larger than grid (2x1 +cat)
	Run time: .028 seconds
  -empty grid (0x0)
	Run time: .026 seconds
  -only not allowed words (2x1 -no)
	Run time: .027 seconds
  -words that contain/compose a not allowed word (2x1 +no -on)
	Run time: .028 seconds
  -more words than room on grid (3x1 +cat +one)
	Run time: .028 seconds


MISC. COMMENTS TO GRADER:  
Optional, please be concise!
I copied a lot of code from lecture and then modified it, thus the coding style might be slighly different (along with commenting style).
Order notation sucks just for the record.


