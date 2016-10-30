#include <stdlib.h>
#include <stdio.h>

#include "show_xor.h"
#include "window.h"
#include "testing_cut.h"

#include "image_to_matrix.h"
#include "filters.h"

void show_picture()
{
    int w;
    int h;

    double *pixels = file_to_matrix_grey("./image_test/min.png", NULL, &w, &h);

    printf("%d %d\n", w, h);

    for (size_t i = 0; i < w * h; ++i)
        printf("%f ", pixels[i]);
    printf("\n");
}

char is_same_string(char *s1, char *s2)
{
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 != *s2)
            return (0);
        else
        {
            ++s1;
            ++s2;
        }
    }
    return (*s1 == *s2);
}

typedef struct
{
    char *arg;
    char *description;
    void (*fun)(void);
} argument_t;

int main(int argc, char *argv[])
{
    argument_t  arguments[] = {{"xor", "show neural network xor", show_xor},
			                   {"cut", "rapid test for cutting", test_cut},
					   {"filter", "test for filters", test_filters},
					   {"pcut", "pretty test for cutting", show_cutting},
					   {"mat_copy", "test for copying matrix", test_mat_copy},
					   {"load", "load image", show_picture}};
    size_t nb_arguments = 6;
    if (argc > 1)
    {
        for (size_t i = 0; i < nb_arguments; i++)
        {
            if (is_same_string(argv[1], arguments[i].arg))
            {
                if (arguments[i].fun)
                    arguments[i].fun();
                else
                    printf("Error in arg %s : function is NULL\n", argv[1]);
                break;
            }
        }
    }
    else
    {
        printf("%s arguments:\n", argv[0]);
        for (size_t i = 0; i < nb_arguments; i++)
            printf("    %s - %s\n", arguments[i].arg,
                                    arguments[i].description);

        run_window(argc, argv);
    }

    return (0);
}
