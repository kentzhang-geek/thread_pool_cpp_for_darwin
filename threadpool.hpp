/**
 * Do What You Want To Do Lisence
 */

#ifndef __CPP_THREAD_POOL_TRY_TO_WRITE__
#define __CPP_THREAD_POOL_TRY_TO_WRITE__

#include <pthread.h>
#include <vector>
#include <map>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <stdio.h>

class thread_handle {
public:
	void * thread_ctx;
	char * name;
	int run();
	thread_handle();
	virtual int run_once() {return 0;};
	virtual int run_loop() {return 0;};
};

class thread_pool {
protected:
	std::map<char *, thread_handle *> * actors;
	std::vector<thread_handle *> * queue;
	std::vector<pthread_t *> * arena;
	pthread_mutex_t pool_lock;
	sem_t * actor_dispatcher;
public:
	thread_pool(int num_of_arena);
	~thread_pool();
	int add_actor(char * actor_name, thread_handle *x);
	int remove_actor(char * actor_name);
	int wait_actor() {
		return sem_wait(this->actor_dispatcher);
	}
	int post_actor() {
		return sem_post(this->actor_dispatcher);
	}
	thread_handle * require_actor();
};

#endif



