#include <stdio.h>

enum options_e { HELP = 'h', VERSION = 'v', TCP_SOCKET = 's' };

int main(int argc, char *argv[]) {

  if (argc > 1 && argv[1][0] == '-') {
    switch (argv[1][1]) {
    case HELP:
      printf("This should be a function that prints the help menu\n");
      break;
    case VERSION:
      printf("This should be a function that prints the version\n");
      break;
    case TCP_SOCKET:
      printf("This should be a function that creates a TCP socket\n");
      break;
    }
  } else {
    printf("No or incorrect command line argument provided.\n");
  }

  return 0;
}
