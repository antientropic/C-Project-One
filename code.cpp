/* This program compares the following five sort algorithms:
 * Heapsort, mergesort, quick sort, select sort, and insert sort
 * Author: Clifford Anderson
 * Date: Last modified on 02/06/2021
 */

#include <algorithm>   // Provides swap
#include <cstdlib>     // Provides EXIT_SUCCESS, size_t
#include <iostream>    // Provides cout
#include <ctime>       // provide clock function.
using namespace std;
const size_t ARRAY_SIZE = 10000;

// PROTOTYPES of the sorting functions used in this test program:
// Each of these functions has the same precondition and postcondition:
// Precondition: data is an array with at least n components.
// Postcondition: The elements of data have been rearranged so
// that data[0] <= data[1] <= ... <= data[n-1].
//void heapsort(int data[], size_t n);
void mergesort(int data[], size_t n);
void quicksort(int data[], size_t n);
void selectionsort(int data[], size_t n);
void insertionsort(int data[], size_t n);

// PROTOTYPE of a function that will test one of the sorting functions:
void testsort(void sorter(int data[], size_t n), const char* name);


int main()
{
	cout << "This program will generate arrays with ARRAY_SIZE elements" << endl;
	cout << "Then it sorts the arrays by using different sort function and " << endl;
	cout << "displays the needed time for each sorting\n" << endl;
	cout << "Press Enter key to start test ";
	getchar();
	cout << endl;

	/*testsort(heapsort, "heapsort");
	cout << "Press Enter key to continue ";
	getchar();
	cout << endl;*/

	testsort(mergesort, "mergesort");
	cout << "Press Enter key to continue ";
	getchar();
	cout << endl;

	testsort(quicksort, "quicksort");
	cout << "Press Enter key to continue ";
	getchar();
	cout << endl;

	testsort(selectionsort, "selectionsort");
	cout << "Press Enter key to continue ";
	getchar();
	cout << endl;


	testsort(insertionsort, "insertionsort");

	cout << "Press Enter key to exit ";
	getchar();

	return EXIT_SUCCESS;
}



void testsort(void sorter(int data[], size_t n), const char* name)
{
	const int    LIMIT = 10000;    // Biggest number to put in the array
	int data[ARRAY_SIZE];              // Array of integers to be sorted
	size_t count[LIMIT];               // Count of how many times each
									   // number appears in data array
	size_t i;                          // Index for the data array.

	clock_t beginning, ending;          // the beginning and ending time to call sorter function

	cout << "Testing the " << name << endl;

	// Initialize the count array to zeros:
	fill_n(count, LIMIT, (size_t)0);

	// Fill the data array with random numbers:
	srand(0);
	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		data[i] = rand() % (LIMIT);
		++count[data[i]];
	}

	// Sort the numbers
	beginning = clock();
	sorter(data, ARRAY_SIZE);
	ending = clock();

	// Check that the data array is sorted and that it has the right
	// number of copies of each number:
	--count[data[0]];
	for (i = 1; i < ARRAY_SIZE; ++i)
	{
		if (data[i - 1] > data[i])
		{
			cout << "Incorrect sort at index " << i << endl;
			return;
		}
		--count[data[i]];
	}

	for (i = 0; i < (size_t)LIMIT; ++i)
	{
		if (count[i] != 0)
		{
			cout << "Incorrect numbers in the data array after sorting."
				<< endl;
			return;
		}
	}


	cout << "Sorting completed correctly ";
	cout << "in " << (ending - beginning) / 1000.0 << " seconds\n" << endl;
}



//*************************************************************************
// HEAPSORT IMPLEMENTATION:
// Assume that the heap data stored in array. i.e. we view the array as heap
/*size_t parent(size_t k)
{

}

size_t left_child(size_t k)
{

}

size_t right_child(size_t k)
{

}

// make a heap based on given data array
void make_heap(int data[], size_t n)
{

}

void reheapify_down(int data[], size_t n)
{

}

//void heapsort(int data[], size_t n)
//{
//
//}
//*************************************************************************
*/


//*************************************************************************
// MERGESORT IMPLEMENTATION:
//
void merge(int data[], size_t n1, size_t n2)
// Precondition: data is an array (or subarray) with at least n1 + n2 elements.
// The first n1 elements (from data[0] to data[n1 - 1]) are sorted from
// smallest to largest, and the last n2 (from data[n1] to data[n1 + n2 - 1])
// also are sorted from smallest to largest.
// Postcondition: The first n1 + n2 elements of data have been rearranged to be
// sorted from smallest to largest.
// NOTE: If there is insufficient dynamic memory, then bad_alloc is thrown.
// Library facilities used: cstdlib
{
	int mergedSize = n1 + n2; //this variable provides the size of our dynamic array
	size_t mergePos = 0; //this initializes the beginning index of the dynamic array
	size_t leftPos = 0; //this provides the same functionality as the i key in the book example
	size_t rightPos = 0; //this provides the same functionality as the k key in the book example
	int* mergedNumbers; //this declares a dynamic array
	
	mergedNumbers = new int[mergedSize](); //this initializes the dynamic array

	while ((leftPos < n1) && (rightPos < n2)) { //this while loop iterates through the array and stores the smallest value at mergePos
		if (data[leftPos] < (data + n1)[rightPos]) {
			mergedNumbers[mergePos] = data[leftPos];
			leftPos++; //this provides loop control
		}
		else {
			mergedNumbers[mergePos] = (data + n1)[rightPos];
			rightPos++; //this provides loop control

		}
		mergePos++; //this increments the mergePos index
	}

	while (leftPos < n1) { //if there are any remaining indexes prior to n1 after rightPos == n2, this code handles them
		mergedNumbers[mergePos] = data[leftPos];
		leftPos++;
		mergePos++;
	}
	
	while (rightPos < n2) {// if there are any remaining indexes prior to n2 after leftPos == n1, this code handles them
		mergedNumbers[mergePos] = (data + n1)[rightPos];
		rightPos++;
		mergePos++;
	}

	for (mergePos = 0; mergePos < mergedSize; mergePos++) {//this copies our sorted array back into the original array
		data[mergePos] = mergedNumbers[mergePos];
	}

	delete[] mergedNumbers; //this deletes the dynamic array
}

void mergesort(int data[], size_t n)
// Precondition: data is an array with at least n components.
// Postcondition: The elements of data have been rearranged so
// that data[0] <= data[1] <= ... <= data[n-1].
// NOTE: If there is insufficient dynamic memory, thenbad_alloc is thrown.
// Library facilities used: cstdlib
{
	size_t n_one = 0; //the declaration of n_one and n_two allow us to create values to be used to populate the dynamic array in the merge function 
	size_t n_two = 0;

	if (n > 1) { //if n = 1, no sorting is necessary

		n_one = n / 2; //this is the halfway point
		n_two = n - n_one; //this is this is the remaining size of the array

		mergesort(data, n_one); //these function calls recursively operate on the values of n_one and n_two
		mergesort((data + n_one), n_two); //the use of (data + n_one) allows us to set the pointer to the relevant portion of the data array

		merge(data, n_one, n_two); //this invokes the merge function to order the array with the sorted elements
	}
	else {
		return;
	}

}
//*************************************************************************



//*************************************************************************
// QUICKSORT IMPLEMENTATION:
//
//*************************************************************************

size_t partition(int data[], size_t n)
{
	int pivot = data[n - 1]; //this variable declares and initializes the pivot point
	size_t highIndex = 0; //this variable provides the value to be returned

	for (int i = 0; i < n - 1; i++) //this for loop allows us to iterate through the array to check values
	{
		if (data[i] < pivot) //in the instance that value indexed at i is less than the value of pivot, swap is performed
		{
			int swap = data[i]; //this is a standard swap algorithm
			data[i] = data[highIndex];
			data[highIndex] = swap;
			highIndex++; //this increments the value of highIndex
		}
	}

	return highIndex; //this returns the highest index of the low partition
}


void quicksort(int data[], size_t n)
{
	int lowPartition = partition(data, n); //invocation of the partition function returns the value of the upper index of the low partition

	int swap = data[lowPartition]; //this is a standard swap algorithm 
	data[lowPartition] = data[n - 1];
	data[n - 1] = swap;
	
	if (lowPartition > 1) { //this code allows for recursive sorting of both the high and low partitions of the array
		quicksort(data, lowPartition);
	}
	if (n - lowPartition - 1 > 1){
		quicksort((data + lowPartition+ 1), (n - lowPartition -1)); //the use of the (data + lowPartition + 1) allows us to set the pointer to the desired value of the array
	}
}

//*************************************************************************
// SELECTIONSORT IMPLEMENTATION:
//
void selectionsort(int data[], size_t n)
// Library facilities used: algorithm, cstdlib
{
	int i = 0; //this variable provides outer loop control
	int j = 0; //this variable provides inner loop control
	int smallestIndex = 0; //this variable gives us a reference index for comparison to find the smaller value in each pair of indexed values
	int swap = 0;  //this variable allows us to swap indexed values
	
	for (i = 0; i < n - 1; ++i) { //the outer loop allows us to iterate through all array indexes

		smallestIndex = i; //in each iteration, smallest index takes on the value of i
		
		for (j = i + 1; j < n; ++j) { //the inner loop allows us to compare the value of j (always 1 more than i) against the value of i

		 if (data[j] < data[smallestIndex] ) {
			 smallestIndex = j; //if the integer located at index j is less than the the integer located at index smallestIndex,
			                    //smallestIndex takes on the value of 
		 }
	  }

		swap = data[i]; //the rest of the code is a standard swapping algorithm
		data[i] = data[smallestIndex];
		data[smallestIndex] = swap;
   }

}
//*************************************************************************

//*************************************************************************
// INSERTION SORT IMPLEMENTATION
//
void insertionsort(int data[], size_t n)
{
	int i = 0; //this variable provides outer loop control
	int j = 0; //this variable provides inner loop control
	int swap = 0;  //this variable allows us to swap indexed values

	for (i = 1; i < n; i++) { //this outer loop enables us to iterate from index 1 to n
		j = i; //this assignment allows us to use variable j to sort the array

		while (j > 0 && data[j] < data[j - 1]) { //the while loop tests each index against the immediately preceding index;
												 //in the initial iteration, data[1] is tested against data[0]. if data[1]
												 //is less than data[0], the body of the while loop executes.

			swap = data[j]; //all of this code is standard code for swapping values
			data[j] = data[j - 1];
			data[j - 1] = swap;
			j--; //this decrement operator allows us to terminate the while loop (one condition is that j must be greater than 0);
		}
	}

}


