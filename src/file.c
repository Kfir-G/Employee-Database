#include "../include/file.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/common.h"

int create_db_file(char *filename) {
  /**
   * Creates a new database file.
   * If the file already exists, it closes the file descriptor and returns an error.
   * Otherwise, it creates a new file with read/write permissions.
   *
   * filename: The name of the file to create.
   *
   * Returns: The file descriptor on success, or STATUS_ERROR on failure.
  */

  int fd = open(filename, O_RDWR); // point here is to ensure user doesnt open existing and deletes it
  if (fd != -1) {
    close(fd);
    printf("File already exists\n");
    return STATUS_ERROR;
  }

  fd = open(filename, O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("open");
    return STATUS_ERROR;
  }

  return fd;
}

int open_db_file(char *filename) {
  /**
   * Function: open_db_file
   * -----------------------
   * Opens an existing database file with read/write permissions.
   *
   * filename: The name of the file to open.
   *
   * Returns: The file descriptor on success, or STATUS_ERROR on failure.
  */

  int fd = open(filename, O_RDWR, 0644);
  if (fd == -1) {
    perror("open");
    return STATUS_ERROR;
  }

  return fd;
}
