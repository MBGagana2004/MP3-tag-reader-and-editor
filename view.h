/*Name : MB Gagana
  date : 20-06-2026
  batch: 26001_005
  description: Developed a command-line application in C to read and edit ID3v2 metadata of MP3 files.
Implemented binary file handling to access and modify tags such as Title, Artist, Album, Year, Genre, and Comment.
Used structures, file pointers, and command-line arguments to perform efficient metadata operations.
Preserved the original audio data while updating only the required metadata fields.
Followed a modular programming approach with proper error handling and Makefile-based project organization.
Strengthened skills in C programming, binary file processing, and Linux development.*/


#ifndef VIEW_H
#define VIEW_H

#include "common.h"


// Color codes for terminal output 
#define CYAN    "\033[1;36m"
#define BLUE    "\033[1;34m"
#define YELLOW  "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define GREEN   "\033[1;32m"
#define RESET   "\033[0m"

int view_tags(char *filename);

//Open the MP3 file in read mode 
Status open_mp3_file(char *filename, ViewInfo *viewInfo);

// Verify whether the file contains a valid ID3 header 
Status check_id3_header(ViewInfo *viewInfo);

//Display all MP3 tag information 
Status view_mp3_tags(ViewInfo *viewInfo);

// Read frame data from the MP3 file 
Status read_frame_data(FILE *fptr, char *data);

// Read and display the Title tag (TIT2) 
Status read_title(ViewInfo *viewInfo);

// Read and display the Artist tag (TPE1) 
Status read_artist(ViewInfo *viewInfo);

//Read and display the Album tag (TALB) 
Status read_album(ViewInfo *viewInfo);

// Read and display the Year tag (TYER) 
Status read_year(ViewInfo *viewInfo);

//Read and display the Genre tag (TCON) 
Status read_genre(ViewInfo *viewInfo);

// Read and display the Comment tag (COMM) 
Status read_comment(ViewInfo *viewInfo);

#endif