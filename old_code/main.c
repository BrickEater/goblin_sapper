// NOTE: Steps that need to be taken:
//  create the socket with socket()
//  bind the address to the socket with bind()
//  listen for a connection to the socket with listen()
//  accept the connection to the socket with accept()
//
//  NOTE: The program is meant to be a multi tool for pen testing but for now
//  it's only a TCP server.
//
//  TODO: Parse the user port input into an int. (I'm assuming I need to do this
//  but maybe not since I'll be using htons()
//  TODO: Create socket
//  TODO: bind port address to socket

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <unistd.h>

#define VERSION "1.0.0"

void help();
void version();
void deploy_server(char *port_string);

int main(int argc, char *argv[]) {

  if (argc == 1) {
    help();
  }

  for (int i = 1; i < argc; i++) {

    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      help();
      return 0;
    }
    if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
      version();
      return 0;
    }
    if (strcmp(argv[i], "-s") == 0) {
      if (i + 1 < argc) {
        deploy_server(argv[i + 1]);
        i++;

      } else {
        fprintf(stderr, "Error: -s requires a port number.\n");
        return 1;
      }
    }
  }
  return 0;
}

void help() {
  printf("Usage: gsap [options]\n"
         "\n"
         "Options:\n"
         "  -h, --help         Display the help menu.\n"
         "  -v, --version      Display the version information.\n"
         "  -s <port number>   Create a TCP server on the specified port.\n"
         "\n"
         "Example:\n"
         "  gasp -s 8080       Start a server on port 8080.\n");
}

void version() { printf("Goblin Sapper version %s\n", VERSION); }

void deploy_server(char *port_string) {
  printf("Deploying server on port %s\n", port_string);

  int port = atoi(port_string);
  if (port == 0 && strcmp(port_string, "0") != 0) {
    fprintf(stderr, "Invalid port number provided.\n");
    return;
  }

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr = {AF_INET, htons(port), 0};
  bind(socket_fd, &addr, sizeof(addr));
  int listener = listen(socket_fd, 10);
  int client_fd = accept(socket_fd, 0, 0);
  char buffer[256] = {0};
  recv(client_fd, buffer, 256, 0);

  char *file = buffer + 5;
  *strchr(file, ' ') = '\0';
  int opened_fd = open(file, O_RDONLY);
  sendfile(client_fd, opened_fd, 0, 256);
  close(opened_fd);
  close(client_fd);
  close(socket_fd);
}
