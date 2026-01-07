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

int fvax_convert(const char *input_path, char **output_path) 
{
    size_t len = strlen(input_path);
    char *ivf_path = malloc(len + 5);
    if (!ivf_path) 
    {
        printf("Memory allocation failed\n");
        return (1);
    }
    strcpy(ivf_path, input_path);
    char *dot = strrchr(ivf_path, '.');
    if (dot)
        *dot = '\0';
    strcat(ivf_path, ".ivf");
    *output_path = malloc(len + 6);
    if (!*output_path)
    {
        printf("Memory allocation failed\n");
        free(ivf_path);
        return (2);
    }
    strcpy(*output_path, input_path);
    dot = strrchr(*output_path, '.');
    if (dot)
        *dot = '\0';
    strcat(*output_path, ".fvax");
    char command[4096];
    int nbr = snprintf(command, sizeof(command),
        "ffmpeg -y -i \"%s\" -c:v libsvtav1 -an -f ivf \"%s\"", input_path, ivf_path);
    if (nbr < 0 || (size_t)nbr >= sizeof(command)) 
    {
        printf("Failed to build ffmpeg command\n");
        free(ivf_path);
        free(*output_path);
        return (3);
    }
    int ret = system(command);
    if (ret != 0) 
    {
        printf("ffmpeg command failed\n");
        free(ivf_path);
        free(*output_path);
        return (4);
    }
    int res = fvax_compress(ivf_path, *output_path);
    if (res != 0) 
    {
        printf("FVAX compression failed with code %d\n", res);
        free(ivf_path);
        free(*output_path);
        *output_path = NULL;
        return (res);
    }
    remove(ivf_path);
    free(ivf_path);
    return (0);
}
// FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.