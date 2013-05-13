#include <iostream>
#include <semaphore.h>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
using namespace std;
sem_t mutex;

#define PI 3.14159265



class Task {
public:
    Task(int);
protected:
    int T; // period in ms
public:
        friend void *timer_main( void * task);
        friend void *execute_main( void * task);
        virtual void execute() = 0;// abstract class
protected:
        /* Function to block the Process until next tick */
        void waitForNextCycle() {  }
};

void *timer_main( void * task) {
	while(true) {
		sem_post(&mutex);
		usleep(1000000);
	}
}
void *execute_main( void * task) {
        cout << "Start execution ...." <<endl;
        Task *t = (Task *) task;
        t->execute();
        return NULL;
}
// Construktor starts threads:
Task::Task(int t=1000): T(t) {
        pthread_t timerthread;
        pthread_t executethread;
        
        pthread_create( &timerthread, NULL, &timer_main, (void *) this );
        pthread_create( &executethread, NULL, &execute_main, (void *) this );
};

class Display : public Task {
public:
        Display(int T): Task(T) {};
        void execute();
};
void Display::execute() {
        cout << "... Display::execute T=" << T << endl;
        sem_post(&mutex); // don't start without me!
        while( true )
        {
                // critical region:
                sem_wait(& mutex);              
 //               p.display("P= ");
  //              cout << "Abstand =" << (int) Abstand(p, Ldir) << endl << endl;
		cout << "Display execute..." << endl;
                sem_post(& mutex);
                waitForNextCycle();
        }
}
class point {
private:
	int x;
	int y;
public:
	point() {
		x = 0;
		y = 0;
	};
	move(int v, int D) {
		x += (int) v * cos(D*PI/180);
		y += (int) v * sin(D*PI/180);
	}
};


class Fahren : public Task {
public:
        Fahren(int T, int v, int d): Task(T), V(v), D(d) {};
        void execute();
private:
        int V; // speed
        int D; // direction
};
void Fahren::execute() {
	cout << test << endl;
        while( true ) {
                // simulate moving the vehicle:         
                sem_wait(& mutex); // enter critical region     
                // compute distance travelled during period
                double realV = (T * V) / 1000.0;
                p.move(realV, D);
                //sem_post(& mutex); // end critical region
                // calculateNewSetValue() and actuateProcess():
                int entf =  0;// Abstand(p, Ldir);
                const int deltha = 1;
                if (entf > 0) 
                        D += deltha;
                else if (entf < 0)
                		D = deltha;      
                waitForNextCycle();
        }
}

int main( int argc, char *argv[] )
{
//        InitAll(45); // direction of line [0, 90]
        usleep(1000);
        Display D(); 
        cout << "Los geht's!!" << endl;
        Fahren F(1000/* period in ms */ , 
  /* speed in pixels per second */15 , 
  /* start direction [0, 90] */ 0 );
	F.execute();
        // sleep forever:
        sem_t block;
        sem_init( &block, 0, 0 );
        sem_wait( &block );
        
        return 0;
}

