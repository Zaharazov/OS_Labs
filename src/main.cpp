#include <unistd.h> // for fork() and pipe
#include <string>

int main()
{
    int fd[2]; // 0 - read, 1 - write

    if (pipe(fd) == -1) return -1;

    int id = fork(); // create a process

    if (id == -1) // error
    {
        return -1;
    }
    else if (id == 0) // child
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("./child", NULL);
        return 0;
    }
    else // parent (id > 0)
    {
        close(fd[0]);
        std::string number = "";
        char c;

        if (read(STDIN_FILENO, &c, sizeof(char)) == -1) return -1;

        while (c != '\n')
        {
            if (c == ' ')
            {
                if (write(fd[1], &number, sizeof(number)) == -1) return -1;
                number = "";
            }
            else
            {
                number += c;
            }

            if (read(STDIN_FILENO, &c, sizeof(char)) == -1) return -1;
        }

        if (number != "")
        {
            if (write(fd[1], &number, sizeof(number)) == -1) return -1;
        }

        wait(NULL);
        close(fd[1]);
    }
    return 0;
}
