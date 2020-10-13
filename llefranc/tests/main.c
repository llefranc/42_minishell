#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
(void)argc;
(void)argv;
	
  int in, out;
//   char *grep_args[] = {"grep", "Villanova", NULL};

  // open input and output files

  in = open("scores", O_RDONLY);
  out = open("harry", O_WRONLY | O_TRUNC | O_CREAT);


  // close unused file descriptors

  close(in);
  close(out);



	printf("salut\n");
}