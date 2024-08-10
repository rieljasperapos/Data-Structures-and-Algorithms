#include <stdio.h>
#include <string.h>

#define MAX 3

int main() {
  char strs[MAX][6] = {
    "Jasper",
    "Kasper",
    "Casper"
  };
  printf("%c", strs[2][0]);
}