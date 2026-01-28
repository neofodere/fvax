/* encoder.c
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

static int incrustar_bytes(FILE *archivo_fvax, const char *archivo_temp, uint64_t *total_bytes)
{
	FILE *archivo = fopen(archivo_temp, "rb");
	if (!archivo)
		return (-1);

	uint8_t buffer[8192];
	size_t bytes_leidos;
	uint64_t bytes_copiados = 0;

	while ((bytes_leidos = fread(buffer, 1, sizeof(buffer), archivo)) > 0)
	{
		fwrite(buffer, 1, bytes_leidos, archivo_fvax);
		bytes_copiados += bytes_leidos;
	}
	fclose(archivo);
	if (total_bytes)
		*total_bytes = bytes_copiados;
	return (0);
}

int fvax_encode(const char *ruta_entrada, const char *ruta_salida)
{
	FILE *archivo_salida = NULL;
	header_fvax header;
	char comando[2048];
	const char *video_temp = "tmp_fvax_video.ivf";
	const char *audio_temp = "tmp_fvax_audio.opus";

	snprintf(comando, sizeof(comando),
		"ffmpeg -y -i \"%s\" -c:v libaom-av1 -crf 30 -b:v 0 -pix_fmt yuv420p -an \"%s\"", ruta_entrada, video_temp);
	if (system(comando) != 0)
	{
		fprintf(stderr, "Error: ffmpeg couldn’t encode the video.\n");
		return (-1);
    }
    snprintf(comando, sizeof(comando),
		"ffmpeg -y -i \"%s\" -vn -c:a libopus -b:a 128k \"%s\"", ruta_entrada, audio_temp);
	
	int tiene_audio = (system(comando) == 0);
	if (!tiene_audio)
		remove(audio_temp);
	int ancho = 0;
	int alto = 0;
	double fps = 0.0;
	uint32_t total_frames = 0;
	uint32_t frecuencia_audio = 0;
	uint16_t canales_audio = 0;

	snprintf(comando, sizeof(comando),
		"ffprobe -v error -select_streams v:0 -show_entries stream=width,height -of csv=p=0:s=x \"%s\" > tmp_fvax_res.txt",
		ruta_entrada);
	system(comando);
	FILE *archivo_metadatos = fopen("tmp_fvax_res.txt", "r");
	if (archivo_metadatos)
	{
		fscanf(archivo_metadatos, "%dx%d", &ancho, &alto);
		fclose(archivo_metadatos);
	}
	snprintf(comando, sizeof(comando),
		"ffprobe -v error -select_streams v:0 -show_entries stream=r_frame_rate -of csv=p=0 \"%s\" > tmp_fvax_fps.txt",
		ruta_entrada);
	system(comando);
	archivo_metadatos = fopen("tmp_fvax_fps.txt", "r");
	if (archivo_metadatos)
	{
		int num = 0, den = 1;
		if (fscanf(archivo_metadatos, "%d/%d", &num, &den) == 2 && den != 0)
			fps = (double)num / (double)den;
		if (fps <= 0.0) 
			fps = 30.0;
		fclose(archivo_metadatos);
	}
	snprintf(comando, sizeof(comando),
		"ffprobe -v error -count_frames -select_streams v:0 -show_entries stream=nb_read_frames -of csv=p=0 \"%s\" > tmp_fvax_frames.txt",
		ruta_entrada);
	system(comando);
	archivo_metadatos = fopen("tmp_fvax_frames.txt", "r");
	if (archivo_metadatos)
	{
		fscanf(archivo_metadatos, "%u", &total_frames);
		fclose(archivo_metadatos);
	}
	if (total_frames == 0)
		total_frames = 1;
    if (tiene_audio)
	{
		snprintf(comando, sizeof(comando),
			"ffprobe -v error -select_streams a:0 -show_entries stream=sample_rate,channels -of csv=p=0 \"%s\" > tmp_fvax_audio.txt",
			ruta_entrada);
		system(comando);
		archivo_metadatos = fopen("tmp_fvax_audio.txt", "r");
		if (archivo_metadatos)
		{
			fscanf(archivo_metadatos, "%u,%hu", &frecuencia_audio, &canales_audio);
			fclose(archivo_metadatos);
		}
    }
	memset(&header, 0, sizeof(header));
	memcpy(header.header, HEADER_FVAX, 6);
	strncpy(header.copyright, COPYRIGHT_FVAX, sizeof(header.copyright) - 1);
	header.copyright[sizeof(header.copyright) - 1] = '\0';
	header.tamano_header = (uint16_t)sizeof(header_fvax);
	header.ancho = (uint16_t)ancho;
	header.alto = (uint16_t)alto;
	header.canales_audio = canales_audio;
	header.frecuencia_audio= frecuencia_audio;
	header.denominador_fps = 1000;
	header.numerador_fps = (uint32_t)(fps * 1000.0 + 0.5);
	header.total_frames = total_frames;
    archivo_salida = fopen(ruta_salida, "wb");
	if (!archivo_salida)
	{
		fprintf(stderr, "Error: The FVAX file could not be created.\n");
		return (-1);
    }
	fwrite(&header, 1, sizeof(header), archivo_salida);
	header.pos_video = ftell(archivo_salida);
	if (incrustar_bytes(archivo_salida, video_temp, &header.tamano_video) != 0) 
	{ 
		fprintf(stderr, "Error: The video could not be embedded into the FVAX container.\n"); 
		fclose(archivo_salida); 
		remove(video_temp);
		if (tiene_audio)
			remove(audio_temp);
		return (-1); 
	}
    if (tiene_audio)
	{
		header.pos_audio = ftell(archivo_salida);
		if (incrustar_bytes(archivo_salida, audio_temp, &header.tamano_audio) != 0)
		{
			fprintf(stderr, "Error: The audio could not be embedded into the FVAX container.\n");
			fclose(archivo_salida);
			return (-1);
		}
	}
	else 
	{
		header.pos_audio = 0;
		header.tamano_audio = 0;
	}
	header.tamano_archivo = (uint64_t)ftell(archivo_salida);
	fseek(archivo_salida, 0, SEEK_SET);
	fwrite(&header, 1, sizeof(header), archivo_salida);
	fclose(archivo_salida);
	remove("tmp_fvax_video.ivf");
	remove("tmp_fvax_audio.opus");
	remove("tmp_fvax_res.txt");
	remove("tmp_fvax_fps.txt");
	remove("tmp_fvax_frames.txt");
	if (tiene_audio)
		remove("tmp_fvax_audio.txt");
	return (0);
}
// FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
