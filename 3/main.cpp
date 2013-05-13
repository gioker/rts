#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

std::mutex mtx;
std::thread* timer;

int readSensors() {
	printf("reading sensors...\n");
	return 5;
	
}
int CalculateNewSetValues() {
	printf("calculating values...\n");
}
	
void ActuateProcess() {
}

void WaitForNextCycle() {
	mtx.lock();
	printf("waiting for new Cycle\n");
}

void Error() {
}

void ThreadTimer()
{
	while(1) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		printf("Clock Tick\n");
		mtx.unlock();
	}
}

void initializeClock() {
	timer = new std::thread(&ThreadTimer);
}

int main (void){
	int state1, state2, staten;
	initializeClock();
	while(1){
		readSensors();
		if (CalculateNewSetValues())
			ActuateProcess();
		else
		Error();
		
		WaitForNextCycle();
	}
	return 0;
}
