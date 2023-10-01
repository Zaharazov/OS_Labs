#include <fcntl.h> // for open 
#include <unistd.h> // for read() and write()
#include <string>

int main()
{
    int output;
    output = open("output.txt", O_WRONLY, 0);
    std::string parentdata;
    float divisible = 0;
    bool notempty = 0;

    while (read(STDIN_FILENO, &parentdata, sizeof(parentdata)) != 0) {
        if (divisible == 0)
        {
            notempty = 1;
            divisible = std::stof(parentdata);
        }
        else
        {
            if (std::stof(parentdata) == 0)   exit(-1);

            divisible /= std::stof(parentdata);
        }
    }

    if (!notempty) exit(-1);

    std::string div_str = std::to_string(divisible);

    char answer[100];
    sprintf(answer, "The answer is: %f", divisible);

    if (write(output, &answer, 15 + div_str.length()) == -1) {
        return -1;
    }
}
