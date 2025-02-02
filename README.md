# About the project
A preprocessor to convert certain arithmetic operations on matrices to C code.

# Running the project
In a Linux environment, use the following command:
`./P232.sh prog.c`

# Arithmetic operations

| Operation  | Functionality | 
|------------|---------------|
|@int arr(n) | Declares a 1D array with the name arr and size n.|
|@int arr(m,n) | Declares a 2D mxn array with the name arr.|
|@read arr < f1 | Reads all elements of an array from a file.|
|@copy arr1 = arr2 | Copies the elements of arr2 to arr1.|
|@init arr = 5 | Initializes the values of the elements in the arr to the constant value of 5. |
|@print arr | Prints the elements of the array. |
|@dotp arr1 = arr2 . arr3   | Calculates the dot product of arr2 and arr3 and stores it in arr1 and preprocessor variable P_dot. |
|@add arr1 = arr2 + arr3 | adds arr3 to arr2 and stores the result of each element in arr1 accordingly. |
|@mult arr1 = arr2 * arr3 | Does matrix multiplication of arr2 and arr3 and stores the each element of resulting array in arr1 accordingly. |
|@sum A | Sums all the elements of A and then assigns this value to the preprocessor variable P_sum. |
|@aver A | Calculates the average of the elements of A and stores this value to the preprocessor variable P_aver. |

# An example

```C
#include "P_header.h"
int main()
{
	
	@int B(10,2)
	@int Z(10,2)
	@int A(10)
	@int C(10)
	@int T(10)
	@init A = 2
	@aver A


	return 0;
}
```

```C
#include "P_header.h"
int main()
{
int B[10][2];
int Z[10][2];
int A[10];
int C[10];
int T[10];
int size0 = sizeof(A) / sizeof(A[0]);
for(int i = 0; i < size0; i++) {
	A[i] = 2;
}
double average1 = 0;
int size1 = sizeof(A) / sizeof(A[0]);
for(int i = 0;i < size1;i++)
	average1 += A[i];
P_aver = average1 / size1;
return 0;
}
```
