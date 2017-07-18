/*

List of Authors:

1. Eashan Trehan
2. Ellen Qiu
3. Wan Fang
4. Wang Tiankai

Advisory: Research on technical terms like 'mutation', 'crossover', 'fitness', 'selection' or write to eashan12trehan@gmail.com 

*/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>

using namespace std;

string notes[14] = {" ", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"}; // Storing musical notes in an array 

void printParent( int parent[][8], int fitnessParent[4]) // Function for printing the parent
{
	for(int i =1; i<4; i++)
	{
		cout<<"Parent no. "<<i<<": ";

		for(int j=1; j<8; j++)
			cout<<notes[parent[i][j]]<<" ";

		cout<<endl<<"Fitness = "<<fitnessParent[i]<<endl<<endl;
	}
}

void printResult( int parent[][8], int fitnessParent[4], int k) // Function for printing the final result
{
	cout<<"generation: "<<k<<endl;

	for(int i =1; i<4; i++)
	{
		cout<<i<<": ";

		for(int j=1; j<8; j++)
			cout<<notes[parent[i][j]]<<" ";

		cout<<endl<<"Fitness = "<<fitnessParent[i]<<endl<<endl;
	}
}

int fitness(const int &a, const int &b) // Function for evaluating the fitness of an offspring/parent
{
	int c = abs(a - b);

	switch(c)
	{
		case 12: return 2;
		case 5:
		case 7: return 1;
		case 0:
		case 3:
		case 4:
		case 8:
		case 9: return 0;
		case 2:
		case 6:
		case 10: return -1;
		case 1: 
		case 11: return -2;
	}

	return 0;
}

void mutation(int genes[8]) // Function to carry out 'mutation'
{
	int pos = rand()%8;

	if(genes[pos]!=13)
		genes[pos]++;
	
	else
		genes[pos] = 1;
}

void crossover(int o1[8], int o2[8]) // Function to carry out 'crossover'
{
	int pos = rand()%8;
	bool flag = false;

	while(flag==false)
	{
		if(o1[pos]!=o2[pos])
		{
			int temp;

			temp = o1[pos];
			o1[pos] = o2[pos];
			o2[pos] = temp;
			
			flag = true;
		}

		else
			pos = rand()%8;
	}
}

void fitUpdate( int parent[][8], int offspring[][8], int fitnessParent[4], int fitnessoffspring[4]) // Function to update the 'fitness'
{
	for(int i=1; i<4; i++)
	{
		int fitparent = 0;
		int fitoffspring = 0;

		for(int j=0; j<7; j++)
		{
			fitparent+= fitness(parent[i][j], parent[i][j+1]);
			fitoffspring += fitness(offspring[i][j], offspring[i][j+1]);
		}

		fitnessParent[i] = fitparent;
		fitnessoffspring[i] = fitoffspring;
	}
}

void selection( int parent[][8], int offspring[][8], int fitnessParent[4], int fitnessoffspring[4]) // Function to carry out 'selection'
{
	int fitness[8];

	for(int i=1; i<4; i++)
	{
		fitness[i] = fitnessParent[i];
		fitness[i+4] = fitnessoffspring[i];
	}

	sort(fitness, fitness+8);

	int temp = 0;
	int tempparent[4][8];

	for(int i=1; i<4; i++)
	{
		bool flag = false;

		for(int j=5; j<8 && temp<4 && !flag; j++)
		{
			if(fitnessParent[i]==fitness[j])
				{
					for(int k =1; k<8; k++)
						tempparent[temp][k] = parent[i][k];

					temp++;
					flag = true;

		}
	}
}

	for(int i=1; i<4; i++)
	{
		bool flag = false;

		for(int j=5; j<8 && temp<4 && !flag; j++)
		{
			if(fitnessoffspring[i]==fitness[j])
				{
					for(int k =1; k<8; k++)
						tempparent[temp][k] = parent[i][k];

					temp++;
					flag = true;

		}
	}
}

	for(int i=1; i<4; i++)
		for(int j=1; j<8; j++)
			parent[i][j] = tempparent[i][j];

}

void genetic( int parent[][8], int offspring[][8], int fitnessParent[4], int fitnessoffspring[4]) // Function for generating the offspring
{
	for(int i=1; i<4; i++)
		if(rand()%2==0)
			mutation(offspring[i]);

	for(int i=1; i<2; i++)
		if(rand()%2==0)
			crossover(offspring[2*i], offspring[2*i+1]);

	fitUpdate(parent, offspring, fitnessParent, fitnessoffspring);
	selection(parent, offspring, fitnessParent, fitnessoffspring);
	fitUpdate(parent, offspring, fitnessParent, fitnessoffspring);
}

void initial(int parent[][8], int offspring[][8], int fitnessParent[4], int fitnessoffspring[4]) // Function for initialising & creating the first parent
{
	for(int i=1; i<4; i++)
		for(int j=1; j<8; j++)
			parent[i][j] = rand()%12+1;

	for(int i=1; i<4; i++)
		for(int j=1; j<8; j++)
			offspring[i][j] = parent[i][j];

	fitUpdate(parent, offspring, fitnessParent, fitnessoffspring);
}

int main()
{
	int parent[4][8];
	int offspring[4][8];
	int fitnessParent[4];
	int fitnessoffspring[4];
	int i;
	
	srand(time(NULL));

	initial(parent, offspring, fitnessParent, fitnessoffspring);
	printParent(parent, fitnessParent);

	for(i=1; i<10000; i++)
	{
		genetic(parent, offspring, fitnessParent, fitnessoffspring);

		if(i==10000)
			printResult(parent, fitnessParent, i);
	}

	printResult(parent, fitnessParent, i);
	system("pause");

	return 0;
}