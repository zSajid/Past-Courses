#include <iostream>
#include<string.h>
using namespace std;

// Global
int test1 [3] = {1,2,3}, test2 [6] = {9,2,5,8,29,22}, test3 [9] = {1,3,4,5,6,7,8,9,10};

int max(int left_indx, int right_indx);

int main()
{
    // Variables
    int n = 9;

    cout << max(0, 6) << endl;

    return 0;
}

int max(int left_indx, int right_indx)
    {
     // Variables
     int medium = 0, upperBound = 0, lowerBound = 0, run = 0;

     // Check for the base case; which is that there's only one element in the array or if it's null
     if(right_indx - left_indx == 1)
     {
      return test2[left_indx];
     }
/*
     else if(right_indx - left_indx == 0)
     {
      return NULL;
     }
*/
     medium = ((right_indx +left_indx)/2);
     lowerBound = max(left_indx, medium);
     upperBound = max(medium, right_indx);
     cout << "Upper Bound is " << upperBound << " " << "Lower Bound is " << lowerBound << endl;

     if(lowerBound > upperBound)
     {
       return lowerBound;
     }
     else
     {
        return upperBound;
     }
    }
