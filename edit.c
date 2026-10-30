#include <stdio.h>
#include <string.h>
#include "edit.h"

/* Update one specific ID3 frame inside the MP3 file. */
int edit_tag(char *filename, char *frame, char *value)
{
    FILE *fptr = fopen(filename, "r+b");

    if (!fptr)
    {
        printf("File open failed\n");
        return 0;
    }

    fseek(fptr, 10, SEEK_SET);

    char id[5];
    id[4] = '\0';

    while (fread(id, 4, 1, fptr))
    {
        char size_buf[4];

        fread(size_buf, 4, 1, fptr);

        int size = ((unsigned char)size_buf[0] << 24) |
                   ((unsigned char)size_buf[1] << 16) |
                   ((unsigned char)size_buf[2] << 8)  |
                   ((unsigned char)size_buf[3]);

        fseek(fptr, 2, SEEK_CUR);

        if (strcmp(id, frame) == 0)
        {
            int i;

            // Write encoding byte 
            fputc(0, fptr);

            // Write new tag value 
            fwrite(value, 1, strlen(value), fptr);

            // Clear remaining bytes of old tag 
            for (i = strlen(value) + 1; i < size; i++)
            {
                fputc('\0', fptr);
            }

            fclose(fptr);

            printf("Tag Updated Successfully\n");
            return 1;
        }

        fseek(fptr, size, SEEK_CUR);
    }

    fclose(fptr);

    printf("Tag not found\n");
    return 0;
}

/* Update the common title, artist, album, year, genre, and comment tags together. */
int edit_tags(char *filename, char *title, char *artist, char *album, char *year, char *genre, char *comment)
{
    int ok = 1;

    ok &= edit_tag(filename, "TIT2", title);
    ok &= edit_tag(filename, "TPE1", artist);
    ok &= edit_tag(filename, "TALB", album);
    ok &= edit_tag(filename, "TYER", year);
    ok &= edit_tag(filename, "TCON", genre);
    ok &= edit_tag(filename, "COMM", comment);

    if (ok)
    {
        printf("All tags updated successfully\n");
        return 1;
    }

    return 0;
}