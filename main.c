#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int integers[100];
int avg, min, max;
pthread_t tid;

void threadControl() {
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
}

void *findAvg(void *arg) {
	threadControl();
	int len = *(int *)arg-1;
	int sum = 0;
	for (int i=0; i<len; i++) {
		sum = sum + integers[i];
	}
	avg = sum/(len);
        pthread_exit(NULL);
}

void *findMin(void *arg) {
	threadControl();
	int len = *(int *)arg-1;
	min = integers[0];
	for (int i=1; i<len; i++) {
		if (integers[i] < min) {
			min = integers[i];
		}
	}
	pthread_exit(NULL);
}

void *findMax(void *arg) {
	threadControl();
	int len = *(int *)arg-1;
	max = integers[0];
	for (int i=1; i<len; i++) {
		if (integers[i] > max) {
			max = integers[i];
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	for (int i=1; i<argc; i++) {
		integers[i-1] = atoi(argv[i]);
	}

	int avgFunc = pthread_create(&tid, NULL, findAvg, &argc);
	threadControl();
	sleep(1);
	pthread_join(tid, NULL);
	printf("The average value is %d\n", avg);

	int minFunc = pthread_create(&tid, NULL, findMin, &argc);
	threadControl();
	sleep(1);
	pthread_join(tid, NULL);
	printf("The minimum value is %d\n", min);

	int maxFunc = pthread_create(&tid, NULL, findMax, &argc);
	threadControl();
	sleep(1);
	pthread_join(tid, NULL);
	printf("The maximum value is %d\n", max);

	exit(0);
}
