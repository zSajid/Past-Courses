#include<iostream>
using namespace std;

int test3[6] = {3, 4, 1, 230, 400, 33};
int test4[20] = {3, 4, 1, 230, 400, 33, 999, 57, 67, 97, 87, 45, 23, 55, 0, 2222, 365, 555, 666 , 777};
int test5[4] = {3,4,92420,230};
void mergeSort(int arr[], int left_indx, int right_indx);
void merge(int arr[], int left_indx, int medium, int right, int size);

int main()
    {
     int length = 20;
     mergeSort(test4, 0, 20);

      for(int i = 0; i < length; i++)
      {
        cout << test4[i] << " ";
      }
     return 0;
    }

void mergeSort(int arr[], int left_indx, int right_indx)
    {
     int length = right_indx, bz = 0, low = 0;

     // Loop through the array based on the block size
        // For every time the block size increases by 1, that's how much the second for loop will increase in terms of the comparisons
     for( bz = 1; bz < length; bz = 2*bz)
        {
         for( low = 0; low < (length - bz); low += (bz+bz))
         {
           // Merge the array, the lower length as the starting position within the array, so it focuses on the starting of the width, and the stopping index being the stopping point of the accumlation of low and bz
           int medium = low+bz-1;
           int rightBZ =0;

            // Check to see what value is less, and to set it up as the right block size ending value
           if(low+bz+bz-1 < length- 1)
           {
            rightBZ = low+bz+bz-1;
           }

           else
           {
            rightBZ = length-1;
           }

           // After breaking the blocks into pieces that are related to its size, then merge them together into order.
           merge(arr,low, medium, rightBZ, right_indx);
         }
        }
    }

void merge(int arr[], int left_indx, int medium, int right, int size)
    {
     // Variables
     int * tmpArray = new int [size];
     int start = left_indx, j = 0;

     // This prints out the information of what portion of the arrays are being manipulated
     for(int i = left_indx; i <= right; i++)
     {
         cout << arr[i] << " " ;
     }
     cout << endl;

     for(start = left_indx; start <= medium; start++)
     {
         tmpArray [start] = arr[start]; // Copy over the values from the real array with the values that are given in from left index until the middle
     }

     for(int j = medium +1; j <= right; j++) // Then copy over the values from medium +1, because medium was copied over till the end, which is right_indx
     {
      tmpArray [j] = arr[right-j+medium+1];
     }

     // Reset variable locations, and set j to the very end, rather than medium
     start = left_indx, j = right;

     // Loop through the block sizes from the left index to the end of the right one, and switch them depending on what's needed.
     for(int newStart = left_indx; newStart <= right; newStart++)
     {
         if(tmpArray [j] < tmpArray [start])
         {
            arr[newStart] = tmpArray [j--];
         }

         else
         {
             arr[newStart] = tmpArray [start++];
         }
     }

     // Delete the allocation array and set the pointer to null
     delete tmpArray ;

     tmpArray = NULL;
    }

