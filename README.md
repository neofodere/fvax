# <img src="https://resources.fodsoft.com/images/ext/icono_archivo_fvax.png" width="32" height="auto"> FVAX
<img src="https://resources.fodsoft.com/images/ext/logo_fvax_b.png" width="512" height="auto">

## 📖 Description
FVAX (Fod Video-Audio eXperience) is an audio and video container format developed by Néo Foderé de Frutos under the FODSOFT™ brand.

FVAX uses <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/84/AV1_logo_2018.svg/1200px-AV1_logo_2018.svg.png" width="38" height="auto"> (***AV1***) as its video codec and <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/02/Opus_logo2.svg/250px-Opus_logo2.svg.png" width="48" height="auto"> (***Opus***) as its audio codec.

The FVAX encoder works by using **FFmpeg** to create a **WebM** and an **Ogg Opus** separately, and then combining them efficiently.

## 📚 Dependencies
### For usage:
- **FFmpeg** (5.0 or later recommended)

### For compiling:
- **GCC** (15 or later recommended)

## 🚀 Setup guide
>[!NOTE]
>I recommend using MSYS2 to compile or use FVAX on Windows.



## 📂 Source code structure
File | Description |
|----|-------------|
| src/**Makefile** | Build automation file. |
| src/**encoder.c** | The responsible for converting any video file into the FVAX container. |
| src/**decoder.c** | The responsible for converting any FVAX file to a standard format. |
| src/**fvax.c** | The entry point of the program. |
| src/**fvax.h** | The header containing the definitions, the header struct... |

## <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/06/AGPLv3_Logo.svg/250px-AGPLv3_Logo.svg.png" width="64" height="auto"> License
FVAX is under the ***AGPLv3*** license. FVAX is under the ***AGPLv3*** license. This means that if you want to distribute or use FVAX, you must comply with all the terms of the license.

For more details, click [here](https://raw.githubusercontent.com/neofodere/fvax/refs/heads/main/LICENSE).

## 

**FVAX and all related titles and logos are property of FODSOFT™. Néo Foderé de Frutos.**

**© 2026 FODSOFT™. Néo Foderé de Frutos. All rights reserved.**
<!-- FODSOFT(TM). Neo Fodere de Frutos. All rights reserved. -->
