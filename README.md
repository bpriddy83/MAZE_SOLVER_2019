# MAZE_SOLVER_2019
use stack or queque to solve mazes
Brianna Priddy
CSCI262
2pm section
Project 2 - Mazes

This project took me roughly 3 hours to complete

This was a good project to see how queues and stacks work. The lab write up was easy to understand and helped
walk me through the process.

PROJECT DESCRIPTION:

PART 1 - Download and build the starter code

In order to practice working with code written by other programmers this code was set up so only a few portions needed
to be completed. The functionality to open files with mazes in them was the first task, followed by finding the starting
position in the maze, and to traverse through the maze. The code compiled as is and was easy to navigate.

PART 2 - Write the _read_maze() method

The first line of the files had the number of rows and columns in each maze. Walls were defined by '#' symbols, '*'
was the goal and 'o' was the starting position. Other moves were '.'. The vectors of rows and columns were established
and filled with the proper amount of rows of text from the file. I tested this by printing the maze.

PART 3 - Write the _print_maze() method

Because I had printed the maze in the step above this step was redundant. I moved the printing code to this section and
the code ran successfully.

PART 4 - Write the _initialize() method

The stored vectors now had to be traversed for the initial position 'o'. Similar for loops as printing were used and I
created a new class to store points that would be used in the maze and their row and column position. This was my first
time using a class in another class, so it was a nice learning experience. I tested the point by printing out the
row and column location. I then added the point to the queue or stack.

PART 5 - Write the _step() method

The following functionality was implemented:

    If no more steps are possible (your stack is empty), set _no_more_steps to true and return.
    Pop a point from the stack. This is your current point.
    If the current point is the goal ('*'), note this (set the _goal_reached and _no_more_steps variables to true) and
    return.
    If the point is other than the start point, mark it as visited (set it to '@').
    Examine the points above, to the right, below, and to the left of the current point. If they are valid (i.e.,
    within the maze boundaries), reachable (i.e., not walls), and not already visited (not marked with '@' or the 'o'),
    then push them onto the stack.
    Make sure the top item on your stack is not visited (this can happen when, for instance, you have visited multiple
    neighbors of a point previously). Pop any already visited items.
    If the stack is empty, set _no_more_steps to true.

Helper functions for adding to stacks and queues, checking size and validity fo points was utilized. Valid points
were a little tricky. It was okay to check if it was a '#' or a 'o' or an '@', but remembering to check the bounds of
the vectors was the tricky part.
