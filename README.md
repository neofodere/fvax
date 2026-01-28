# <img src="https://resources.fodsoft.com/images/ext/icono_archivo_fvax.png" width="32" height="auto"> FVAX
<img src="https://resources.fodsoft.com/images/ext/logo_fvax_b.png" width="512" height="auto">

## 📖 Description
FVAX (Fod Video-Audio eXperience) is an audio and video container format developed by Néo Foderé de Frutos under the FODSOFT™ brand.

FVAX uses <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/84/AV1_logo_2018.svg/1200px-AV1_logo_2018.svg.png" width="38" height="auto"> (***AV1***) as its video codec and <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/02/Opus_logo2.svg/250px-Opus_logo2.svg.png" width="48" height="auto"> (***Opus***) as its audio codec.

## <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/06/AGPLv3_Logo.svg/250px-AGPLv3_Logo.svg.png" width="64" height="auto"> License
FVAX is under the ***AGPLv3*** license. 

### 📜 Conditions
- You must preserve the original copyright notice.  
All redistributions or modified versions of FVAX must keep the line:
`© FODSOFT™. Néo Foderé de Frutos. All rights reserved.`

- You must keep the **AGPLv3 license**.  
Any modified version of FVAX must be released under the same license, with no exceptions.

- You must **provide the full source code** of any modified version.  
This applies whether you distribute binaries or run FVAX as part of a network service.

- You must clearly state any changes you made.  
Modifications must be documented so users know what differs from the original FVAX.

- **You cannot rebrand FVAX as a proprietary or closed-source product.**  
The AGPLv3 prevents anyone from taking FVAX, modifying it, and releasing it under a different or restrictive license.

- You must give proper attribution.  
Any public use, redistribution, or fork must credit the original author and project name.

- You cannot remove trademarks or authorship references.  
The **FODSOFT™** and **Néo Foderé de Frutos** names and FVAX branding must remain intact in all derived works.

- You must provide users with access to the source when FVAX is used over a network.  
This closes the “SaaS loophole” and ensures transparency even in server-side deployments.

For more details, click [here](https://raw.githubusercontent.com/neofodere/fvax/refs/heads/main/LICENSE).

## 📁 Project structure
`src/Makefile`: Build automation file.

`src/encoder.c`: The file responsible for converting any video file into the FVAX container using the AV1 and Opus codecs.

`src/decoder.c`: The file responsible for converting any FVAX file to a standard format.

`src/fvax.c`: The entry point of the project.

`src/fvax.h`: The header containing the definitions, declarations, and libraries.

**© 2026 FODSOFT™. Néo Foderé de Frutos. All rights reserved.**
<!-- FODSOFT(TM). Neo Fodere de Frutos. All rights reserved. -->
