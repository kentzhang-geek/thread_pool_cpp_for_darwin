/**
 * Do What You Want To Do Lisence
 */

#include "test.hpp"

/**
 * this method runs thread main method
 * @return error code
 */
int thread_handle::run() {
	int ret;
	ret = this->run_once();
	ret |= this->run_loop();

	return ret;
}

/**
 * Init with name allocated
 */
thread_handle::thread_handle() {
	this->name = (char *)malloc(100);
	bzero(this->name, 100);
}

/**
 * c fucntions that get actors move
 * @param  p thread pool instance
 * @return   unused
 */
void * pthread_arena(void *p) {
	thread_pool * pool = (thread_pool *)p;
	thread_handle * actor_get = NULL;

	do
	{
		actor_get = pool->require_actor();
		if (NULL != actor_get)
			actor_get->run();
	} while (NULL != actor_get);

	pthread_exit(NULL);
}

/**
 * create thread pool with max number of threads
 */
thread_pool::thread_pool(int num_of_arena) {
	pthread_t * arena_tmp = NULL;
	int i;
	char * dispatcher_name = (char *)malloc(100);

	// init components
	this->queue = new std::vector<thread_handle *>();
	this->arena = new std::vector<pthread_t *>();
	this->actors = new std::map<char *, thread_handle *>();
	bzero(dispatcher_name, 100);
	snprintf(dispatcher_name, 100, "dispatcher_name_%p", this);
	pthread_mutex_init(&pool_lock, NULL);
	perror("");
	actor_dispatcher = sem_open(dispatcher_name, O_CREAT, O_RDWR, 0);
	perror(dispatcher_name);

	// create thread
	for (i = 0; i < num_of_arena; i++) {
		arena_tmp = (pthread_t *)malloc(sizeof(pthread_t));
		bzero(arena_tmp, sizeof(pthread_t));
		pthread_create(arena_tmp, NULL, pthread_arena, (void *)this);
	}

	return;
}

/**
 * delete this thread pool
 */
thread_pool::~thread_pool() {
	sem_close(this->actor_dispatcher);
	delete this->actors;
	delete this->arena;
	delete this->queue;

	return;
}

/**
 * input an actor into thread arena
 * @param  actor_name name of actor, using this string find actor
 * @param  x          instance of actor
 * @return            error code
 */
int thread_pool::add_actor(char * actor_name, thread_handle *x) {
	pthread_mutex_lock(&this->pool_lock);
	strcpy(x->name, actor_name);
	this->actors->insert(std::pair<char *, thread_handle *>(actor_name, x));
	this->queue->push_back(x);
	pthread_mutex_unlock(&this->pool_lock);
	return sem_post(this->actor_dispatcher);
}

/**
 * require an actor , use in c threads
 * @return actor required
 */
thread_handle * thread_pool::require_actor() {
	if (0 != this->wait_actor()) {
		return NULL;
	}

	pthread_mutex_lock(&this->pool_lock);
	thread_handle * ret = (*this->queue)[0];
	this->queue->erase(this->queue->begin());
	this->actors->erase(ret->name);
	pthread_mutex_unlock(&this->pool_lock);
	return ret;
}
