HOMEWORK 6 CONTEST: INVERSE WORD SEARCH


NAME:  Josephine Lyons


OPTIMIZATIONS:
What did you do?
This is the exact same as my homework submission.


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?
It seemed to run relatively quick (or at least quicker than I was expecting) on all of them.
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




