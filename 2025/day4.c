/* Advent of Code Day 3.
 * This is a classic 2D-array problem.
 *
 * Initially I solved this by fitting the grid into
 * memory of the same size. The problem with this is that
 * you then need to bounds check on the edges.
 * A slightly neater although less memory efficient method is to
 * put the grid in an array larger than it so you can have a border.
 * This way there's no special handling to do at the edges and you
 * can simply loop through the eight neighbours for all cells in the grid.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define ROLL '@'
#define GOOD_ROLL 'x'

#define DEBUG

int is_roll(char c) {
  return c == ROLL || c == GOOD_ROLL;
}

long long get_file_size(int fd) {
  struct stat fs;
  if (fstat(fd, &fs) < 0) {
    perror("failed to fstat");
    exit(1);
  }

  return fs.st_size;
}

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

  int fd;
  if ((fd = open(filename, O_RDONLY)) < 0)
  {
    fprintf(stderr, "Failed to open file %s: ", filename);
    perror("");
    exit(1);
  }

  long grid_size = get_file_size(fd);
#ifdef DEBUG
  printf("file is %ld bytes\n", grid_size);
#endif

  char *grid;
  long num_accessible_rolls = 0;

  if ((grid = calloc(grid_size*2, 1)) == NULL) {
    fprintf(stderr, "Failed to realloc %s: ", filename);
    perror("");
    exit(1);
  }

  int offset = grid_size / 2;
  if ((read(fd, &grid[offset], grid_size)) < grid_size) {
    perror("failed to read");
    exit(1);
  }

  int width;
  for (width = 0; grid[offset+width] != '\n'; width++)
    ;
  width++;
  int height = grid_size / width;
  printf("%d*%d\n", width, height);

  for (int i = offset; i < offset+grid_size; i++)
  {
    int neighbours = 0;
    if (is_roll(grid[i]))
    {
        for (int wi = -1; wi <= 1; wi++) {
          for (int xi = -1; xi <= 1; xi++) {
            if (wi == 0 && xi == 0) continue; // ignore ourselves
            if (is_roll(grid[i + width*wi + xi]))
              neighbours++;
          }
        }
        
      if (neighbours < 4) {
        num_accessible_rolls++;
        grid[i] = GOOD_ROLL;
      }
    }
  }

  printf("\npassword: %ld\n", num_accessible_rolls);

  free(grid);
  return 0;
}
