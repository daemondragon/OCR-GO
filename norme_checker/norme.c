#include <stdlib.h>
#include <stdio.h>

//gcc -o norme norme.c -Wall
int main(int argc, char *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
    {
        FILE* file = fopen(argv[i], "r");
        if (!file)
        {
            printf("Can't open: %s\n", argv[i]);
            continue;
        }
        else
        {
            int current_line = 0;
            int last_enter = 0;
            int nb_errors = 0;
            char last_c = 'c';
            char c;
            do
            {
                c = getc(file);
                last_enter++;
                if (c != EOF)
                {
                    if (c == '\n')
                    {
                        current_line++;

                        if (last_enter >= 80)
                        {
                            if (nb_errors <= 0)
                                printf("Opened: %s\n", argv[i]);
                            printf("more than 80 character at %d line\n",
                                                                current_line);
                            nb_errors++;
                        }
                        if (last_c == ' ' || last_c == '\t')
                        {
                            if (nb_errors <= 0)
                                printf("Opened: %s\n", argv[i]);
                            printf("space before \\n at: %d line\n",
                                                                current_line);
                            nb_errors++;
                        }

                        last_enter = 0;
                    }
                    last_c = c;
                }
            } while (c != EOF);

            printf("%.3d errors for file %s \n", nb_errors, argv[i]);

            fclose(file);
        }
    }
    return (0);
}
