#include <iostream>
#include <fstream>
#include "inputData.h"
#include <gtest/gtest.h>

using namespace std;

int main(int argc, char **argv)
{
	int **x;
	if (check(x)) cout << "Good job!" << endl;
	else cout << "Bad job!" << endl;
	system("pause");
	return 0;
}