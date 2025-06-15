// stolen from m1lkweed, 2025

#include <assert.h>

typedef struct example{
	unsigned char co;
}example_t;

#define coroutine(co)                \
	switch(*(co))                \
	case 0:                      \
		if((*(co) = 0)){     \
	default: break;              \
		}else if(!(*(co))--)

#define yield2(co, count)        \
	if(!(*(co) = (count))){  \
	case (count): *(co) = 1; \
	}else

#define yield(co, ret) yield2((co), __COUNTER__ + 2) return ret;

static void example_init(example_t *example) {
	example->co = 0;
}

static unsigned int example_next(example_t *example) {
	coroutine(&example->co){
		yield(&example->co, 1);
		yield(&example->co, 2);
		yield(&example->co, 3);
		yield(&example->co, 99);
	}
	return 0;
}

int main(void){
	example_t example;
	example_init(&example);
	assert(example_next(&example) == 1);
	assert(example_next(&example) == 2);
	assert(example_next(&example) == 3);
	assert(example_next(&example) == 99);
	assert(example_next(&example) == 0);
	assert(example_next(&example) == 0);
	return 0;
}
