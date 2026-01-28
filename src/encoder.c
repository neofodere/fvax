/* encoder.c
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

int limpiar_basura(const char *entrada, char *salida_raw, size_t tamano_salida)
{
	FILE *archivo_entrada = fopen(entrada, "rb");
	if (!archivo_entrada)
		return (-1);
	snprintf(salida_raw, tamano_salida, "%s.raw", entrada);
    FILE *archivo_salida = fopen(salida_raw, "wb");
    if (!archivo_salida)
    {
        fclose(archivo_entrada);
        return (-1);
    }
    const char *punto = strrchr(entrada, '.');
    if (punto && strcmp(punto, ".ivf") == 0)
    {
        if (fseek(archivo_entrada, 32, SEEK_SET) != 0)
        {
            fclose(archivo_entrada);
            fclose(archivo_salida);
            return (-1);
        }
        while (1)
        {
            uint8_t tamano_frame_le[4];
            if (fread(tamano_frame_le, 1, 4, archivo_entrada) != 4)
                break;
            uint32_t tamano_frame = (uint32_t)tamano_frame_le[0] | ((uint32_t)tamano_frame_le[1] << 8) | ((uint32_t)tamano_frame_le[2] << 16) | ((uint32_t)tamano_frame_le[3] << 24);
            if (fseek(archivo_entrada, 8, SEEK_CUR) != 0)
                break;
            if (tamano_frame == 0)
                continue;
            if (tamano_frame > 100 * 1024 * 1024)
                break;
            uint8_t *buffer = malloc((size_t)tamano_frame);
            if (!buffer)
                break;
            size_t bytes_leidos = fread(buffer, 1, tamano_frame, archivo_entrada);
            if (bytes_leidos != tamano_frame)
            {
                free(buffer);
                break;
            }
            if (fwrite(buffer, 1, tamano_frame, archivo_salida) != tamano_frame)
            {
                free(buffer);
                break;
            }
            free(buffer);
        }
    }
    else if (punto && strcmp(punto, ".opus") == 0)
    {
        uint8_t oggs[4];
        size_t cap_paquete_opus = 65536;
        uint8_t *paquete_opus = malloc(cap_paquete_opus);
        if (!paquete_opus)
        {
            fclose(archivo_entrada);
            fclose(archivo_salida);
            return (-1);
        }
        size_t pos_paquete = 0;
        while (fread(oggs, 1, 4, archivo_entrada) == 4)
        {
            if (memcmp(oggs, "OggS", 4) != 0)
                break;
            if (fseek(archivo_entrada, 22, SEEK_CUR) != 0)
                break;
            uint8_t num_segmentos;
            if (fread(&num_segmentos, 1, 1, archivo_entrada) != 1)
                break;
            if (num_segmentos == 0)
                continue;
            uint8_t tabla_segmento[255];
            if (fread(tabla_segmento, 1, num_segmentos, archivo_entrada) != num_segmentos)
                break;
            for (int pos = 0; pos < num_segmentos; pos++)
            {
                uint32_t tamano_segmento = tabla_segmento[pos];
                if (pos_paquete + tamano_segmento > cap_paquete_opus)
                {
                    size_t paquete_doble = cap_paquete_opus * 2;
                    while (pos_paquete + tamano_segmento > paquete_doble)
                        paquete_doble *= 2;
                    uint8_t *tmp = realloc(paquete_opus, paquete_doble);
                    if (!tmp)
                    {
                        free(paquete_opus);
                        fclose(archivo_entrada);
                        fclose(archivo_salida);
                        return (-1);
                    }
                    paquete_opus = tmp;
                    cap_paquete_opus = paquete_doble;
                }
                if (tamano_segmento > 0)
                {
                    if (tamano_segmento > 10 * 1024 * 1024)
                    {
                        free(paquete_opus);
                        fclose(archivo_entrada);
                        fclose(archivo_salida);
                        return (-1);
                    }
                    size_t bytes_leidos = fread(paquete_opus + pos_paquete, 1, tamano_segmento, archivo_entrada);
                    if (bytes_leidos != tamano_segmento)
                    {
                        free(paquete_opus);
                        fclose(archivo_entrada);
                        fclose(archivo_salida);
                        return (-1);
                    }
                    pos_paquete += tamano_segmento;
                }
                if (tamano_segmento < 255)
                {
                    if (pos_paquete > 0)
                    {
                        if (fwrite(paquete_opus, 1, pos_paquete, archivo_salida) != pos_paquete)
                        {
                            free(paquete_opus);
                            fclose(archivo_entrada);
                            fclose(archivo_salida);
                            return (-1);
                        }
                        pos_paquete = 0;
                    }
                    else
                        pos_paquete = 0;
                }
            }
        }
        if (pos_paquete > 0)
            fwrite(paquete_opus, 1, pos_paquete, archivo_salida);
        free(paquete_opus);
    }
    fclose(archivo_entrada);
    fclose(archivo_salida);
    return (0);
}

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
	const char *video_temp = "fvax_video_tmp.ivf";
	char video_limpio[256];
	const char *audio_temp = "fvax_audio_tmp.opus";
	char audio_limpio[256];
	int tiene_video = 0;
	int tiene_audio = 0;

	snprintf(comando, sizeof(comando),
		"ffprobe -v error -select_streams v:0 -show_entries stream=codec_type -of csv=p=0 \"%s\" > fvax_hasvideo.fvaxtmp", ruta_entrada);
	system(comando);
	FILE *archivo_metadatos = fopen("fvax_hasvideo.fvaxtmp", "r");
	if (archivo_metadatos)
	{
		char tipo[32];
		if (fscanf(archivo_metadatos, "%31s", tipo) == 1)
			tiene_video = 1;
		fclose(archivo_metadatos);
    }
    remove("fvax_hasvideo.fvaxtmp");
	if (tiene_video)
	{
		snprintf(comando, sizeof(comando),
			"ffmpeg -y -i \"%s\" -c:v libaom-av1 -crf 30 -b:v 0 -pix_fmt yuv420p -an \"%s\"", ruta_entrada, video_temp);
		if (system(comando) != 0)
		{
			fprintf(stderr, "\x1b[38;2;255;89;89mError: ffmpeg couldn’t encode the video.\x1b[0m\n");
			return (-1);
	    }
		if (limpiar_basura(video_temp, video_limpio, sizeof(video_limpio)) != 0)
		{
			fprintf(stderr, "\x1b[38;2;255;89;89mError: Failed cleaning IVF.\x1b[0m\n");
			return (-1);
		}
	}
	snprintf(comando, sizeof(comando),
		"ffmpeg -y -i \"%s\" -vn -c:a libopus -b:a 128k \"%s\"", ruta_entrada, audio_temp);
	if (system(comando) == 0)
		tiene_audio = 1;
	else
	{
		tiene_audio = 0;
		remove(audio_temp);
	}
	int ancho = 0;
	int alto = 0;
	double fps = 0.0;
	uint32_t total_frames = 0;
	uint32_t frecuencia_audio = 0;
	uint16_t canales_audio = 0;
	if (tiene_video)
	{
		snprintf(comando, sizeof(comando),
			"ffprobe -v error -select_streams v:0 -show_entries stream=width,height -of csv=p=0:s=x \"%s\" > fvax_res.fvaxtmp", ruta_entrada);
		system(comando);
		archivo_metadatos = fopen("fvax_res.fvaxtmp", "r");
		if (archivo_metadatos)
		{
			fscanf(archivo_metadatos, "%dx%d", &ancho, &alto);
			fclose(archivo_metadatos);
		}
		snprintf(comando, sizeof(comando),
			"ffprobe -v error -select_streams v:0 -show_entries stream=r_frame_rate -of csv=p=0 \"%s\" > fvax_fps.fvaxtmp", ruta_entrada);
		system(comando);
		archivo_metadatos = fopen("fvax_fps.fvaxtmp", "r");
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
			"ffprobe -v error -count_frames -select_streams v:0 -show_entries stream=nb_read_frames -of csv=p=0 \"%s\" > fvax_frames.fvaxtmp", ruta_entrada);
		system(comando);
		archivo_metadatos = fopen("fvax_frames.fvaxtmp", "r");
		if (archivo_metadatos)
		{
			fscanf(archivo_metadatos, "%u", &total_frames);
			fclose(archivo_metadatos);
		}
		if (total_frames == 0)
			total_frames = 1;
	}
    if (tiene_audio)
	{
		snprintf(comando, sizeof(comando),
			"ffprobe -v error -select_streams a:0 -show_entries stream=sample_rate,channels -of csv=p=0 \"%s\" > fvax_audio.fvaxtmp", ruta_entrada);
		system(comando);
		archivo_metadatos = fopen("fvax_audio.fvaxtmp", "r");
		if (archivo_metadatos)
		{
			fscanf(archivo_metadatos, "%u,%hu", &frecuencia_audio, &canales_audio);
			fclose(archivo_metadatos);
		}
		if (limpiar_basura(audio_temp, audio_limpio, sizeof(audio_limpio)) != 0)
		{
			fprintf(stderr, "\x1b[38;2;255;89;89mError: Failed cleaning Opus.\x1b[0m\n");
			return (-1);
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
		fprintf(stderr, "\x1b[38;2;255;89;89mError: The FVAX file could not be created.\x1b[0m\n");
		return (-1);
    }
	fwrite(&header, 1, sizeof(header), archivo_salida);
	if (tiene_video)
	{
		header.pos_video = ftell(archivo_salida);
		if (incrustar_bytes(archivo_salida, video_limpio, &header.tamano_video) != 0) 
		{ 
			fprintf(stderr, "\x1b[38;2;255;89;89mError: The video could not be embedded into the FVAX container.\x1b[0m\n");
			fclose(archivo_salida); 
			remove(video_limpio);
			if (tiene_audio)
				remove(audio_limpio);
			return (-1);
		}
	}
	else
	{
		header.pos_video = 0;
		header.tamano_video = 0;
	}
    if (tiene_audio)
	{
		header.pos_audio = ftell(archivo_salida);
		if (incrustar_bytes(archivo_salida, audio_limpio, &header.tamano_audio) != 0)
		{
			fprintf(stderr, "\x1b[38;2;255;89;89mError: The audio could not be embedded into the FVAX container.\x1b[0m\n");
			fclose(archivo_salida);
			if (tiene_video)
				remove(video_limpio);
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
	if (tiene_video)
	{
		remove("fvax_video_tmp.ivf");
		remove("fvax_video_tmp.ivf.raw");
		remove("fvax_res.fvaxtmp");
		remove("fvax_fps.fvaxtmp");
		remove("fvax_frames.fvaxtmp");
	}
	if (tiene_audio)
	{
		remove("fvax_audio_tmp.opus");
		remove("fvax_audio_tmp.opus.raw");
		remove("fvax_audio.fvaxtmp");
	}
	return (0);
}
// FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
