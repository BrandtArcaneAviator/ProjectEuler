/*
Program to count the maximum number of routes through
 a lattice grid of a by b cells (represented as a matrix
 M(x,y)) starting at the top left corner (i.e. x=0, y=0)
 and ending in the lower right corner (i.e. x=a, y=b).
 Note that during this route we only allow moves that
 go right one grid space (e.g. from x=0 to x=1) or go
 down one grid space (e.g. from y=0 to y=1).
 
 For reference, here is an example grid (2x2):
	 0,0 -- 1,0 -- 2,0
	 ^      ^      ^
	 ^      ^      ^
	 0,1 -- 1,1 -- 2,1
	 ^      ^      ^
	 ^      ^      ^
	 0,2 -- 1,2 -- 2,2
  
 In this example grid, there are exactly 6 routes:
	 1) 0,0 -> 1,0 -> 2,0 -> 2,1 -> 2,2.
	 2) 0,0 -> 1,0 -> 1,1 -> 2,1 -> 2,2.
	 3) 0,0 -> 1,0 -> 1,1 -> 1,2 -> 2,2.
	 4) 0,0 -> 0,1 -> 1,1 -> 2,1 -> 2,2.
	 5) 0,0 -> 0,1 -> 1,1 -> 1,2 -> 2,2.
	 6) 0,0 -> 0,1 -> 0,2 -> 1,2 -> 2,2.

 Thus, for an arbitrary a by b grid, we need to implement
 the following:
	 i) A matrix representing the grid (a 2-d std::vector).
	 ii) A "2-d" point (can use a class object for this),
	    that points to the current position on this grid
	    (maybe use an set of iterator that point to the
	    element in the matrix?).
	 iii) Member functions which check the current position
	    and execute a specific path (right one, down one).
	 iv) A counter for the number of possible routes.  
 Note that we only care about unique routes, so this
 should only ever increase when we take unique paths.
 To this end, we can record previous paths (e.g. using
 push_back of sets of two values into a vector; a 2-d point
 class would be highly valuable for this) in another
 set of vectors (or a matrix) and compare them to
 new paths to determine if we increase this counter.
 Notably, we could alternatively implement this inside 
 the pathing itself, such that if we've already approached 
 in a certain way we can avoid that path in the future
 (one example here is that path 1) for the 2x2 above
 goes through the point 2,0 and only this path goes
 through this point). Furthermore, we can immediately
 identify a few known routes (and thus avoid simulating
 these):
	 1) Go directly right to end of cells (i.e. x=a),
	    then go directly down to end of cells (i.e., y=b).
	 2) Go directly down to end of cells (i.e. y=b),
	    then go directly right to end of cells (i.e., x=a).
  
 There are two ways we can explore paths, a) choosing
 moves randomly (i.e. using an RNG with equal values
 between move right, move down) and checking the final
 path against previous paths for uniqueness (but this
 may repeat paths often and needlessly), or b) systematically
 by exploring all variations of potential paths.
 I'll note that, e.g. for a 2x2 grid, a given path
 can only EVER have two moves to the right and two moves
 down, thus there are only a set number of permutations
 of executing these two moves (which we know in this case
 to be the six permutations above).  This is notably
 a series of binary (off = move right, on = move down)
 choices whose length must be fixed (again, we MUST have
 2 moves right and 2 moves down in the 2x2 grid).
 Extending this to an a x b grid, we know that we MUST
 have a moves right (the "off" choice) and b moves down
 (the "on" choice), so we only need to find the binary
 permutations of this sequence (again, we know this
 sequence must have length a + b).  Systematically,
 this mean we set up "vectors" that represent choices
 of these permutations.  Using the 2x2 example above,
 this would be like (using 0 and 1 for move right, move
 down):
	 vec1 = { 0, 0, 1, 1 }
	 vec2 = { 0, 1, 0, 1 }
	 vec3 = { 0, 1, 1, 0 }
	 vec4 = { 1, 0, 0, 1 }
	 vec5 = { 1, 0, 1, 0 }
	 vec6 = { 1, 1, 0, 0 }
 Note, in this way, we can fix the requirement that we only
 have "b" moves down by the sum of all elements in the
 vector (i.e. there must be "b" 1 values here), but also 
 note this condition also fixes "a" moves right due to the
 vector length being a + b. For the 20x20 goal, this means
 we have a 40 element vector which has 20 1-values
 and 20 0-values and we find all the unique
 permutations of this vector; note the number of
 unique vectors equals the number of unique paths.
 We can thus make a vector of these binary path
 vectors using a vector of a class of these vectors.
*/  


#include <iostream>
#include <numeric> // For std::accumulate.
#include <vector>

/* 
Vector class for a given path (0=move right,
1 = move down): 
*/
class BinaryPath
{
private:
	std::vector<int> m_binarypath{};
	int m_a{};
	int m_b{};

public:
	// Default initalizes a 1 by 1 grid.
	BinaryPath() : m_a{ 1 }, m_b{ 1 }
	{
		m_binarypath.reserve(2);
	}

	// For an axb grid:
	BinaryPath(int& a, int& b) : m_a{ a }, m_b{ b }
	{
		m_binarypath.reserve((m_a + m_b));
	}

	std::vector<int>& getPath() { return m_binarypath; }
	int& getPathStep(int& nElement1) { return m_binarypath.at(nElement1); }

	/*
	To set the binary value of a given path step.
	Note nElement goes from 0 to a + b - 1,
	and that nValue should only have 0 or 1 values.
	*/
	void setPathStep(int& nElement, int nValue)
	{
		m_binarypath.at(nElement) = nValue;
	}

	/*
	Recall a 1 value is a move down. This then
	returns true if the sum of values in the vector
	equals b, i.e. there are b moves down in the path.
	Note again this also means there are a moves right
	since the vector length is a + b and moves right are
	0 values.  This is used to check that the vector is
	a valid permutation, but does not guarentee uniquenss.
	*/
	bool checkNumMoves()
	{
		if ((std::accumulate(m_binarypath.begin(), m_binarypath.end(), 0)) == m_b)
			return true;
		else
			return false;
	}

};

int main()
{
	/*
	Ask user to input the size of grid a x b:
	*/
	std::cout << "Enter the width (max x) of lattice grid: ";
	int a{};
	std::cin >> a;
	std::cout << "Enter the height (max y) of lattice grid: ";
	int b{};
	std::cin >> b;

	/*
	Make a vector of BinaryPath vectors which needs
	dynamic length (we don't know the number of
	unique permutations yet).
	*/
	std::vector<BinaryPath> uniquePaths{};

	/*
	Initialize a binarypath object to manipulate:
	*/
	BinaryPath currentPath{ a, b };

	/*
	Set up an initial path, which does b moves down first,
	and then a moves right:
	*/
	for (int i{ 0 }; i < (a + b); ++i)
	{
		// If there are b moves down:
		if (currentPath.checkNumMoves())
		{
			// Add move right.
			currentPath.setPathStep(i, 0);
		}
		else
		{
			// Add move down.
			currentPath.setPathStep(i, 1);
		}
	}
	// Now we push_back this as the first unique vector:
	uniquePaths.push_back( currentPath );

	/*
	Now we need to run through permutations of paths
	which satisfy checkNumMoves() and find unique ones.
	Note again that each element can only have either 0
	or 1 values.
	*/
	
	// Outer loop for permutations:
	/*
	for ()
	{
		// Inner loop for constructing currentPaths:
		for ()
		{

		}
	}
	*/


	return 0;
}