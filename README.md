# FVAX
<img src="images/logo_fvax.png" width="575.5" height="auto">

# 📖 Description
>[!WARNING]
>FVAX is currently an experimental project.

FVAX (Fod Video-Audio eXperience) is a powerful and efficient multimedia file format currently in development by Néo Foderé de Frutos under the FODSOFT™ brand.

## 📁 Project structure
`src/Makefile`: Build automation file.

`src/compressor.c`: The format's compressor, which is responsible for removing fixed patterns.

`src/converter.c`: The file responsible for converting any video file to the FVAX format and AV1 codec, passing through the compressor **(src/compressor.c)**.

`src/fvax.c`: The entry point of the project.

`src/fvax.h`: The header containing the definitions, declarations, and libraries.

**© 2026 FODSOFT™. Néo Foderé de Frutos. All rights reserved.**
<!-- FODSOFT(TM). Neo Fodere de Frutos. All rights reserved. -->