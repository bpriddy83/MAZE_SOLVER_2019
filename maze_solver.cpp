/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    maze_solver.cpp

    Code for the maze_solver class.  This class will use stack-based depth
    first search or queue-based breadth first search to find a solution (if
    one exists) to a simple maze.

    C. Painter-Wakefield
*/

#include "maze_solver.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// TODO: read the complete assignment instructions before beginning.  Also look
// at maze_solver.h - you will need to modify it as well.  In this file you
// will need to complete several methods, and add any others as needed for your
// solution. 


/*
 _read_maze()

 Read in maze information (rows, columns, maze) from the provided input stream.
*/
void maze_solver::_read_maze(istream& in) {

	//get the first line from the file

	getline(in, _next_line);

	//convert to stream

	istringstream sin(_next_line);

	//store the first values as number of rows and number of columns

	sin >> _rows;
	sin >> _columns;

	//get the rest of the lines from the file and store them in the maze vector

	for(int i = 0; i < _rows; ++i){
		getline(in, _next_line);
		_maze.push_back(_next_line);
	}

}


/*
 _write_maze()

 Output the (partially or totally solved) maze on cout.
*/
void maze_solver::_print_maze() {

    //print the maze using the vector

    for(int i = 0; i < _rows; ++i){
    	cout << _maze.at(i) << endl;
    }

}


/*
 _initialize()

 Find the start point.  Push or enqueue the start point.
*/
void maze_solver::_initialize() {

	//search each line of the maze to find the location of the initial position

	for(int i = 0; i < _rows; ++i){
		for(int j = 0; j < _columns; ++j){
			if(_maze.at(i).at(j) == 'o'){

				//create a new point object

				point beginning;
				cout << "\nThe starting position was set to : " << i << ", " << j << endl;

				beginning.row = i;
				beginning.column = j;

				//add the new position to the stack or queue

				_push(beginning);
			}
		}
	}

}


/*
 _step()

 Take *one* step towards solving the maze, setting _no_more_steps and
 _goal_reached as appropriate.  This implements the essential maze search
 algorithm; take the next location from your stack or queue, mark the
 location with '@', add all reachable next points to your stack or queue,
 etc.

 Notes:

 - Your initial point should have been pushed/enqueued in the _initialize()
   method.

 - Set the _no_more_steps variable to true when there are no more reachable
   points, or when the maze was successfully solved.

 - Set the _goal_reached variable to true if/when the maze was successfully
   solved.

 - You should write an '@' over every location you have previously visited,
   *except* for the start and goal positions - they should remain 'o' and '*',
   respectively.

 - Since the run() method will call _print_maze() in between calls to _step(),
   you probably want to try to make progress on each call to step.  On some
   mazes, depending on your approach, it may be possible to add the same
   point multiple times to your stack or queue - i.e., if a point is reachable
   from multiple other points.  When this happens, your code will work, but
   it may make very slow progress.  To fix the problem, simply run a loop to
   remove any already visited points from your stack or queue at the beginning
   or end of _step().

 - There are many approaches to dealing with invalid/unreachable points; you
   can choose to add them and then remove them next time you get into _step(),
   you can choose to not add them in the first place, etc.

 - It is strongly recommended that you make helper methods to avoid code
   duplication; e.g., a function to detect that a point is out of bounds is
   a real help on the mazes with no walls.  You can also think about pulling
   out methods that do the actual acting on stacks/queues - this will reduce
   code duplication, since everything is identical between the two except
   for whether you use your stack or queue.  E.g., you could have methods
   named "_push", "_pop", "_next" which use the appropriate data structure.
*/
void maze_solver::_step() {

	//	If no more steps are possible (your stack is empty), set _no_more_steps to true and return.

	if(_size() == 0){
		_no_more_steps = true;
		return;
	}

	//	Pop a point from the stack. This is your current point.

	point current_point = _top();
	_pop();

	//	If the current point is the goal ('*'), note this (set the _goal_reached and _no_more_steps variables
	// to true) and return.

	if(_maze.at(current_point.row).at(current_point.column) == '*'){
		_goal_reached = true;
		_no_more_steps = true;
		return;
	}

	//	If the point is other than the start point, mark it as visited (set it to '@').

	else {
		if (_maze.at(current_point.row).at(current_point.column) != 'o') {
			_maze.at(current_point.row).at(current_point.column) = '@';
		}
	}


	//	Examine the points above, to the right, below, and to the left of the current point. If they are valid
	// (i.e., within the maze boundaries), reachable (i.e., not walls), and not already visited (not marked with '@'
	// or the 'o'), then push them onto the stack.

	point up;
	point down;
	point left;
	point right;

	up.row = current_point.row-1;
	up.column = current_point.column;

	down.row = current_point.row+1;
	down.column = current_point.column;

	left.row = current_point.row;
	left.column = current_point.column-1;

	right.row = current_point.row;
	right.column = current_point.column + 1;

	if(_is_valid(up)){
		_push(up);
	}

	if(_is_valid(right)){
		_push(right);
	}

	if(_is_valid(down)){
		_push(down);
	}
	if(_is_valid(left)){
		_push(left);
	}


	//	Make sure the top item on your stack is not visited (this can happen when, for instance, you have visited
	// multiple neighbors of a point previously). Pop any already visited items.

	while(_size() != 0){
		if(_maze.at(_top().row).at(_top().column) == '@') {
			_pop();
		} else
			break;
	}


	//	If the stack is empty, set _no_more_steps to true.

	if(_size() == 0){
		_no_more_steps = true;
	}
}




/***************************************************************************
    You should not need to modify code below this point.  Touch at your own
    risk!
****************************************************************************/

/*
 maze_solver constructor

 You should not need to modify this.  It opens the maze file and passes
 the input stream to read_maze(), along with setting up some internal state
 (most importantly, the variable telling you whether to use a stack or
 a queue).
*/
maze_solver::maze_solver(string infile, bool use_stak, bool pause) {
	_use_stack = use_stak;
	_do_pause = pause;

	_no_more_steps = false;
	_goal_reached = false;

	// parse out maze name for later use in creating output file name
	int pos = infile.find(".");
	if (pos == string::npos) {
		_maze_name = infile;
	} else {
		_maze_name = infile.substr(0, pos);
	}

	// open input file and read in maze
	ifstream fin(infile);

	_read_maze(fin);

	fin.close();
}

/*
 run()

 Initializes the maze_solver, then runs a loop to keep moving forward towards
 a solution.

 While more steps are possible (while no_more_steps == false), run() calls
 step(), then calls print_maze(), then pause().  Once there are no more steps,
 it prints a success/failure message to the user (based on the goal_reached 
 flag) and writes the final maze to a solution file.
*/

void maze_solver::run() {
    _initialize();

	cout << "Solving maze '" << _maze_name << "'." << endl;
	cout << "Initial maze: " << endl << endl;
	_print_maze();
	cout << endl;
	_pause();

	// main loop
	while (!_no_more_steps) {
		_step();
		cout << endl;
		_print_maze();
		cout << endl;
		_pause();
	}

	// final output to user
	cout << "Finished: ";
	if (_goal_reached) {
		cout << "goal reached!" << endl;
	} else {
		cout << "no solution possible!" << endl;
	}
}


/*
 pause()

 Pauses execution until user hits enter (unless do_pause == false).
*/
void maze_solver::_pause() {
	if (!_do_pause) return;
	string foo;
	cout << "Hit Enter to continue...";
	getline(cin, foo);
}

bool maze_solver::_is_valid(point p){
	if((p.row >= 0) && (p.row < _rows) && (p.column >=0) && (p.column < _columns)){
		if ((_maze.at(p.row).at(p.column) != '#') &&
			(_maze.at(p.row).at(p.column) != '@') &&
			(_maze.at(p.row).at(p.column) != 'o')){
			return true;
		}
	}
	return false;
}

void maze_solver::_push(point p) {

	if(_use_stack) {
		stackOfPoints.push(p);
	} else{
		queueOfPoints.push(p);
	}
}

void maze_solver::_pop(){

	//check to top of the stack to make sure it hasn't been visited already

	if(_use_stack) {
		stackOfPoints.pop();
	} else{
		queueOfPoints.pop();
	}
}
point maze_solver::_top(){
	//check to top of the stack to make sure it hasn't been visited already

	if(_use_stack) {
		return stackOfPoints.top();
	} else{
		return queueOfPoints.front();
	}
}

int maze_solver::_size(){
	//check the size
	if(_use_stack) {
		return stackOfPoints.size();
	} else{
		return queueOfPoints.size();
	}
}