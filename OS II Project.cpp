#include<iostream>
#include <queue>
#include <cstdio>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

void printQueue(queue<int> q){
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}
void printVector(vector<int> const& myVec) {
	for (int i = 0; i < myVec.size(); i++)
		cout << myVec.at(i) << ' ';
	cout << endl;
}
const int constSize = 100;
int Length_of_string;
int FrameSize;
int checkerArr[constSize];
int myPages[constSize];
 
void FIFO(void)
{
	queue<int> myQueue;
	int PageFaults = 0;

	for (int x = 0; x < Length_of_string; x++){
		if (checkerArr[myPages[x]] == true){
			cout << myPages[x] << " No Page Fault this number is already inserted in the memory\n";
		}
		else{
			myQueue.push(myPages[x]);
			checkerArr[myPages[x]] = true;
			if (myQueue.size() > FrameSize)
			{
				int p = myQueue.front();
				checkerArr[p] = false;
				myQueue.pop();
			}
			PageFaults++;
			cout <<  myPages[x] << " caused a page fault\n";
		}
	}
	cout << "\nTotal Page Faults: " << PageFaults<<endl;
	cout << "Content of the frames in the final stage: ";
	printQueue(myQueue);
	return;
}

void LRU()
{
	unordered_set<int> u_set;
	unordered_map<int, int> u_map;

	int page_faults = 0;
	for (int x = 0; x < Length_of_string; x++){
		if (u_set.find(myPages[x]) != u_set.end()){
			cout << myPages[x] << " No Page Fault this number is already inserted in the memory\n";
		}
		else{
			if (u_set.size() <  FrameSize){
				u_set.insert(myPages[x]);
				page_faults++;
			}
			else{
				int lru = INT_MAX, value;
				for (auto it : u_set){
					if (u_map[it] < lru){
						lru = u_map[it];
						value = it;
					}
				}
				u_set.erase(value);
				u_set.insert(myPages[x]);
				page_faults++;
			}
			cout  << myPages[x] << " caused a page fault\n";
		}
		u_map[myPages[x]] = x;
	}
	cout << "\nTotal Page Faults: " << page_faults<<endl;
	cout << "Content of the frames in the final stage:  ";
	unordered_set<int> ::iterator i;
	for (i = u_set.begin(); i != u_set.end(); i++)
		cout << (*i) << " ";
	cout << endl;
}

void Optimal()
{
	vector<int> myVector;
	int PageFault = 0;
	for (int x = 0; x < Length_of_string; x++)
	{
		int z;
		for (z = 0; z < myVector.size(); z++)
			if (myVector[z] == myPages[x])
				break;
		if (z == myVector.size())
		{
			if (myVector.size() < FrameSize)
				myVector.push_back(myPages[x]);

			else
			{
				int indx = x + 1;
				int res = -1, far = indx;
				for (int a = 0; a < myVector.size(); a++)
				{
					int b;
					for (b = indx; b < Length_of_string; b++)
					{
						if (myVector[a] == myPages[b])
						{
							if (b > far)
							{
								far = b;
								res = a;
							}
							break;
						}
					}
					if (b == Length_of_string)
					{
						res = a;
						break;
					}
				}
				myVector[res] = myPages[x];
			}
			PageFault++;
			cout <<  myPages[x] << " caused a page fault\n";
		}
		else
		{
			cout  << myPages[x] << " No Page Fault this number is already inserted in the memory\n";
		}
	}
	cout << "\nTotal Page Faults: " << PageFault<<endl;
	cout << "Content of the frames in the final stage: ";
	printVector(myVector);
}


int main()
{
	char cont;
	do {
		cout << "Number of Frames: ";
		cin >> FrameSize;

		cout << "Enter the Length of Page Reference String: ";
		cin >> Length_of_string;

		cout << "Enter the Page Reference String Numbers:\n";
		for (int i = 0; i < Length_of_string; i++)
			cin >> myPages[i];

		cout << "Which Algorithim you want to use?\n Choose from the following:\n 1 FIFO\n 2 LRU\n 3 Optimal\n";
		int algo;
		cin >> algo;
		if (algo == 1) {
			cout << "You Chose FIFO Algorithim\n";
			FIFO();
		}
		else if (algo == 2) {
			cout << "You Chose LRU Algorithim\n";
			LRU();
		}
		else if (algo == 3) {
			cout << "You Chose Optimal Algorithim\n";
			Optimal();
		}
		else {
			cout << "Wrong choice!!\n";
		}
		cout << "Press c to restrat the program\n";
		cin >> cont;
		system("CLS");

	} while (cont == 'c');
	
}
