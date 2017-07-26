#include <iostream>
#include <string>
#include <sstream>
//#include <cctype>		//isalpha
// #include <stdlib.h>
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

void sortloop(Tracker arr[], Tracker &temp, int &fOpen, int last, 
			  int piv, int &lastC, int &arraySorted)
{
	for(int i = fOpen; i < last; i++)				
		if(arr[i].getval() <= arr[piv].getval()) 	
		{						
			switchtracker(temp, arr, i, fOpen);
			lastC = fOpen;		//[1] becomes lastC, lastC = 1
			fOpen = lastC + 1;  //fOpen becomes 2

			arraySorted = 1;	//this subarray is not sorted, more quicksort calls needed
		}

		else if(arr[i].getval() < arr[i - 1].getval()) //piv==min, but array not sorted (0,6,5,4,4,3)
				arraySorted = 1;

		else
			continue;
}

void quicksort(Tracker arr[], int piv, int last)
{
	Tracker temp;
	int arraySorted = 0; //0 = true. can be set to false during for

	if(last - piv <= 1)	//list is done sorting for subarray size 1
		return;

	int fOpen = piv + 1, lastC = -1; //first opened is 1 after piv
									//last closed hasnt happened yet
	
	sortloop(arr, temp, fOpen, last, piv, lastC, arraySorted);

	if(arraySorted == 0)	//subarray sorted
		return;

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


void display(Tracker ar[], int length)
{
	for(int i = length - 1; i >= 0; i--)
		cout <<"Eater " << ar[i].getid() <<" ate "<< ar[i].getval() 
			<< " pancakes." << endl;
	return;
}	// display()


int loopInput(string &input, int length)
{
	int i;
	for(i = 0; i < length; i++)
		if(!isdigit(input[i]))
			break;
	return i;
}

void prompt(string &input, int i)
{
	cout << "Enter number of pancakes eater " << i + 1 
			 << " ate: ";
			 						//getline must use string type, no char arr hahah
	getline(cin, input);		//get usr input
}


void checkInput(string &input, int i)
{
	int length = input.length();
	int check = loopInput(input, length);
	while(length < 1 || check != length ) //broke b4 end of string
	{
		cout << "Invalid number. Must enter at least one digit and only digits." <<endl;
		prompt(input, i);
		length = input.length();
		check = loopInput(input, length);		

	}
}


int main(int argc, char** argv)
{
	int val, eaters;

	//Tracker ar[10];
	Tracker temp;
	string input;

	//ask how many eaters
	cout << "Enter the number of eaters that participated in the contest: ";
	getline(cin, input);
	stringstream ss1(input);
	ss1 >> eaters;

	Tracker* ar = new Tracker[eaters];

	//use new to allocate for Tracker ar[]

	for(int i = 0; i < eaters; i++)
	{
		prompt(input, i);
		checkInput(input, i);
		stringstream ss2(input);	//translate char to int
		ss2 >> val;
		Tracker track(i + 1, val);
		ar[i] = track; 
	}

	quicksort(ar, 0, eaters);	//sort by largest num pancakes (val)
	display(ar, eaters);			//display results
	cout <<"-----------------------------"<<endl;
	return 0;
}
