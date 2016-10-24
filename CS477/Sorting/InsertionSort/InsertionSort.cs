using System;

class InsertionSort{
	static int Main(){
		int[] list = { 33, 1, 3, 2, 49, 300, 200 };

		for (int i = 1; i < list.Length; i++) {
			int val = list [i];
			int j = i - 1;

			while(j >= 0 && (val <= list[j])){
				list [j + 1] = list [j];
				j--;
			}

			list [j+1] = val;

		}

		for (int i = 0; i < list.Length ; i++) {
					Console.Write (list [i] + " ");
				}
				Console.WriteLine ();
	
	
			return 0;
		}

	}

