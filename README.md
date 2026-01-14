# FVAX
<img src="images/logo_fvax.png" width="575.5" height="auto">

## 📖 Description
>[!WARNING]
>FVAX is currently an experimental project in development, and not all features are available yet.

FVAX (Fod Video-Audio eXperience) is an audio and video container format developed by Néo Foderé de Frutos under the FODSOFT™ brand.

FVAX uses <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/84/AV1_logo_2018.svg/1200px-AV1_logo_2018.svg.png" width="38" height="auto"> (***AV1***) as its video codec and <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/02/Opus_logo2.svg/250px-Opus_logo2.svg.png" width="48" height="auto"> (***Opus***) as its audio codec.

## <img src="https://raw.githubusercontent.com/neofodere/fvax-player/main/images/logo_fvax_player.png" width="64" height="auto"> How to play audio and video files in FVAX format
FVAX Player™ is coming...

## <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/06/AGPLv3_Logo.svg/250px-AGPLv3_Logo.svg.png" width="64" height="auto"> License
FVAX is under the ***AGPLv3*** license. For more details, click [here](https://raw.githubusercontent.com/neofodere/fvax/refs/heads/main/LICENSE).

## 📁 Project structure
`src/Makefile`: Build automation file.

`src/compressor.c`: The format's compressor, which is responsible for removing fixed patterns.

`src/converter.c`: The file responsible for converting any video file to the FVAX format and AV1 codec, passing through the compressor **(src/compressor.c)**.

`src/fvax.c`: The entry point of the project.

`src/fvax.h`: The header containing the definitions, declarations, and libraries.

**© 2026 FODSOFT™. Néo Foderé de Frutos. All rights reserved.**
<!-- FODSOFT(TM). Neo Fodere de Frutos. All rights reserved. -->
