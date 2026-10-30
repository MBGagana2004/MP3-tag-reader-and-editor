#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"
#include "edit.h"

/* Display the command-line usage instructions for the program. */
void display_usage(void)
{
    printf("========================================\n");
    printf(" MP3 TAG READER AND EDITOR\n");
    printf("========================================\n");

    printf("Usage:\n");
    printf("./a.out -v file.mp3\n");
    printf("./a.out -p file.mp3\n");
    printf("./a.out -e -t \"Title\" file.mp3\n");
    printf("./a.out -e -a \"Artist\" file.mp3\n");
    printf("./a.out -e -A \"Album\" file.mp3\n");
    printf("./a.out -e -y \"Year\" file.mp3\n");
    printf("./a.out -e -m \"Genre\" file.mp3\n");
    printf("./a.out -e -c \"Comment\" file.mp3\n");
    printf("./a.out -e -all \"Title\" \"Artist\" \"Album\" \"Year\" \"Genre\" \"Comment\" file.mp3\n");
}

/* Entry point that routes the user command to either viewing or editing modes. */
int main(int argc, char *argv[])
{
    char *frame = NULL;

    if(argc < 3)
    {
        display_usage();
        return 0;
    }

    // View Tags 
    if(strcmp(argv[1], "-v") == 0)
    {
        view_tags(argv[2]);
    }

    // Play MP3 
    else if(strcmp(argv[1], "-p") == 0)
    {
        char command[300];

        sprintf(command, "cmd.exe /c start \"\" \"%s\"", argv[2]);

        printf("Playing: %s\n", argv[2]);

        system(command);
    }

    // Edit Tags 
    else if(strcmp(argv[1], "-e") == 0)
    {
        if(argc == 10 && strcmp(argv[2], "-all") == 0)
        {
            edit_tags(argv[9], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
            return 0;
        }

        if(argc != 5)
        {
            display_usage();
            return 0;
        }

        if(strcmp(argv[2], "-t") == 0)
            frame = "TIT2";
        else if(strcmp(argv[2], "-a") == 0)
            frame = "TPE1";
        else if(strcmp(argv[2], "-A") == 0)
            frame = "TALB";
        else if(strcmp(argv[2], "-y") == 0)
            frame = "TYER";
        else if(strcmp(argv[2], "-m") == 0)
            frame = "TCON";
        else if(strcmp(argv[2], "-c") == 0)
            frame = "COMM";
        else
        {
            printf("Invalid edit option\n");
            return 0;
        }

        edit_tag(argv[4], frame, argv[3]);
    }
    else
    {
        display_usage();
    }

    return 0;
}