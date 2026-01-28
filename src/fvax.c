/* fvax.c
    ________ ___      ___ ________     ___    ___ 
   |\  _____\\  \    /  /|\   __  \   |\  \  /  /|
   \ \  \__/\ \  \  /  / | \  \|\  \  \ \  \/  / /
    \ \   __\\ \  \/  / / \ \   __  \  \ \    / / 
     \ \  \_| \ \    / /   \ \  \ \  \  /     \/  
      \ \__\   \ \__/ /     \ \__\ \__\/___/\__\  
       \|__|    \|__|/       \|__|\|__/___/ /\ _\ 
    
    FVAX and all related titles and logos are trademarks of FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
    FVAX is licensed under the AGPLv3. More information at "https://github.com/neofodere/fvax/blob/main/LICENSE".
*/

#include "fvax.h"

static void imprimir_cabecera(void)
{
	printf("    ________ ___      ___ ________     ___    ___ \n");
	printf("   |\\  _____\\\\  \\    /  /|\\   __  \\   |\\  \\  /  /|\n");
	printf("   \\ \\  \\__/\\ \\  \\  /  / | \\  \\|\\  \\  \\ \\  \\/  / /\n");
	printf("    \\ \\   __\\\\ \\  \\/  / / \\ \\   __  \\  \\ \\    / / \n");
	printf("     \\ \\  \\_| \\ \\    / /   \\ \\  \\ \\  \\  /     \\/  \n");
	printf("      \\ \\__\\   \\ \\__/ /     \\ \\__\\ \\__\\/___/\\__\\  \n");
	printf("       \\|__|    \\|__|/       \\|__|\\|__/___/ /\\ _\\ \n");
	printf("\x1b[38;2;125;125;125m<== FVAX (Fod Video-Audio eXperience) - FODSOFT(TM) ==>\x1b[0m\n");
}

static void mostrar_ayuda(void)
{
	printf("Usage:\n");
	printf("  fvax encode <input_video> <output.fvax>\n");
	printf("  fvax decode <input.fvax> <output_video>\n");
	printf("\nExamples:\n");
	printf("  fvax encode example.mkv example.fvax\n");
	printf("  fvax decode example.fvax example.mkv\n");
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		mostrar_ayuda();
		return (1);
	}
	if (strcmp(argv[1], "encode") == 0)
	{
		if (argc != 4)
		{
			fprintf(stderr, "\x1b[38;2;255;89;89mError: Invalid encode syntax.\x1b[0m\n");
			mostrar_ayuda();
			return (1);
		}
		imprimir_cabecera();
		int resultado_encode = fvax_encode(argv[2], argv[3]);
		if (resultado_encode != 0)
		{
			fprintf(stderr, "\x1b[38;2;255;89;89mEncoding failed.\x1b[0m\n");
			return (1);
		}
		printf("\x1b[38;2;0;200;0mEncoding completed successfully.\x1b[0m\n");
		return (0);
    }

    else if (strcmp(argv[1], "decode") == 0)
    {
		if (argc != 4)
		{
			fprintf(stderr, "\x1b[38;2;255;89;89mError: Invalid decode syntax.\x1b[0m\n");
            mostrar_ayuda();
			return (1);
		}
		imprimir_cabecera();
		int resultado_decode = fvax_decode(argv[2], argv[3]);
		if (resultado_decode != 0)
		{
			fprintf(stderr, "\x1b[38;2;255;89;89mDecoding failed.\x1b[0m\n");
			return (1);
		}
		printf("\x1b[38;2;0;200;0mDecoding completed successfully.\x1b[0m\n");
		return (0);
    }

	else if (strcmp(argv[1], "/help") == 0 || strcmp(argv[1], "--help") == 0)
    {
        mostrar_ayuda();
        return (0);
    }
	else if (strcmp(argv[1], "/version") == 0 || strcmp(argv[1], "--version") == 0)
    {
        printf("FVAX v1.0\n(c) 2026 FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.\n");
        return (0);
    }
	fprintf(stderr, "\x1b[38;2;255;89;89mError: Unknown command '%s'.\x1b[0m\n", argv[1]);
	mostrar_ayuda();
	return (1);
}
// FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
