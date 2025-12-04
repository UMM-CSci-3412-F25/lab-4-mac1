#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat() in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */

  struct stat buf;
  if (stat(path, &buf) != 0) {
    perror("stat failed");
    exit(EXIT_FAILURE);
  }

  return S_ISDIR(buf.st_mode);
}
bool is_regular_file(const char* path) {
  struct stat buf;
  if (stat(path, &buf) != 0) {
    perror("stat failed");
    exit(EXIT_FAILURE);
  }

  return S_ISREG(buf.st_mode);
}

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {
  /*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */

  if (is_dir(path)) {
    num_dirs++;

    DIR* dir = opendir(path);
    if (dir == NULL) {
      perror("opendir failed");
      exit(EXIT_FAILURE);
    }

    // Change to the target directory
    if (chdir(path) != 0) {
      perror("chdir failed");
      closedir(dir);
      exit(EXIT_FAILURE);
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
      // Skip "." and ".." entries
      if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
        process_path(entry->d_name);
      }
    }

    // Change back to the parent directory
    if (chdir("..") != 0) {
      perror("chdir to parent failed");
      closedir(dir);
      exit(EXIT_FAILURE);
    }

    closedir(dir);
  }
}

void process_file(const char* path) {
  /*
   * Update the number of regular files.
   * This is as simple as it seems. :-)
   */

   struct stat s;
    if (stat(path, &s) != 0) {
      perror("stat failed");
      exit(EXIT_FAILURE);
    }
    num_regular++;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
