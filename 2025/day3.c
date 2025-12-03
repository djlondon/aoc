/* Advent of Code Day 3.
*/

#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 512
#define DEBUG

/* Convert an ascii number '0' - '9' into
* the numerical value 0 - 9.
* Returns -1 on invalid input.
*/
char ascii_to_num(char c) {
  if (c < '0' || c > '9') return -1;
  return c - '0';
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage %s part filename\n", argv[0]);
    exit(1);
  }

  char part = argv[1][0];
  char *filename = argv[2];

  if ((part != '1') && (part != '2')) {
    fprintf(stderr, "part %c must be 1 or 2\n", part);
    exit(1);
  }

  FILE *fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Failed to open file %s: ", filename);
    perror("");
    exit(1);
  }

  long joltage_total = 0;
  char buffer[BUF_SIZE];
  char *n;

  while ((n = fgets(buffer, BUF_SIZE, fp))) {
    char first_digit = 0;
    int first_digit_loc = 0;
    char second_digit = 0;
#ifdef DEBUG
    printf("%s", buffer);
#endif

    for (int i = 0; buffer[i+1] != '\0' && buffer[i+1] != '\n'; i++) {
      int v = ascii_to_num(buffer[i]);
      if (v > first_digit) {
        first_digit = v;
        first_digit_loc = i;
      }
    }

    for (int i = first_digit_loc+1; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
      int v = ascii_to_num(buffer[i]);
      if (v > second_digit) {
        second_digit= v;
      }
    }

#ifdef DEBUG
    printf("%d %d\n", first_digit, second_digit);
#endif

    if (part == '1') {
      joltage_total += first_digit * 10 + second_digit;
    }
    else if (part == '2') {
    }
#ifdef DEBUG
    printf("%ld\n", joltage_total);
#endif

  }

  if (!feof(fp)) {
    perror("Issue reading file");
    fclose(fp);
    exit(1);
  }

  printf("password: %ld\n", joltage_total);

  fclose(fp);

  return 0;
}
