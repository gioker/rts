#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iostream>


struct task {
	std::string seq;
	char name;
	int prio;
	int release;
	int current;
	std::string realseq;
};

int main() {
	int blockV = -1;
	int blockQ = -1;
	task tasks[4];
	tasks[0].seq = "EQQQQE";
	tasks[0].prio = 1;
	tasks[0].release = 0;
	tasks[0].current = 0;	
	tasks[0].name = 'a';
	tasks[1].seq = "EE";
	tasks[1].prio = 2;
	tasks[1].release = 2;
	tasks[1].current = 0;	
	tasks[1].name = 'b';
	tasks[2].seq = "EVVE";
	tasks[2].prio = 3;
	tasks[2].release = 2;
	tasks[2].current = 0;	
	tasks[2].name = 'c';
	tasks[3].seq = "EEQVE";
	tasks[3].prio = 4;
	tasks[3].release = 4;
	tasks[3].current = 0;	
	tasks[3].name = 'd';


	int timer = 0;
	int curr;
	while (timer <= 20) {
		curr = -1;
		for (int i = 3; i >= 0; i--) { // finding right task
			if (timer >= tasks[i].release) {
				if (tasks[i].seq[tasks[i].current] == 'E') {
					curr = i;
					break; }
				else if (tasks[i].seq[tasks[i].current] == 'Q') {
					if (blockQ == -1) {
						curr = i;
						blockQ = i;
						break;
					}
					else {
						tasks[i].realseq += 'B';
						curr = blockQ;
						break;
					}
				}
				else if (tasks[i].seq[tasks[i].current] == 'V') {
					if (blockV == -1) {
						curr = i;
						blockV = i;
						break;
					}
					else {
						curr = blockV;
						break;
					}
				}

			}			
		}	
		if (curr >= 0) {
			std::cout << "current: " << tasks[curr].name << " with: " << tasks[curr].seq[tasks[curr].current] << std::endl;
			tasks[curr].realseq += tasks[curr].seq[tasks[curr].current];
			tasks[curr].current++;
			if (blockV == curr && tasks[curr].seq[tasks[curr].current] != 'V')
				blockV = -1;
			if (blockQ == curr && tasks[curr].seq[tasks[curr].current] != 'Q')
				blockQ = -1;
		}
//		std::cout << timer << std::endl; 	

	
		timer++;
	}
	for (int i = 0; i < 4; i++) 
		std::cout << tasks[i].name << " " << tasks[i].realseq << std::endl;
}
