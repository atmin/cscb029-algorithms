#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

/*
Даден е ориентиран ацикличен граф G(V,E).
Да се намери дължината на най-дълъг маршрут (ориентиран път) в G
*/

/*
> gcc -o longest_path longest_path.c
> cat dag.txt | ./longest_path
*/

int G[MAX][MAX]; // G[i] - наследници на връх i. G[i][0] - брой наследници
int H[MAX][MAX]; // H[i] - предшественици на връх i. Същия формат
int N; // брой върхове
int L[MAX];
int s[MAX]; // топологично сортирани върхове
bool marked[MAX];
bool tempmarked[MAX];

void input() {
  for (char line[MAX]; fgets(line, sizeof(line), stdin);) {
    char *token = strtok(line, " ");
    G[++N][0] = 0;
    while (token && strcmp(token, "\n") != 0) {
      int len = ++G[N][0];
      G[N][len] = atoi(token);
      token = strtok(NULL, " ");
    }
  }
  for (int i = 1; i <= N; i++) {
    for (int len = G[i][0], j = 1; j <= len; j++) {
      int predecessor = G[i][j];
      H[predecessor][++H[predecessor][0]] = i;
    }
  }
}

void output() {
  printf("H\n");
  for (int i = 1; i <= N; i++) {
    printf("%2d ", i);
    for (int len = H[i][0], j = 1; j <= len; j++) {
      printf("%2d ", H[i][j]);
    }
    printf("\n");
  }
  printf("\ns\n");
  for (int i = 1; i <= N; i++) {
    printf("%2d ", s[i]);
  }
  printf("\nL\n");
  for (int i = 1; i <= N; i++) {
    printf("%2d ", L[i]);
  }
  printf("\n");
}

void visit(node) {
  if (tempmarked[node]) {
    printf("cycle detected at node %d", node);
    exit(1);
  }
  if (!marked[node]) {
    tempmarked[node] = true;
    for (int len = G[node][0], i = 1; i <= len; i++) {
      visit(G[node][i]);
    }
    marked[node] = true;
    tempmarked[node] = false;
    int last = N;
    while (s[last] != 0) {
      last--;
    };
    s[last] = node;
  }
}

void topsort() {
  while (true) {
    int node = 1;
    while (marked[node] && node <= N) {
      node++;
    }
    if (node == N + 1) {
      break;
    }
    visit(node);
  }
}

void solve() {
  topsort();
  for (int i = 1; i <= N; i++) {
    int k = s[i];
    L[k] = 0;
    if (H[k][0] > 0) {
      for (int j = 1; j <= H[k][0]; j++) {
        int predecessor = H[k][j];
        L[k] = L[predecessor] > L[k] ?
          L[predecessor] : L[k] + 1;
      }
    }
  }
}

int main() {
  input();
  solve();
  output();
}
