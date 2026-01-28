/*
    ________ ___      ___ ________     ___    ___ 
   |\  _____\\  \    /  /|\   __  \   |\  \  /  /|
   \ \  \__/\ \  \  /  / | \  \|\  \  \ \  \/  / /
    \ \   __\\ \  \/  / / \ \   __  \  \ \    / / 
     \ \  \_| \ \    / /   \ \  \ \  \  /     \/  
      \ \__\   \ \__/ /     \ \__\ \__\/___/\__\  
       \|__|    \|__|/       \|__|\|__/___/ /\ _\ 
    
    FVAX and all related titles and logos are trademarks of FODSOFT™ (Néo Foderé de Frutos). All rights reserved.
    FVAX is licensed under the AGPLv3. More information at "https://github.com/neofodere/fvax/blob/main/LICENSE".
*/

#ifndef FVAX_H
#define FVAX_H

#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define FVAX_MAGIC "FVAX"
#define FVAX_VERSION "v1.0"
#define FVAX_HEADER_SIZE

typedef struct
{
    char magic[4];
    char version[8];
    uint16_t header_size;
    uint32_t flags;
    uint16_t width;
    uint16_t height;
    uint32_t fps_num;
    uint32_t fps_den;
    uint32_t frame_count;
    uint64_t file_size;
    uint32_t header_crc;
    uint8_t reserved[32];
} fvax_header;

int fvax_encode(const char *input_path, const char *output_path);
int fvax_convert(const char *input_path, char **output_path);

#endif
// FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
