#ifndef EDIT_H
#define EDIT_H

#include "common.h"

int edit_tag(char *filename, char *frame, char *value);
int edit_tags(char *filename, char *title, char *artist, char *album, char *year, char *genre, char *comment);

// Open MP3 file and temporary file for editing
Status open_edit_files(char *filename, EditInfo *editInfo);

// Edit title tag (TIT2)
Status edit_title(EditInfo *editInfo, char *new_title);

// Edit artist tag (TPE1)
Status edit_artist(EditInfo *editInfo, char *new_artist);

// Edit album tag (TALB)
Status edit_album(EditInfo *editInfo, char *new_album);

// Edit year tag (TYER)
Status edit_year(EditInfo *editInfo, char *new_year);

// Edit genre tag (TCON)
Status edit_genre(EditInfo *editInfo, char *new_genre);

// Edit comment tag (COMM)
Status edit_comment(EditInfo *editInfo, char *new_comment);

// Common function to edit any frame
Status edit_frame(EditInfo *editInfo, char *frame_name, char *new_data);

// Copy remaining MP3 data after editing
Status copy_remaining_data(FILE *src, FILE *dest);

// Replace original MP3 file with updated file
Status replace_original_file(char *mp3_file);

// Search for a frame in the MP3 file
Status find_frame(FILE *fptr, char *frame_name);

#endif