#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;
int P;
int *v;
int *vQSort;
pthread_barrier_t barrier;

int min(int a, int b) {
  if (a <= b) return a;
  return b;
}

void compare_vectors(int *a, int *b) {
	int i;

	for (i = 0; i < N; i++) {
		if (a[i] != b[i]) {
			printf("Sortare incorecta\n");
			return;
		}
	}

	printf("Sortare corecta\n");
}

void display_vector(int *v) {
	int i;
	int display_width = 2 + log10(N);

	for (i = 0; i < N; i++) {
		printf("%*i", display_width, v[i]);
	}

	printf("\n");
}

int cmp(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return A - B;
}

void get_args(int argc, char **argv)
{
	if(argc < 3) {
		printf("Numar insuficient de parametri: ./oets N P\n");
		exit(1);
	}

	N = atoi(argv[1]);
	P = atoi(argv[2]);
}

void init()
{
	int i;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);

	if (v == NULL || vQSort == NULL) {
		printf("Eroare la malloc!");
		exit(1);
	}

	srand(42);

	for (i = 0; i < N; i++)
		v[i] = rand() % N;
}

void print()
{
	printf("v:\n");
	display_vector(v);
	printf("vQSort:\n");
	display_vector(vQSort);
	compare_vectors(v, vQSort);
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;

	// implementati aici OETS paralel
  int start = thread_id * (double) N / P;
  int end = min(N, (thread_id + 1) * (double) N / P);
  
  int start_even, start_odd, aux;
  if (start % 2 == 1) {
    start_even = start + 1;
    start_odd = start;
  } else {
    start_even = start;
    start_odd = start + 1;
  }
  
  for (int k = 0; k < N; k++) {
  	for (int i = start_even; i < end && (i < N - 1); i++) {
  		if (v[i] > v [i + 1]) {
  			aux = v[i];
			v[i] = v[i + 1];
			v[i + 1] = aux;
  		}
  	}
  	pthread_barrier_wait(&barrier);
  	for (int j = start_odd; j < end && (j < N - 1); j++) {
		if (v[j] > v [j + 1]) {
  			aux = v[j];
			v[j] = v[j + 1];
			v[j + 1] = aux;
  		}
  	}
  	pthread_barrier_wait(&barrier);
  }
  
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	get_args(argc, argv);
	init();

	int i, aux;
	pthread_t tid[P];
	int thread_id[P];
	pthread_barrier_init(&barrier, NULL, P);
	// se sorteaza vectorul etalon
	for (i = 0; i < N; i++)
		vQSort[i] = v[i];
	//qsort(vQSort, N, sizeof(int), cmp);

	// se creeaza thread-urile
	for (i = 0; i < P; i++) {
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	// se asteapta thread-urile
	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	pthread_barrier_destroy(&barrier);
	// bubble sort clasic - trebuie transformat in OETS si paralelizat
	/*int sorted = 0;
	while (!sorted) {
		sorted = 1;

		for (i = 0; i < N-1; i++) {
			if(v[i] > v[i + 1]) {
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sorted = 0;
			}
		}
	}*/

	// se afiseaza vectorul etalon
	// se afiseaza vectorul curent
	// se compara cele doua
	//print();

	free(v);
	free(vQSort);

	return 0;
}
