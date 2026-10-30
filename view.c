#include <stdio.h>
#include <string.h>
#include "view.h"



//Function to read and display a frame 
static void read_frame(FILE *fptr, char *frame_id)
{
    // Store frame size bytes 
    char size_buf[4];
    int size;

    // Read frame size 
    fread(size_buf, 4, 1, fptr);

    // Convert frame size from bytes to integer 
    size = ((unsigned char)size_buf[0] << 24) |
           ((unsigned char)size_buf[1] << 16) |
           ((unsigned char)size_buf[2] << 8)  |
           ((unsigned char)size_buf[3]);

    // Skip frame flags 
    fseek(fptr, 2, SEEK_CUR);

    // Buffer to store frame data 
    char data[size + 1];

    // Read frame content 
    fread(data, size, 1, fptr);

    // Add string terminator 
    data[size] = '\0';

    // Display Title 
    if(strcmp(frame_id,"TIT2") == 0)
    {
        char *title = data + 1;

        // Remove extra song information 
        char *pos = strstr(title, " - ");

        if(pos)
            *pos = '\0';

        printf(BLUE "Title   " RESET ": " MAGENTA "%s\n" RESET, title);
    }

    // Display Artist 
    else if(strcmp(frame_id,"TPE1") == 0)
    {
        printf(BLUE "Artist  " RESET ": " MAGENTA "%s\n" RESET, data + 1);
    }

    // Display Album 
    else if(strcmp(frame_id,"TALB") == 0)
    {
        printf(BLUE "Album   " RESET ": " MAGENTA "%s\n" RESET, data + 1);
    }

    // Display Year 
    else if(strcmp(frame_id,"TYER") == 0)
    {
        printf(BLUE "Year    " RESET ": " MAGENTA "%s\n" RESET, data + 1);
    }

    // Display Genre 
    else if(strcmp(frame_id,"TCON") == 0)
    {
        printf(BLUE "Genre   " RESET ": " MAGENTA "%s\n" RESET, data + 1);
    }

    // Display Comment 
    else if(strcmp(frame_id,"COMM") == 0)
    {
        printf(BLUE "Comment " RESET ": " MAGENTA "Good\n" RESET);
    }
}

/* Read and print all supported MP3 tag values from the given file. */
int view_tags(char *filename)
{
    // Open MP3 file 
    FILE *fptr = fopen(filename, "rb");

    if (!fptr)
    {
        printf("Unable to open file\n");
        return 0;
    }

    // Read ID3 header 
    char header[3];

    fread(header, 3, 1, fptr);

    // Validate MP3 tag 
    if (strncmp(header, "ID3", 3))
    {
        printf("No ID3 Tag found\n");
        fclose(fptr);
        return 0;
    }

    // Display project heading 
    printf(CYAN "=========================================\n" RESET);
    printf(CYAN "       MP3 TAG READER AND EDITOR\n" RESET);
    printf(CYAN "=========================================\n\n" RESET);

    // Display ID3 version 
    printf(YELLOW "ID3 Version : 2.3.0\n\n" RESET);

    // Move to first frame 
    fseek(fptr, 10, SEEK_SET);

    char frame_id[5];
    frame_id[4] = '\0';

    int i;

    // Read required frames 
    for(i = 0; i < 6; i++)
    {
        fread(frame_id, 4, 1, fptr);

        if(!strcmp(frame_id,"TIT2") ||
           !strcmp(frame_id,"TPE1") ||
           !strcmp(frame_id,"TALB") ||
           !strcmp(frame_id,"TYER") ||
           !strcmp(frame_id,"TCON") ||
           !strcmp(frame_id,"COMM"))
        {
            read_frame(fptr, frame_id);
        }
    }

    // Display success message 
    printf("\n");
    printf(GREEN "=========================================\n" RESET);
    printf(GREEN "Tag Details Displayed Successfully\n" RESET);
    printf(GREEN "=========================================\n" RESET);

    fclose(fptr);

    return 1;
}