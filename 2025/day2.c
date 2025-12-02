/* Advent of Code Day 2.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 64
#define DEBUG

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "Usage %s part filename\n", argv[0]);
    exit(1);
  }

  char part = argv[1][0];
  char *filename = argv[2];

  if ((part != '1') && (part != '2'))
  {
    fprintf(stderr, "part %c must be 1 or 2\n", part);
    exit(1);
  }

  FILE *fp;
  if ((fp = fopen(filename, "r")) == NULL)
  {
    fprintf(stderr, "Failed to open file %s: ", filename);
    perror("");
    exit(1);
  }

  long invalid_count = 0;
  char *range = NULL;
  size_t rangecap = 0;
  ssize_t n;

  while ((n = getdelim(&range, &rangecap, ',', fp)) > 0)
  {
    char buf[BUF_SIZE];
    long start, end;
    int i, j;
    for (i = 0; range[i] != '-'; i++)
      buf[i] = range[i];
    buf[i] = '\0';
    start = strtol(buf, NULL, 10);
    i++; // skip -
    for (j = 0; range[i] != ',' && range[i] != '\n'; i++, j++)
      buf[j] = range[i];
    buf[j] = '\0';
    end = strtol(buf, NULL, 10);

#ifdef DEBUG
    printf("%s: %ld %ld\n", range, start, end);
#endif

    for (long x = start; x <= end; x++)
    {
      size_t len, ii;
      if (snprintf(buf, BUF_SIZE, "%ld", x) < 0)
      {
        perror("Error in sprintf");
        fclose(fp);
        exit(1);
      }
      len = strnlen(buf, BUF_SIZE);

      if (part == '1') {
        if (len % 2 != 0)
          continue;
        for (ii = 0; ii < (len / 2); ii++)
        {
          if (buf[ii] != buf[ii + len / 2])
            goto valid;
        }
        invalid_count += x;
        valid:;
      } else if (part == '2') {
      }
    }

#ifdef DEBUG
    printf("invalid_count: %ld\n", invalid_count);
#endif
  }

  if (!feof(fp))
  {
    perror("Issue reading file");
    fclose(fp);
    exit(1);
  }

  printf("password: %ld\n", invalid_count);

  fclose(fp);

  return 0;
}
