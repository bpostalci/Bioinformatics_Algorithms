#pragma once

#include "Typedefs.h"

void fill_buffer(char **buffer, const char *file_path);
void write_buffer_1d(char *buffer, const char *file_path, const char *extension, const char *mode);
void write_buffer_2d(char **buffer, uint_t buffer_len, const char *file_path, const char *extension, const char *mode);