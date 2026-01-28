/* fvax.h
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

#ifndef FVAX_H
#define FVAX_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADER_FVAX "[FVAX]"
#define COPYRIGHT_FVAX "(c) - FODSOFT(TM). Neo Fodere de Frutos. All rights reserved."

typedef struct
{
	char header[6];
	char copyright[61];
	uint8_t  reserva[32];
	uint16_t tamano_header;
	uint16_t ancho;
	uint16_t alto;
	uint16_t canales_audio;
	uint32_t numerador_fps;
	uint32_t denominador_fps;
	uint32_t total_frames;
	uint32_t frecuencia_audio;
	uint64_t pos_video;
	uint64_t tamano_video;
	uint64_t pos_audio;
	uint64_t tamano_audio;
	uint64_t tamano_archivo;
} header_fvax;

int fvax_encode(const char *ruta_entrada, const char *ruta_salida);
int fvax_decode(const char *ruta_entrada, const char *ruta_salida);

#endif
// FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
