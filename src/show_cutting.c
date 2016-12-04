#include "show_cutting.h"

static char is_inside(int x, int y, int width, int height)
{
    return (0 <= x && x < width &&
            0 <= y && y < height);
}

void frame_cut_characters(GdkPixbuf *pixbuf, double *matrix, W_list *list)
{
    if (!pixbuf || !matrix || !list)
        return;

    guchar  *pixels     = gdk_pixbuf_get_pixels(pixbuf);
    gint    channel     = gdk_pixbuf_get_n_channels(pixbuf);
    gint    width       = gdk_pixbuf_get_width(pixbuf);
    gint    height      = gdk_pixbuf_get_height(pixbuf);
    gint    rowstride   = gdk_pixbuf_get_rowstride(pixbuf);

    infos *actual = list->first;
    while (actual)
    {
        if (actual->type == WORD)
        {
            int pos_x = (actual->pos - matrix) % width - 1;
            int pos_y = (actual->pos - matrix) / width - 1;

            for (size_t x = 0; x < actual->width + 2; ++x)
            {
                for (size_t y = 0; y < actual->height + 2; y++)
                {
                    if ((y == 0 || y == actual->height + 1 ||
                         x == 0 || x == actual->width + 1) &&
                         is_inside(pos_x + x, pos_y + x, width, height))
                    {
                        int f_x = pos_x + (int)x;
                        int f_y = pos_y + (int)y;
                        pixels[(f_x * channel) + (f_y * rowstride)] = 255;
                        pixels[(f_x * channel) + (f_y * rowstride) + 1] = 0;
                        pixels[(f_x * channel) + (f_y * rowstride) + 2] = 0;
                    }
                }
            }
        }
        else if (actual->type == SPACE)
        {
            int pos_x = (actual->pos - matrix) % width + 3;
            int pos_y = (actual->pos - matrix) / width + actual->height;
            for (size_t x = 0; x + 6 < actual->width; ++x)
            {
                if (is_inside(pos_x + x, pos_y, width, height))
                {
                    int f_x = pos_x + (int)x;
                    int f_y = pos_y;
                    pixels[(f_x * channel) + (f_y * rowstride)] = 255;
                    pixels[(f_x * channel) + (f_y * rowstride) + 1] = 0;
                    pixels[(f_x * channel) + (f_y * rowstride) + 2] = 0;
                }
            }
        }
        actual = actual->nxt;
    }
}
