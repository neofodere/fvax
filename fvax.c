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

int fvax_convert(const char *input_path, char **fvax_output_path);

int main(int argc, char **argv) 
{
    if (argc == 3 && strcmp(argv[1], "convert") == 0) 
    {
        const char *input_path = argv[2];
        char *fvax_path = NULL;
        int result = fvax_convert(input_path, &fvax_path);
        if (result != 0) 
        {
            printf("Conversion to FVAX failed with code %d\n", result);
            return (result);
        }
        printf("Conversion to FVAX completed successfully: %s\n", fvax_path);
        free(fvax_path);
        return (0);
    }
    if (argc != 2) 
    {
        printf("Usage:\n");
        printf("  fvax <input_ivf>\n");
        printf("  fvax convert <input_video>\n");
        return (1);
    }
    const char *input_path = argv[1];
    size_t len = strlen(input_path);
    char *output_path = malloc(len + 6);
    if (!output_path) 
    {
        printf("Memory allocation failed\n");
        return (2);
    }
    strcpy(output_path, input_path);
    char *dot = strrchr(output_path, '.');
    if (dot)
        *dot = '\0';
    strcat(output_path, ".fvax");
    int result = fvax_compress(input_path, output_path);
    if (result != 0) 
    {
        printf("Compression failed with code %d\n", result);
        free(output_path);
        return (result);
    }
    printf("FVAX compression completed successfully: %s\n", output_path);
    free(output_path);
    return (0);
}
// FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.