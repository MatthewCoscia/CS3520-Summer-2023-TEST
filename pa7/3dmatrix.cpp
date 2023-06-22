// Program to read 3-dimensional matrix and display the elements as 1xSIZE^3 matrix
// TODO
// initize matrix using update_3d method (see comments below)
// display method must not be able to modify array elements (update the code as needed)
// display method must use a single loop/iterator to print the entire array with addresses
// display cannot use nested loops
//

#include <iostream>
// 1. added cstdlib header.
#include <cstdlib>
#define SIZE 7

void update_3d(double Matrix_3d[][SIZE][SIZE], int size);
void display_1d(double Matrix_3d[][SIZE][SIZE], int size);

int main(void)
{
	// prompt the user to initialize the matrix accordingly
	double Matrix_3d[SIZE][SIZE][SIZE] = {};
	// initialize the array to non-zero values (use scanf or random numbers generator)
	update_3d(Matrix_3d, SIZE);
	// display the values
	display_1d(Matrix_3d, SIZE);
	return 0;
}

void update_3d(double matrix[][SIZE][SIZE], int size)
{
    // 2. added the std namespace.
	std::cout << "Entering SIZE^3 elements of the matrix:" << std::endl;
    //3. initialized integer i.
	for (int i = 0; i < size; i++)
	{
		int j = 0;
		for (; j < size; j++)
		{
			int k = 0;
			for (; k < size; k++)
			{
				// cin for Matrix_3d[i][j][k] or random number generator
			}
		}
	}
}

// update as needed. 1 'for' loop only with 1 iterator to print all values with addresses
// must not be able to update the array.
// Share any observations.
// 4. completed the display_id function.
void display_1d(double Matrix_3d[][SIZE][SIZE], int size) {
    std::cout << "Displaying matrix values with addresses:" << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                std::cout << "Address: " << &(Matrix_3d[i][j][k]) << ", Value: " << Matrix_3d[i][j][k] << std::endl;
            }
        }
    }
}
