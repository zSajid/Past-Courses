#include<iostream>
using namespace std;


int main()
	{
		int arr[] = {3, 6,2,8,40,0, 2};

		for(int i = 0; i <7; i++)
		{
			cout << arr[i] << " " ;
		}
		cout << endl;

		// Iterate once for each element in the array
		for(int i = 0; i < 6; i++)
			{
				// For each element, start from 0, and iterate again, so the ovearll algorithm should take n^2
				for(int j =0; j < 6; j++)
				{
					if(arr[j] > arr[j+1])
					{
						cout << "Swapping " << arr[j] << " and " << arr[j+1] << endl;
						int temp = arr[j];
						arr[j] =arr[j+1];
						arr[j+1] = temp;
					}
				}

			}

		for(int i = 0; i <7; i++)
		{
			cout << arr[i] << " " ;
		}
		cout << endl;
		
	
	}

