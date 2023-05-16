#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{

    char sourcepath_args[1024] = "!";
    char files_args[1024] = "";
    char final_cmd[2048] = "javac -d classfiles -sourcepath ";

    FILE* comp_file = fopen("./jocoa_lists.txt", "r");

    char line[1024];
    
    while (fgets(line, sizeof(line), comp_file) != NULL)
    {

        size_t line_len = strlen(line);

        if (line[line_len - 1] == '\n')
        {
            
            line[line_len - 1] = '\0';

        }

        strcat(sourcepath_args, ";");
        strcat(sourcepath_args, line);

        strcat(files_args, line);
        strcat(files_args, " ");

    }

    char* pos = strstr(sourcepath_args, "!;");

    if (pos != NULL)
    {
        
        memmove(pos, pos + 2, strlen(pos + 2) + 1);
    
    }

    strcat(final_cmd, sourcepath_args);
    strcat(final_cmd, " ");
    strcat(final_cmd, files_args);

    printf("%s\n", final_cmd);

    fclose(comp_file);

    return 0;
}
