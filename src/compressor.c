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

#include "fvax.h"

int fvax_compress(const char *input_path, const char *output_path) 
{
    FILE *input = fopen(input_path, "rb");
    if (!input) 
    {
        printf("Failed to open input file\n");
        return (1);
    }
    FILE *output = fopen(output_path, "wb");
    if (!output) 
    {
        printf("Failed to open output file\n");
        fclose(input);
        return (2);
    }
    unsigned char ivf_header[32];
    if (fread(ivf_header, 1, 32, input) != 32) 
    {
        printf("Failed to read IVF header\n");
        fclose(input);
        fclose(output);
        return (3);
    }
    if (memcmp(ivf_header, "DKIF", 4) != 0) 
    {
        printf("Input file is not a valid IVF container\n");
        fclose(input);
        fclose(output);
        return (4);
    }
    fvax_header fh;
    memset(&fh, 0, sizeof(fvax_header));
    memcpy(fh.magic, FVAX_MAGIC, 4);
    strncpy(fh.version, FVAX_VERSION, sizeof(fh.version) - 1);
    fh.version[sizeof(fh.version) - 1] = '\0';
    fh.header_size = sizeof(fvax_header);
    fh.flags = 0;
    fh.width  = ivf_header[12] | (ivf_header[13] << 8);
    fh.height = ivf_header[14] | (ivf_header[15] << 8);
    fh.fps_num = ivf_header[16] | (ivf_header[17] << 8) | (ivf_header[18] << 16) | (ivf_header[19] << 24);
    fh.fps_den = ivf_header[20] | (ivf_header[21] << 8) | (ivf_header[22] << 16) | (ivf_header[23] << 24);
    fh.frame_count = ivf_header[24] | (ivf_header[25] << 8) | (ivf_header[26] << 16) | (ivf_header[27] << 24);
    fh.file_size = 0;
    fh.header_crc = 0;
    fwrite(&fh, 1, sizeof(fvax_header), output);
    while (1) 
    {
        unsigned char frame_header[12];
        size_t read_bytes = fread(frame_header, 1, 12, input);
        if (read_bytes == 0)
            break;
        if (read_bytes != 12) 
        {
            printf("Corrupted IVF frame header\n");
            fclose(input);
            fclose(output);
            return (5);
        }
        uint32_t frame_size = frame_header[0] | (frame_header[1] << 8) |
            (frame_header[2] << 16) | (frame_header[3] << 24);
        if (frame_size > 100000000) 
        {
            printf("Frame size too large\n");
            fclose(input);
            fclose(output);
            return (8);
        }
        unsigned char *frame = malloc(frame_size);
        if (!frame) 
        {
            printf("Memory allocation failed\n");
            fclose(input);
            fclose(output);
            return (6);
        }
        if (fread(frame, 1, frame_size, input) != frame_size) 
        {
            printf("Failed to read frame data\n");
            free(frame);
            fclose(input);
            fclose(output);
            return (7);
        }
        fwrite(frame, 1, frame_size, output);
        free(frame);
    }
    fclose(input);
    uint64_t file_size = ftell(output);
    fseek(output, offsetof(fvax_header, file_size), SEEK_SET);
    fwrite(&file_size, 1, sizeof(uint64_t), output);
    fclose(output);
    return (0);
}
// FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.