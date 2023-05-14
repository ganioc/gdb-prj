// usage: sieve nthreads n
// Where nthreads is the number of worker threads

#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define MAX_N 100000000
#define MAX_THREADS 100

int nthreads; // number of threads
int n;        // uppoer bound of range in which to find primes
int prime[MAX_N + 1];
int nextbase; // next sieve multiplier to be used,

int work[MAX_THREADS];

// lock index for shared variable nextbase
pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;

// ID
pthread_t id[MAX_THREADS];

// crosses out all multiples of k , from k*k on
void crossout(int k){
  int i;

  for(i = k; i*k <= n; i++){
    prime[i*k] = 0;
  }
}

//
void *worker(int tn){
  int lim, base;

  // no need to check multipliers bigger than sqrt(n)
  lim = sqrt(n);

  do {
    // get next sieve multiplier, avoiding duplication across threads
    pthread_mutex_lock(&nextbaselock);
    base = nextbase += 2;
    pthread_mutex_unlock(&nextbaselock);
    if(base <= lim){
      work[tn]++;
      // dont' bother with crossing out if base is known to be
      // compose
      if(prime[base]){
	crossout(base);
      }
    }else{
      return;
    }

  }while(1);
    

}

int main(int argc, char **argv){
  int nprimes, totwork, i;
  void *p;

  n = atoi(argv[1]);
  nthreads = atoi(argv[2]);

  for(i = 2; i <= n ; i++){
    prime[i] = 1;
  }
  crossout(2);

  nextbase = 1;

  // get threads started
  for(i = 0; i< nthreads; i++){
    pthread_create(&id[i], NULL, (void *)worker, (void *)i);
  }

  // wait for all done
  totwork = 0;
  for(i = 0; i< nthreads; i++){
    pthread_join(id[i], &p);
    printf("%d values of base done\n", work[i]);
    totwork += work[i];
  }
  printf("%d total values of base done\n", totwork);

  // report results
  nprimes = 0;
  for(i = 2; i<= n; i++){
    if (prime[i])
      nprimes++;
  }
  printf("the number of primes found was %d\n", nprimes);

  return 0;
}
