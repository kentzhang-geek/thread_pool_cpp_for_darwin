/**
 * Do What You Want To Do Lisence
 *
 * Description : Actors in arenas. Seems like thread instances in thread pool.
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

/**
 * inherit this class and overwrite run_once or run_loop to run your code in thread.
 * Also you can overwrite destructor if needed.
 * 
 * Notice that run_loop will only be called once, your should realize your own loop
 * in run_loop if needed
 */
class thread_handle {
public:
	void * thread_ctx;
	char * name;
	int run();
	thread_handle() ;
	virtual ~thread_handle();
	virtual int run_once() {return 0;};
	virtual int run_loop() {return 0;};
};

/**
 * this class realize a thread pool, all thread begin to run once your created pool, 
 * threads will wait for actors require arena
 * Once an actor is ready for play his role, pool will add actor to queue and post a
 * semphore to acknowledge arena. Then arena will get semphore and get an actor from
 * queue to run.
 *
 * Notice : 
 * @param actor_name in method add_actor is not required yet, it will be
 * ignored
 * method remove_actor is empty yet, it will return imediatelly. 
 */
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



