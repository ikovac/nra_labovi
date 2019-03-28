#include <iostream>
#include <thread>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// A dummy function 
void sum(int start, int end, int *arr, int *sum)
{
	unsigned long int local_sum = 0;
	int i = 0;

	for (i = start; i < end; i++) {
		local_sum += arr[i];
	}

	*sum = local_sum;
}

int RandomNumberGenerator(void);

int main()
{
	srand(time(NULL));
	int myArray[40000] = { 0 };
	int i = 0;
	int sum1 = 0;
	int sum2 = 0;
	float average = 0;

	for (i = 0; i < 40000; i++) {
		myArray[i] = RandomNumberGenerator();
	}

	thread th1(sum, 0, 20000, myArray, &sum1);
	thread th2(sum, 20000, 40000, myArray, &sum2);

	// Wait for the threads to finish
	th1.join();
	th2.join();

	average = (float)(sum1 + sum2) / 40000;
	cout << "Average: " << average << endl;

	return 0;
}

int RandomNumberGenerator()
{
	int randomNumber = 0;

	randomNumber = rand() % (6 - 1) + 1;

	return randomNumber;
}