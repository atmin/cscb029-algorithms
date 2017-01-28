#include <stdio.h>
#include <stdlib.h>

/*
Generates COUNT random numbers in the range 0..999
Usage: gen RANDOM_SEED COUNT
*/

int main(int argc, char *argv[]) {
  int seed = atoi(argv[1]);
  int count = atoi(argv[2]);
  srand(seed);
  for (int i = 0; i < count; i++) {
    printf("%d\n", rand() % 1000);
  }
}
