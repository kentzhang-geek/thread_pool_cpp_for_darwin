#include "gtest/gtest.h"
#include <iostream>
#include "threadpool.hpp"

static pthread_mutex_t mu;

class thread_A : thread_handle {
public:
	char * xxx;
	thread_A(char *p ) {xxx = p;}
	~thread_A() {
		std::cout << "dectruct  <==  " << this->xxx << std::endl;
	}
	int run_once() {
		sleep(1);
		pthread_mutex_lock(&mu);
		std::cout << "cccc" << this->xxx << std::endl;
		pthread_mutex_unlock(&mu);
		return 0;
	}
};

TEST(thread_pool, 001) {
	thread_pool * s = new thread_pool(3);
	pthread_mutex_init(&mu, NULL);
	s->add_actor("sa", (thread_handle *)(new thread_A("sa\n")));
	s->add_actor("sb", (thread_handle *)(new thread_A("sb\n")));
	s->add_actor("sc", (thread_handle *)(new thread_A("sc\n")));
	s->add_actor("sd", (thread_handle *)(new thread_A("sd\n")));
	s->add_actor("se", (thread_handle *)(new thread_A("se\n")));
	s->add_actor("sf", (thread_handle *)(new thread_A("sf\n")));
	s->add_actor("sg", (thread_handle *)(new thread_A("sg\n")));
	s->add_actor("sh", (thread_handle *)(new thread_A("sh\n")));
	s->add_actor("si", (thread_handle *)(new thread_A("si\n")));
	s->add_actor("s1", (thread_handle *)(new thread_A("s1\n")));
	s->add_actor("s2", (thread_handle *)(new thread_A("s2\n")));
	s->add_actor("s3", (thread_handle *)(new thread_A("s3\n")));
	s->add_actor("s4", (thread_handle *)(new thread_A("s4\n")));
	s->add_actor("s5", (thread_handle *)(new thread_A("s5\n")));
	s->add_actor("s6", (thread_handle *)(new thread_A("s6\n")));
	s->add_actor("s7", (thread_handle *)(new thread_A("s7\n")));
	getchar();
	return ;
}

int main(int argc, char ** argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}
