/* Advent of Code Day 1.
 * This problem essentially requires utilising modular arithmetic.
 * Part 2 then requires integer arithmetic (dealing with rounding).
*/

#include <stdio.h>
#include <stdlib.h>

#define DIAL_MAX 100
#define DIAL_INIT 50
#define BUF_SIZE 512
#define DEBUG

/* Calculate the modulo of dividend and divisor.
 * This always returns a positive number as expected in
 * modular arithmeticic.
 */
int mod(int dividend, int divisor) {
      int ret;
      ret = (dividend) % divisor;
      if (ret < 0) ret += divisor;
      return ret;
}

int rotate_right_count_all_zeroes(int *dial, int amount) {
    int rot = *dial + amount;
    *dial = rot % DIAL_MAX;
    return rot / DIAL_MAX;
}

int rotate_right_count_end_zero(int *dial, int amount) {
  *dial = (*dial + amount) % DIAL_MAX;
  return (*dial == 0);
}

int rotate_left_count_all_zeroes(int *dial, int amount) {
    int zero_count = 0;
    int rot = *dial - amount;
    // NOTE: This is effectively doing ceiling (rounding up).
    // A negative number when we're not on zero must mean
    // we went through zero. However, we still need to consider
    // when starting at zero, in case we go beyond the DIAL_MAX.
    if ((rot <= 0 && *dial != 0))
      zero_count += 1 - rot / DIAL_MAX;
    else if (rot <= -DIAL_MAX)
      zero_count += - rot / DIAL_MAX;
    *dial = mod(rot, DIAL_MAX);
    return zero_count;
}

int rotate_left_count_end_zero(int *dial, int amount) {
  *dial = (*dial - amount) % DIAL_MAX;
  return (*dial == 0);
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

  int dial = DIAL_INIT;
  int zero_count = 0;
  char buffer[BUF_SIZE];
  char *n;
  char dir;

  while ((n = fgets(buffer, BUF_SIZE, fp))) {
    char *b = buffer;
    dir = buffer[0];
    int amount = atoi(++b);

    #ifdef DEBUG
    printf("%c %d: %s", dir, amount, buffer);
    #endif
    
    if (dir == 'L') {
      if (part == '1')
        zero_count += rotate_left_count_end_zero(&dial, amount);
      else if (part == '2')
        zero_count += rotate_left_count_all_zeroes(&dial, amount);
    }
    else if (dir == 'R') {
      if (part == '1')
        zero_count += rotate_right_count_end_zero(&dial, amount);
      else if (part == '2')
        zero_count += rotate_right_count_all_zeroes(&dial, amount);
    }
    else continue; /* ignore lines that don't begin with L/R */

    #ifdef DEBUG
    printf("zero count: %d; dial: %d\n", zero_count, dial);
    #endif

  }

  if (!feof(fp)) {
      perror("Issue reading file");
      fclose(fp);
      exit(1);
  }

  printf("password: %d\n", zero_count);

  fclose(fp);
  
  return 0;
}
