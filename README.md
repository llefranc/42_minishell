# Minishell (@42Paris - made with [Corentin Debraix][1])

As beautiful as a shell

![Alt text](https://github.com/lucaslefrancq/42-07_philosophers/blob/main/minishell_example.png)

## About

Minishell is the 6th project of the mandatory part of the cursus.
It's only made in C and the main goal was to create a shell working like bash.
In this case we had to understand how processes, redirections, pipes, execve and bash builtins work.
We also had to learn how bash was handling a command line (lexer / parser / exec).

- Here is the [subject][2]

`This project was code for MACOS`

### Building and running the program

1. Download/Clone this repo

        git clone https://github.com/lucaslefrancq/42-06_minishell
2. `cd` into the root directory, and run `make`

        cd 42-06_minishell
        make

3.  run `./minishell` without any argument.
    
## Sources

- [Tutorial for writing a small shell in C][5]
- [Comprendre les fonctions liées aux processus : fork, exit et wait (FR)][6]
- [Understanding fork][7]
- [Difference between inputs / arguments when using pipes][8]
- [Understanding redirection][3]
- [Les variables d'environnement en C (FR)][4]


[1]: https://github.com/codebrai
[2]: https://github.com/lucaslefrancq/42-06_minishell/blob/main/minishell.en.subject.pdf
[8]: https://superuser.com/questions/178796/understanding-how-inputs-are-sent-to-pipes-in-bash/178798#178798
[3]: https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/dup2.html
[4]: http://supertos.free.fr/supertos.php?page=950
[5]: https://brennan.io/2015/01/16/write-a-shell-in-c/
[6]: http://pageperso.lif.univ-mrs.fr/~luigi.santocanale/teaching/0506teaching/SYSTEME/lecture2.handout.pdf
[7]: https://www.geeksforgeeks.org/fork-system-call/#:~:text=Fork%20system%20call%20is%20used,the%20fork()%20system%20call.