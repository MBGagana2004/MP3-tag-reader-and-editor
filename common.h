#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

/* Shared status values used by the viewer and editor modules. */
typedef enum {
    STATUS_OK = 0,
    STATUS_ERROR = 1
} Status;

/* Stores the tag values read from an MP3 file. */
typedef struct {
    char title[256];
    char artist[256];
    char album[256];
    char year[16];
    char genre[64];
    char comment[256];
} ViewInfo;

/* Stores the tag values that will be written back to an MP3 file. */
typedef struct {
    char title[256];
    char artist[256];
    char album[256];
    char year[16];
    char genre[64];
    char comment[256];
} EditInfo;

#endif

