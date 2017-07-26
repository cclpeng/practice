#include <iostream>
#include <string>
#include <sstream>
#include <cctype>		//isalpha
#include <stdlib.h>
using namespace std;


//for 10 ppl, supposed to enter number of pancakes each person eats
//then display which person ate mostpancakes down to which person ate
//least pancakes
struct Tracker
{
	private:
		int id;
		int val;
	public:
		Tracker(){}				//default constructor for array makin
		Tracker(int identity, int value);//constructor
		Tracker(const Tracker &source);	//copy constructor
		int getval();
		int getid();
		//dont put here.void quicksort(Tracker ar[], int piv, int last);
};

Tracker::Tracker(int identity, int value)
{
	id = identity;
	val = value;
}	// general constructor

Tracker::Tracker(const Tracker &source)
{
	//left hand side is Tracker::Tracker, rhs is source
	id = source.id;
	val = source.val;
}	// copy constructor

int Tracker::getval() { return val; }

int Tracker::getid() { return id; } 

void switchtracker(Tracker &temp, Tracker arr[], int pos1, int pos2)
{
	temp = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = temp;
	return;
} // switch()

void quicksort(Tracker arr[], int piv, int last)
{
	Tracker temp;
	int arraySorted = 0; //0 = true. can be set to false during for

	if(last - piv <= 1)	//list is done sorting for subarray size 1
		return;

	int fOpen = piv + 1, lastC = -1; //first opened is 1 after piv
									//last closed hasnt happened yet
	for(int i = fOpen; i < last; i++)				//3, 4, 1, ...
		if(arr[i].getval() <= arr[piv].getval()) 	//i=2, piv=0, ([2]=1 < [0]=3)
		{						//fOpen=1, lastC=-1
			// temp = arr[i];	//[1]=4 -> 1, [2]=4
			// arr[i] = arr[fOpen];	
			// arr[fOpen] = temp;	//3, 1, 4, ...
			switchtracker(temp, arr, i, fOpen);
			lastC = fOpen;		//[1] becomes lastC, lastC = 1
			fOpen = lastC + 1;  //fOpen becomes 2

			arraySorted = 1;	//this subarray is not sorted, more quicksort calls needed
		}

		else if(arr[i].getval() < arr[i - 1].getval()) //piv==min, but array not sorted (0,6,5,4,4,3)
				arraySorted = 1;

		else
			continue;
	

	if(arraySorted == 0)	//subarray sorted
		return;
//4321 --> 1324 --> 
	//must also deal w lastC not changed

	if(lastC == -1)	//nothing closed, fOpen is still piv+1
	{	//then we should keep piv in same place...
		piv += 1;
		quicksort(arr, piv, last);
		return;
	}

	switchtracker(temp, arr, piv, lastC);
	
	quicksort(arr, piv, lastC);	//1
	quicksort(arr, lastC + 1, last);//4
	
	return;
} // quicksort()


void display(Tracker ar[])
{
	for(int i = 10-1; i >= 0; i--)
		cout <<"Eater " << ar[i].getid() <<" ate "<< ar[i].getval() 
			<< " pancakes." << endl;
	return;
}	// display()


int main(int argc, char** argv)
{
	int val;
	Tracker ar[10];
	Tracker temp;
	string input;

	//ask 10 eaters how many eaten
	for(int i = 0; i < 10; i++)
	{
		cout << "Enter number of pancakes eater " << i + 1 
			 << " ate: ";
			 						//getline must use string type, no char arr hahah
		getline(cin, input);		//get usr input
		stringstream ss(input);	//translate char to int
		ss >> val;
		Tracker track(i + 1, val);
		ar[i] = track; 
	}

	// for(int i = 0; i < 10; i++)
	// 	cout << ar[i].getval() <<", ";
	// cout << endl; 

	quicksort(ar, 0, 10);	//sort by largest num pancakes (val)
	display(ar);			//display results
	cout <<"-----------------------------"<<endl;
	return 0;
}

//test for quicksort
//7, 3, 5, 1008201
//5,2,1,5,7,8,0,0,0,34
//9,8,7,6,5,4,3,2,1,0
//	087654321 9
//  