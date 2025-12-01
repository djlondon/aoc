#include <stdio.h>
#include <stdlib.h>

#define DIAL_MAX 100
#define DIAL_INIT 50
#define BUF_SIZE 512
#define DEBUG

int main(int argc, char **argv) {

  if (argc != 2) {
    fprintf(stderr, "Usage %s filename\n", argv[0]);
    exit(1);
  }
  char *filename = argv[1];
  
  FILE *fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Failed to open file %s", filename);
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
    
    if (dir == 'L') dial = (dial - amount) % DIAL_MAX;
    else if (dir == 'R') dial = (dial + amount) % DIAL_MAX;
    else continue; /* ignore lines that don't begin with L/R */

    if (dial == 0)
      zero_count++;
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
