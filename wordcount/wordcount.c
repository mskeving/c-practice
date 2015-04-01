#include <stddef.h>
#include <stdio.h>

int main(int argc, char** argv)
{

    FILE *fp;
    char buffer[4096];
    int res = 0;
    int word_count = 0;
    int line_count = 0;

    printf("\n");
    printf("program name: \"%s\"\n", argv[0]);

    for (int i = 1; i < argc; i++) {
        printf(" \"%s\"", argv[i]);
        fp = fopen(argv[i], "r");

        if (fp != NULL)
        {
            while (!feof(fp))
            {
                res = fread(buffer, 1, (sizeof buffer)-1, fp);
                buffer[res] = 0;
                for (int i=0; i < res; i++)
                {
                    if (buffer[i]== ' ')
                    {
                        /* Before you say anything, I know this is not the right way to count words.*/
                        ++word_count;
                    }
                    if (buffer[i]== '\n')
                    {
                        ++line_count;
                    }
                }
            }
            fclose(fp);
            printf("\n");
            printf("%d \n", line_count);
            printf("%d \n", word_count);
            printf("%d \n", res);
        }
        else
            printf("File %s not found", argv[1]);
    }
    printf("\n");

    return 0;
}

