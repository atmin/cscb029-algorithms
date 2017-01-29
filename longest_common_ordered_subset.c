#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

/*
Зад. Дадени са редицата alpha=a1,a2,…,aM
и редицата beta=b1,b2,…,bN

Да се намери дължината на най-дългата обща подредица на alpha и beta
Общата подредица на две редици трябва да съдържа елементи които ги има и в двете редици,
да са в същия ред както в редиците без да е необходимо да са последователни.

Например общи подредици на aaabddc и abcdd са a, ab, abc, abdd и др.
*/

/*
> gcc -o longest_common_ordered_subset longest_common_ordered_subset.c
> cat 2strings.txt | ./longest_common_ordered_subset
*/

char alpha[MAX];
char beta[MAX];
int M, N;
int L[MAX][MAX];
char path[MAX][MAX];
char result[MAX] = "";

void input() {
  scanf("%s", alpha);
  scanf("%s", beta);
  M = strlen(alpha);
  N = strlen(beta);
}

void output() {
  printf("alpha == %s\nbeta  == %s\n", alpha, beta);
  printf("M == %d\nN == %d\n", M, N);
  printf("longest common ordered subset  == %s\n\n", result);
  printf("       ");
  for (int j = 0; j < N; j++) {
    printf(" %c ", beta[j]);
  }
  printf("\n");
  for (int i = 0; i <= M; i++) {
    printf("  %c ", i == 0 ? ' ' : alpha[i - 1]);
    for (int j = 0; j <= N; j++) {
      printf("%2d ", L[i][j]);
    }
    printf("\n");
  }
}

void solve() {
  for (int i = 0; i <= M; i++) {
    L[i][0] = 0;
  }
  for (int j = 0; j <= N; j++) {
    L[0][j] = 0;
  }
  for (int i = 1; i <= M; i++) {
    for (int j = 1; j <= N; j++) {
      if (alpha[i - 1] == beta[j - 1]) {
        L[i][j] = L[i - 1][j - 1] + 1;
        path[i][j] = 'x';
      } else {
        if (L[i - 1][j] >= L[i][j - 1]) {
          L[i][j] = L[i - 1][j];
          path[i][j] = 'i';
        } else {
          L[i][j] = L[i][j - 1];
          path[i][j] = 'j';
        }
      }
    }
  }

  int len = L[M][N];
  result[len] = 0;
  for (int i = M, j = N; i > 0 && j > 0;) {
    if (path[i][j] == 'x') {
      i--; j--; len--;
      result[len] = alpha[i];
    } else {
      if (path[i][j] == 'i') {
        i--;
      } else {
        j--;
      }
    }
  }
}

int main() {
  input();
  solve();
  output();
}
