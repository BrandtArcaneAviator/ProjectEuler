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

 Thus, for an arbitrary a by b grid, we would need to implement
 the following:
	 i) A matrix representing the grid (a 2-d std::vector).
	 ii) A "2-d" point (can use a class object for this),
	    that points to the current position on this grid
	    (maybe use an set of iterator that point to the
	    element in the matrix?).
	 iii) Member functions which check the current position
	    and execute a specific path (right one, down one).
	 iv) A counter for the number of possible routes.  
 However, note that we only care about unique routes, so this
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
 By implementing it this way, we can determine the
 number of unique paths for ANY a x b grid (again,
 noting that a != b is fine so long as we have b 1-values
 and a 0-values).

 I'll note that, as in problem 24, to do permutations
 in lexicographic order, we can use std::next_permutation
 or std::prev_permutation.
 We use the latter here to iterate permutations starting
 at the LAST lexicographic value (i.e. with all 1 values
 first in the digit sequence), saving only the unique ones.
 The length of the vector holding these permutations (vectors
 themselves) is then the number of unique possible paths in
 the grid using only move right one, move down 1.
*/  

#include <algorithm> // for std::next_permutation
#include <iostream>
#include <numeric> // For std::accumulate.
#include <vector>


	/*
	Recall a 1 value is a move down. This then
	returns true if the sum of values in the vector
	equals b, i.e. there are b moves down in the path.
	Note again this also means there are a moves right
	since the vector length is a + b and moves right are
	0 values.  This is used to check that the vector is
	a valid permutation, but does not guarentee uniquenss.
	*/
	bool checkNumMoves(std::vector<int>& binarypath1, const int& b)
	{
		if ((std::accumulate(binarypath1.begin(), binarypath1.end(), 0)) == b)
			return true;
		else
			return false;
	}

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
	std::vector<std::vector<int>> uniquePaths{};

	/*
	Initialize a binarypath object to manipulate:
	*/
	std::vector<int> currentPath{};
	currentPath.reserve(a + b);

	/*
	Set up an initial path, which does b moves down first,
	and then a moves right.  Notably sets up the
	# moves down == b and # moves right = a conditions
	by the placement of digits into this vector.
	All subsequent permutations keep these conditions
	as a result.
	*/
	for (int i{ 0 }; i < (a + b); ++i)
	{
		// If there are b moves down:
		if (checkNumMoves(currentPath, b))
		{
			// Add move right.
			currentPath.push_back( 0 );
		}
		else
		{
			// Add move down.
			currentPath.push_back( 1 );
		}
	}
	// Now we push_back this as the first unique vector:
	uniquePaths.push_back( currentPath );

	/* DEBUG: print the first permutation:
	std::cout << "The first permutation is: (";
	for (int i : currentPath)
	{
		std::cout << i << ", ";
	}
	std::cout << ").\n";
	*/

	/*
	Now we need to run through permutations of paths
	which satisfy checkNumMoves() and find unique ones.
	Note again that each element can only have either 0
	or 1 values.  For the 2x2 dxample, e.g., note we have
	two 0 and two 1 values, so we need the unique permutations 
	of the digit vector [1,1,0,0], which is already made
	above by the first initialization.
	*/
	
	/* Boolean Variable to confirm uniqueness: */
	bool pathisUnique{ true };


	/*  
	Outer loop for permutations.
	Note we need to use prev_permutation because
	we started with the LAST lexicographic permutation,
	e.g. in 2x2 grid, [1,1,0,0].
	*/
	do
	{
		/* Checking previous permutations for uniquness */
		for (std::vector<int> path : uniquePaths)
		{
			/* If current path already exists in 
		 	   uniquePaths (i.e. is NOT unique): */
			if (std::equal(path.begin(), path.end(), currentPath.begin()))
			{
				pathisUnique = false;
				break; 
				/* necessary break to keep pathisUnique false
				in the instance where we find its not unique. */
			}

			/* Will only stay true if the if statement
			fails for ALL paths in uniquePaths,
			i.e. we find another unique permutation: */
		}

		/* If path is unique, add it; otherwise
		   iterate to next permutation: */
		if (pathisUnique)
		{
			uniquePaths.push_back(currentPath);
		}

		/* Reset boolean variable: */
		pathisUnique = true;
	
	} while (std::prev_permutation(currentPath.begin(), currentPath.end()));
	

	/* DEBUG: print the permutations: */
	for (int_fast32_t vec{ 0 }; vec < static_cast<int_fast32_t>(uniquePaths.size()); ++vec)
	{
		for (int_fast32_t it{ 0 }; it < static_cast<int_fast32_t>(uniquePaths[vec].size()) ; ++it)
		{
			std::cout << uniquePaths[vec].at(it);
		}
		std::cout << "    ";
		if ((vec + 1) % 5 == 0)
		{
			std::cout << '\n';
		}
	}
	std::cout << '\n';


	/* 
	Now we can find the max number of unique paths simply
	by checking the length of the unique paths vector: 
	*/
	std::cout << "The number of unique paths using only move down, move right in a "
		<< a << " X " << b << " grid is: " << uniquePaths.size() << ".\n";


	return 0;
}