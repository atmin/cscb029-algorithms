#include <stdio.h>
#include <stdlib.h>

/*
> ./gen 42 60 | ./merge_sort
*/

#define MAXN 10000

int array[MAXN], N = 0;
int scratch[MAXN];

void input() {
  for (int number; scanf("%d", &number) == 1;) {
    array[N++] = number;
  }
}

void output() {
  for (int i = 0; i < N; i++) {
    printf("%3d  ", array[i]);
    if ((i + 1) % 10 == 0) {
      printf("\n");
    }
  }
  printf("\n\n");
}

void merge_sort(int left, int right) {
  if (left == right) {
    return;
  }

  int pivot = (left + right) / 2;
  int i = 0;
  int left_i = left;
  int pivot_i = pivot + 1;

  merge_sort(left, pivot);
  merge_sort(pivot + 1, right);

  while ((left_i < pivot + 1) && (pivot_i < right + 1)) {
    scratch[i++] = array[left_i] <= array[pivot_i] ?
      array[left_i++] : array[pivot_i++];
  }
  while (left_i < pivot + 1) {
    scratch[i++] = array[left_i++];
  }
  while (pivot_i < right + 1) {
    scratch[i++] = array[pivot_i++];
  }
  for (int length=i, i=0, left_i=left; i < length; i++, left_i++) {
    array[left_i] = scratch[i];
  }
}

int main() {
  input();
  output();
  merge_sort(0, N - 1);
  output();
}
