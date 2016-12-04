#include "improve_string.h"

static char is_letter(char c)
{
    return (('a' <= c && c <= 'z') ||
            ('A' <= c && c <= 'Z'));
}

static char is_digit(char c)
{
    return ('0' <= c && c <= '9');
}

static char is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static char is_sentence_end(char c)
{
    return (c == '.' || c == '!' || c == '?');
}

static char to_upper(char c)
{
    if ('a' <= c && c <= 'z')
        c -= 'a' - 'A';
    return (c);
}

static char to_lower(char c)
{
    if ('A' <= c && c <= 'Z')
        c += 'a' - 'A';
    return (c);
}

#include <stdio.h>

static void improve_letter_case(char *string)
{
    char *actual = string;
    while (*actual)
    {
        if (is_letter(*actual))
        {
            char *prev = actual - 1;
            while (prev >= string && is_whitespace(*prev))
                --prev;

            if (prev < string || is_sentence_end(*prev))
                *actual = to_upper(*actual);
            else
                *actual = to_lower(*actual);
        }
        ++actual;
    }
}

static void remove_useless_white_space(char *string)
{
    char *actual = string;
    char *modified = string;
    char is_prev_white = 0;

    while (*actual)
    {
        if (is_whitespace(*actual))
        {
            if (is_prev_white)
            {
                while (is_whitespace(*actual))
                    ++actual;
            }
            *(modified++) = *(actual++);

            is_prev_white = 1;
        }
        else
        {
            *(modified++) = *(actual++);
            is_prev_white = 0;
        }
    }
    *modified = '\0';
}

void improve_string(char *string)
{
    if (!string)
        return;

    remove_useless_white_space(string);
    improve_letter_case(string);
}
