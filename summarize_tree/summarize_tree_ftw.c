#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <ftw.h>
#include <stdlib.h>

static int num_dirs = 0;
static int num_regular = 0;

int process_entry(const char *fpath, const struct stat *sb,
                   int typeflag, struct FTW *ftwbuf) {
  if (typeflag == FTW_D) {
    num_dirs++;
  } else if (typeflag == FTW_F) {
    num_regular++;
  }
  return 0;  // Continue traversal
}

int main(int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf("Usage: %s <path>\n", argv[0]);
    printf("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  // Use nftw() with FTW_PHYS to not follow symlinks
  if (nftw(argv[1], process_entry, 20, FTW_PHYS) == -1) {
    perror("nftw failed");
    return 1;
  }

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
