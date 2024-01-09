// producer consumer using semaphore
#include <iostream>
#include <queue>
#include <thread>
#include <semaphore.h>
using namespace std;
queue<int> buffer;
sem_t empty;
sem_t full;
sem_t mutex;


//Producer Function
void produce() {
   for (int i = 1; i <=5; ++i) {
   	
      sem_wait(&empty);
      sem_wait(&mutex);
      buffer.push(i);
      
      cout << "Produced : Item " << i << endl;
      sem_post(&mutex);
	  sem_post(&full);
	  
      this_thread::sleep_for(chrono::milliseconds(500));
   }
}


//Consumer Function
void consume() {
   while (true) {
   	
      sem_wait(&full);
      sem_wait(&mutex);
      int data = buffer.front();
      buffer.pop();
      
      cout << "Consumed : Item " << data << endl;
      sem_post(&mutex);
      sem_post(&empty);
      
      this_thread::sleep_for(chrono::milliseconds(1000));
   }
}

int main() {
	
	cout<<"----- Producer Consumer Problem -----\n\n";
	int size = 0;
	cout<<"Enter buffer size : ";
	cin>>size;
	cout<<endl;
	
   sem_init(&empty, 0, size);  
   sem_init(&full, 0, 0);  
   sem_init(&mutex, 0, 1);

   thread producerThread(produce);
   thread consumerThread(consume);

   producerThread.join();
   consumerThread.join();

   sem_destroy(&empty);
   sem_destroy(&full);

   return 0;
}

