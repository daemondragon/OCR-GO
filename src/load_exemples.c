#include "load_exemples.h"

#include <stdlib.h>
#include <dirent.h>

//all pictures must have "*.png" format
static char is_png_picture(char *name)
{
    int actual = 0;
    while (name[actual])
        actual++;

    if (actual < 5)
        return (0);

    return (name[actual - 1] == 'g' &&
            name[actual - 2] == 'n' &&
            name[actual - 3] == 'p' &&
            name[actual - 4] == '.');
}

static uint32_t count_png_pictures(DIR *directory)
{
    uint32_t nb_pictures = 0;
    struct dirent* current_file = readdir(directory);
    while (current_file)
    {
        nb_pictures += is_png_picture(current_file->d_name);
        current_file = readdir(directory);
    }

    return (nb_pictures);
}

neural_exemple_t* load_exemples(char directory_name[],
                                double* (*load_picture)(char*),
                                uint32_t *nb_exemples_loaded)
{
    if (!load_picture || !nb_exemples_loaded)
        return (NULL);

    DIR *directory = opendir(directory_name);
    if (!directory)
        return (NULL);

    uint32_t nb_theorical_pictures = count_png_pictures(directory);
    neural_exemple_t *exemples = malloc(sizeof(neural_exemple_t) *
                                        nb_theorical_pictures);
    if (!exemples)
        return (NULL);

    rewinddir(directory);
    *nb_exemples_loaded = 0;

    struct dirent* current_file = readdir(directory);
    while (current_file && (*nb_exemples_loaded < nb_theorical_pictures))
    {
        if (is_png_picture(current_file->d_name))
        {
            double *temp = load_picture(current_file->d_name);
            if (temp && current_file->d_name[0])
            {
                exemples[*nb_exemples_loaded].inputs = temp;
                exemples[*nb_exemples_loaded].answer =
                    current_file->d_name[0];

                (*nb_exemples_loaded)++;
            }
            else
                nb_theorical_pictures--;
        }
        current_file = readdir(directory);
    }

    closedir(directory);
    return (exemples);
}
