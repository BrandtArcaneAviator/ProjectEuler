// Program to count the maximum number of routes through
// a lattice grid of a by b cells (represented as a matrix
// M(x,y)) starting at the top left corner (i.e. x=0, y=0)
// and ending in the lower right corner (i.e. x=a, y=b).
// Note that during this route we only allow moves that
// go right one grid space (e.g. from x=0 to x=1) or go
// down one grid space (e.g. from y=0 to y=1).
// 
// For reference, here is an example grid (2x2):
	// 0,0 -- 1,0 -- 2,0
	// ^      ^      ^
	// ^      ^      ^
	// 0,1 -- 1,1 -- 2,1
	// ^      ^      ^
	// ^      ^      ^
	// 0,2 -- 1,2 -- 2,2
//  
// In this example grid, there are exactly 6 routes:
	// 1) 0,0 -> 1,0 -> 2,0 -> 2,1 -> 2,2.
	// 2) 0,0 -> 1,0 -> 1,1 -> 2,1 -> 2,2.
	// 3) 0,0 -> 1,0 -> 1,1 -> 1,2 -> 2,2.
	// 4) 0,0 -> 0,1 -> 1,1 -> 2,1 -> 2,2.
	// 5) 0,0 -> 0,1 -> 1,1 -> 1,2 -> 2,2.
	// 6) 0,0 -> 0,1 -> 0,2 -> 1,2 -> 2,2.
//
// Thus, for an arbitrary a by b grid, we need to implement
// the following:
	// i) A matrix representing the grid (a 2-d std::vector).
	// ii) A "2-d" point (can use a class object for this),
	//    that points to the current position on this grid
	//    (maybe use an set of iterator that point to the
	//    element in the matrix?).
	// iii) Member functions which check the current position
	//    and execute a specific path (right one, down one).
	// iv) A counter for the number of possible routes.  
// Note that we only care about unique routes, so this
// should only ever increase when we take unique paths.
// To this end, we can record previous paths (e.g. using
// push_back of sets of two values into a vector; a 2-d point
// class would be highly valuable for this) in another
// set of vectors (or a matrix) and compare them to
// new paths to determine if we increase this counter.
// Notably, we could alternatively implement this inside 
// the pathing itself, such that if we've already approached 
// in a certain way we can avoid that path in the future
// (one example here is that path 1) for the 2x2 above
// goes through the point 2,0 and only this path goes
// through this point). Furthermore, we can immediately
// identify a few known routes (and thus avoid simulating
// these):
	// 1) Go directly right to end of cells (i.e. x=a),
	//    then go directly down to end of cells (i.e., y=b).
	// 2) Go directly down to end of cells (i.e. y=b),
	//    then go directly right to end of cells (i.e., x=a).
//  
// There are two ways we can explore paths, a) choosing
// moves randomly (i.e. using an RNG with equal values
// between move right, move down) and checking the final
// path against previous paths for uniqueness (but this
// may repeat paths often and needlessly), or b) systematically
// by exploring all variations of potential paths.
// I'll note that, e.g. for a 2x2 grid, a given path
// can only EVER have two moves to the right and two moves
// down, thus there are only a set number of permutations
// of executing these two moves (which we know in this case
// to be the six permutations above).  This is notably
// a series of binary (off = move right, on = move down)
// choices whose length must be fixed (again, we MUST have
// 2 moves right and 2 moves down in the 2x2 grid).
// Extending this to an a x b grid, we know that we MUST
// have a moves right (the "off" choice) and b moves down
// (the "on" choice), so we only need to find the binary
// permutations of this sequence (again, we know this
// sequence must have length a + b).  Systematically,
// this mean we set up "vectors" that represent choices
// of these permutations.  Using the 2x2 example above,
// this would be like (using 0 and 1 for move right, move
// down):
	// vec1 = { 0, 0, 1, 1 }
	// vec2 = { 0, 1, 0, 1 }
	// vec3 = { 0, 1, 1, 0 }
	// vec4 = { 1, 0, 0, 1 }
	// vec5 = { 1, 0, 1, 0 }
	// vec6 = { 1, 1, 0, 0 }
// Note, in this way, we can fix the requirement that we only
// have "b" moves down by the sum of all elements in the
// vector (i.e. there must be "b" 1 values here), but also 
// note this condition also fixes "a" moves right due to the
// vector length being a + b.
//  
//


#include <iostream>
#include <vector>


// 2-d Point Class:



// 2x2 Grid Class:




int main()
{
	// 



	return 0;
}