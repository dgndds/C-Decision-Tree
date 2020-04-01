#include <stdio.h>
#include <iostream>
#include "Calculate.h"

using namespace std;

int main( int argc, const char* argv[] )
{
    int arr[3] = {32,0,7};

	cout << calculateEntropy(arr,3) << endl;

	return 0;

}
