#include <iostream>
#include <mutex>
#include <thread>
#include <semaphore.h>

using namespace std;

struct Chopsticks
{
    public:
    	//Mutex for each Chopstick
        sem_t mutex;
};

void eat(Chopsticks &left_chpstk, Chopsticks &right_chpstk, int philosopher_number) {
	
	if(philosopher_number % 2 == 0){  // For Even philosphers
	    sem_wait(&left_chpstk.mutex);
	    sem_wait(&right_chpstk.mutex);
	}else{                            // For odd philosophers
	    sem_wait(&right_chpstk.mutex);
	    sem_wait(&left_chpstk.mutex);
	}

    cout << "Philosopher " << philosopher_number << " is eating ...  \n" << endl;

    chrono::milliseconds timeout(1500);
    this_thread::sleep_for(timeout);

    cout << "Philosopher " << philosopher_number << " has finished eating \n" << endl;

	if(philosopher_number % 2 == 0){ // For Even philosphers
	    sem_post(&right_chpstk.mutex);
    	sem_post(&left_chpstk.mutex);
	}else{							 // For odd philosophers
    	sem_post(&left_chpstk.mutex);
	    sem_post(&right_chpstk.mutex);
	}
}

int main() {
    cout << "----- Dining Philosopher Problem -----\n\n";

	
    int size; //Input number of philosophers
    cout << "Enter number of Philosophers: ";
    cin >> size;
    int no_of_philosophers = size;

    Chopsticks chp[no_of_philosophers]; 	// Create object mutex for each chopstick
    
    thread philosopher[no_of_philosophers]; //Threads for each chopstick
 
    for (int i = 0; i < no_of_philosophers; ++i) {
        sem_init(&chp[i].mutex, 0, 1);  //Initializing each mutex
    }
	
    cout << "Philosopher " << (0 + 1) << " is reading.. \n" << endl;
    philosopher[0] = thread(eat, ref(chp[0]), ref(chp[no_of_philosophers - 1]), (0 + 1)); //Calling for first philosopher

	for (int i = 1; i < no_of_philosophers; ++i) {
        cout << "Philosopher " << (i + 1) << " is reading.. \n" << endl;
        philosopher[i] = thread(eat, ref(chp[i]), ref(chp[(i - 1) % no_of_philosophers]), (i + 1)); //Iteratively calling for each philosopher
    }
	
    for (auto &ph : philosopher) {
        ph.join();
    }

    for (int i = 0; i < no_of_philosophers; ++i) {
        sem_destroy(&chp[i].mutex);
    }

    return 0;
}