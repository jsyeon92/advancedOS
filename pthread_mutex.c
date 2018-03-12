#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

typedef struct __myarg_t {
	int a;
	int b;
} myarg_t;

typedef struct __myret_t {
	int x;
	int y;
} myret_t;

void *mythread(void *arg){
	myarg_t *m = (myarg_t *) arg;
	int i=0;
	pthread_mutex_t lock;
	int rc= pthread_mutex_init(&lock, NULL);
	assert(rc == 1);
	pthread_mutex_lock(&lock);
	for(i=0; i< 10000; i++){
		m->a++;
	}
	pthread_mutex_unlock(&lock);
	myret_t *r = malloc(sizeof(myret_t));
	r->x =1;
	r->y =2;
	return (void *) r;
}
int main (int argc, char *argv[]) {
	pthread_t p;
	pthread_t l;
	myret_t *m;
	
	myarg_t args = {10, 20};
	pthread_create(&p, NULL, mythread, &args);
	pthread_create(&l, NULL, mythread, &args);
	pthread_join(p, (void **) &m);
	pthread_join(l, (void **) &m);
	
	printf("returned %d %d %d\n", m->x, m->y, args.a);
	free(m);
	return 0;
}
