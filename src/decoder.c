/* decoder.c
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

int fvax_decode(const char *ruta_entrada, const char *ruta_salida)
{
	FILE *archivo = fopen(ruta_entrada, "rb");
	if (!archivo)
	{
		fprintf(stderr, "\x1b[38;2;255;89;89mError: Cannot open FVAX file '%s'.\x1b[0m\n", ruta_entrada);
		return (1);
	}
	header_fvax header;
	if (fread(&header, 1, sizeof(header), archivo) != sizeof(header))
	{
		fclose(archivo);
		fprintf(stderr, "\x1b[38;2;255;89;89mError: Cannot read FVAX header.\x1b[0m\n");
		return (1);
	}
	if (memcmp(header.header, HEADER_FVAX, 6) != 0)
	{
		fclose(archivo);
		fprintf(stderr, "\x1b[38;2;255;89;89mError: Invalid FVAX magic header.\x1b[0m\n");
		return (1);
	}
	const char *video_temp = "tmp_dec_video.ivf";
	const char *audio_temp = "tmp_dec_audio.opus";
	if (header.tamano_video == 0 || header.pos_video == 0)
	{
		fclose(archivo);
		fprintf(stderr, "\x1b[38;2;255;89;89mError: FVAX file contains no video payload.\x1b[0m\n");
		return (1);
	}
	FILE *video_salida = fopen(video_temp, "wb");
    if (!video_salida)
	{
		fclose(archivo);
		fprintf(stderr, "\x1b[38;2;255;89;89mError: Cannot create temp video file.\x1b[0m\n");
		return (1);
	}
	fseek(archivo, (long)header.pos_video, SEEK_SET);
	uint64_t bytes_restantes = header.tamano_video;
	unsigned char buffer[8192];
	while (bytes_restantes > 0)
	{
		size_t chunk = bytes_restantes > sizeof(buffer) ? sizeof(buffer) : (size_t)bytes_restantes;
		size_t bytes_leidos = fread(buffer, 1, chunk, archivo);
		if (bytes_leidos == 0)
			break;
		fwrite(buffer, 1, bytes_leidos, video_salida);
		bytes_restantes -= bytes_leidos;
	}
	fclose(video_salida);
	int tiene_audio = (header.pos_audio != 0 && header.tamano_audio != 0);
	if (tiene_audio)
	{
		FILE *out_audio = fopen(audio_temp, "wb");
		if (!out_audio)
		{
			fclose(archivo);
			fprintf(stderr, "\x1b[38;2;255;89;89mError: Cannot create temp audio file.\x1b[0m\n");
			remove(video_temp);
			return (1);
		}
		fseek(archivo, (long)header.pos_audio, SEEK_SET);
		bytes_restantes = header.tamano_audio;
		while (bytes_restantes > 0)
		{
			size_t chunk = bytes_restantes > sizeof(buffer) ? sizeof(buffer) : (size_t)bytes_restantes;
			size_t bytes_leidos = fread(buffer, 1, chunk, archivo);
			if (bytes_leidos == 0)
				break;
			fwrite(buffer, 1, bytes_leidos, out_audio);
			bytes_restantes -= bytes_leidos;
		}
		fclose(out_audio);
	}
	fclose(archivo);
	char comando[2048];
	if (tiene_audio)
	{
		snprintf
		(
			comando,
			sizeof(comando),
			"ffmpeg -y -i \"%s\" -i \"%s\" -c:v copy -c:a copy \"%s\"",
			video_temp,
			audio_temp,
			ruta_salida
		);
	}
	else
	{
		snprintf
		(
			comando,
			sizeof(comando),
			"ffmpeg -y -i \"%s\" -c:v copy \"%s\"",
			video_temp,
			ruta_salida
		);
	}
	int resultado = system(comando);
	remove(video_temp);
	if (tiene_audio)
		remove(audio_temp);
	if (resultado != 0)
	{
		fprintf(stderr, "\x1b[38;2;255;89;89mDecoding failed (ffmpeg error).\x1b[0m\n");
		return (1);
    }
	return (0);
}
// FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
