/* converter.c
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

int fvax_convert(const char *input_ruta, char **output_ruta) 
{
    size_t len = strlen(input_ruta);
    char *ivf_ruta = malloc(len + 5);
    if (!ivf_ruta) 
    {
        printf("Memory allocation failed\n");
        return (1);
    }
    strcpy(ivf_ruta, input_ruta);
    char *dot = strrchr(ivf_ruta, '.');
    if (dot)
        *dot = '\0';
    strcat(ivf_ruta, ".ivf");
    *output_ruta = malloc(len + 6);
    if (!*output_ruta)
    {
        printf("Memory allocation failed\n");
        free(ivf_ruta);
        return (2);
    }
    strcpy(*output_ruta, input_ruta);
    dot = strrchr(*output_ruta, '.');
    if (dot)
        *dot = '\0';
    strcat(*output_ruta, ".fvax");
    char command[4096];
    int nbr = snprintf(command, sizeof(command),
        "ffmpeg -y -i \"%s\" -c:v libsvtav1 -crf 40 -preset 8 -an -f ivf \"%s\"", input_ruta, ivf_ruta);
    if (nbr < 0 || (size_t)nbr >= sizeof(command)) 
    {
        printf("Failed to build ffmpeg command\n");
        free(ivf_ruta);
        free(*output_ruta);
        return (3);
    }
    int ret = system(command);
    if (ret != 0) 
    {
        printf("ffmpeg command failed\n");
        free(ivf_ruta);
        free(*output_ruta);
        return (4);
    }
    int res = fvax_compress(ivf_ruta, *output_ruta);
    if (res != 0) 
    {
        printf("FVAX compression failed with code %d\n", res);
        free(ivf_ruta);
        free(*output_ruta);
        *output_ruta = NULL;
        return (res);
    }
    remove(ivf_ruta);
    free(ivf_ruta);
    return (0);
}
// FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
