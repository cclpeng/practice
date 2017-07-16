#include <iostream>
#include <string>
#include <sstream>
#include <cctype>		//isalpha
#include <stdlib.h>
using namespace std;


//for 10 ppl, supposed to enter number of pancakes each person eats
//then display which person ate mostpancakes down to which person ate
//least pancakes



void quicksort(int* arr, int piv, int last)
{
	/*
	pick card at 0th, first opened = 1st; last closed = -1st
	for 1st to last, if card < 0th, switch card with first opened. card becomes last closed.first opened bcomes last closed + 1
	Finally, swap 0th card with last last closed card
	That's the end of one quicksort. Now do again with other sections
	*/
	int arraySorted = 0; //0 = true. can be set to false during for

	if(last - piv == 1)	//list is considered sorted for subarray sz 1
		return;

	int fOpen = piv + 1, lastC = -1;
	for(int i = fOpen; i < last; i++)
	{							//3, 4, 1, ...
		if(arr[i] < arr[piv]) 	//i=2, piv=0, ([2]=1 < [0]=3)
		{						//fOpen=1, lastC=-1
			int temp = arr[i];	//[1]=4 -> 1, [2]=4
			arr[i] = arr[fOpen];	
			arr[fOpen] = temp;	//3, 1, 4, ...
			lastC = fOpen;		//[1] becomes lastC, lastC = 1
			fOpen = lastC + 1;  //fOpen becomes 2

			arraySorted = 1;	//this subarray is not sorted, more quicksort calls needed
		}
	}

	if(arraySorted == 0)	//subarray sorted
		return;

	int temp = arr[piv];		//1,3,4
	arr[piv] = arr[lastC];
	arr[lastC] = temp;

	cout << piv<<", "<< lastC<<", "<<lastC + 1 <<", "<< last << endl;

	quicksort(arr, piv, lastC);	//1
	quicksort(arr, lastC + 1, last);//4
	return;
}

int main(int argc, char** argv)
{
	
	int ar[10];
	string* array = new string[10];

	//ask 10 eaters how many eaten
	for(int i = 0; i < 10; i++)
	{
		cout << "Enter number of pancakes eater " << i + 1 
			 << " ate: ";
		getline(cin, array[i]);		//get usr input
		stringstream ss(array[i]);	//translate char to int
		ss >> ar[i];

	}

	quicksort(ar, 0, 10);

	//display results

	return 0;
}
