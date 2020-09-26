#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
(void)argc;
(void)argv;
	
  int in, out;
  char *grep_args[] = {"grep", "Villanova", NULL};

  // open input and output files

  in = open("scores", O_RDONLY);
  out = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

  // replace standard input with input file
  int stdin_var;
  int stdout_var;

	stdin_var = dup(0);
	stdout_var = dup(0);

  dup2(in, 0);

  // replace standard output with output file

  dup2(out, 1);

  // close unused file descriptors

  close(in);
  close(out);

  // execute grep

  execvp("grep", grep_args);
  
  dup2(stdin_var, 0);
  dup2(stdout_var, 1);


	printf("salut\n");
}