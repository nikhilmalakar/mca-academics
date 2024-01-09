#include <iostream>
#include <mutex>
#include <thread>
#include <semaphore.h>

using namespace std;

struct Fork
{
    public:
    	//Mutex for each fork
        sem_t mutex;
};

void eat(Fork &left_fork, Fork &right_fork, int number) {
	
    sem_wait(&left_fork.mutex);
    sem_wait(&right_fork.mutex);

    cout << "Philosopher " << number << " is eating" << endl;

    chrono::milliseconds timeout(1500);
    this_thread::sleep_for(timeout);

    cout << "Philosopher " << number << " has finished eating" << endl;

    sem_post(&right_fork.mutex);
    sem_post(&left_fork.mutex);
}

int main() {
	
    int philosophers = 10;

    Fork fk[philosophers];
    thread philosopher[philosophers];

    for (int i = 0; i < philosophers; ++i) {
        sem_init(&fk[i].mutex, 0, 1);
    }

    cout << "Philosopher " << (0 + 1) << " is reading.." << endl;

    philosopher[0] = thread(eat, ref(fk[0]), ref(fk[philosophers - 1]), (0 + 1));

    for (int i = 1; i < philosophers; ++i) {
        cout << "Philosopher " << (i + 1) << " is reading.." << endl;
        philosopher[i] = thread(eat, ref(fk[i]), ref(fk[(i - 1) % philosophers]), (i + 1));
    }

    for (auto &ph : philosopher) {
        ph.join();
    }

    for (int i = 0; i < philosophers; ++i) {
        sem_destroy(&fk[i].mutex);
    }

    return 0;
}