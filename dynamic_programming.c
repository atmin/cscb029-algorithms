#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define INF 999

/*
Задача pi(N). N човека чакат на опашка за билети,
като времето за което i-тият човек ще си купи билет е t(1,i),i=1,2,…,N.

Ако двама съседи в опашката, i-тият и (i+1)-ят се кооперират,
купуват билетите за време t(2,i), i=1,2,…,N-1.

Ако j съседи в опашката - от i-тия до (i+j-1)-вия се кооперират,
купуват билетите за време t(j,i), i=1,2,…,N-j+1, и т.н. Всички заедно биха си купили билети за време tN1.
Да се намери минималното време, за което може всички в опашката да си купят билети.
*/

/*
> cat t_queue.txt | ./dynamic_programming
*/

int M[MAXN][MAXN], N = 0;

void input() {
  for (int number; scanf("%d", &number) == 1;) {
    M[0][N++] = number;
  }
}

void output() {
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N; i++) {
      printf("%3d ", M[j][i]);
    }
    printf("\n");
  }
  printf("\n\n");
}

int min(int a, int b) {
  return a < b ? a : b;
}

void solve() {
  for (int j = 1; j < N; j++) {
    for (int i = 0; i < N - j; i++) {
      M[j][i] = INF;
      for (int k = 0; k < j; k++) {
        M[j][i] = min(M[j][i], M[k][i] + M[j - k - 1][i + k + 1]);
        printf("[%d][%d] %d\n", j+1, i+1, M[j][i]);
      }
    }
  }
}

int main() {
  input();
  solve();
  output();
}
