using System;

class StringReversal{
	static int Main(){
		char[] input = {'b', 'a', 'r', 'b', 'e', 'd'};

		stringReverse (input);

		for (int i = 0; i < 6; i++) {
			Console.Write (input [i] );
		}
		return 0;

	}

	static void stringReverse(char [] arr, int w = 6){



		for(int i = 0, j = w-1; i < w/2; i++, j--){
			char tmp = arr [j];
			arr [j] = arr [i];
			arr [i] = tmp;
		}

	}


}
