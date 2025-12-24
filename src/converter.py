import py7zr
from pathlib import Path
import os

CHUNK_SIZE = 256 * 1024

def preprocess_chunk(chunk: bytes, prev: bytes | None) -> bytes:
    if prev:
        chunk = bytes((c - p) % 256 for c, p in zip(chunk, prev))
    shuffled = bytearray()
    shuffled.extend(chunk[0::2])
    shuffled.extend(chunk[1::2])
    return bytes(shuffled)

def compress(input_path: str) -> str:
    input_file = Path(input_path)
    if not input_file.exists():
        raise FileNotFoundError(f"No existe el archivo: {input_file}")

    output_file = input_file.with_suffix(".fvax")
    temp_path = input_file.with_suffix(".fvax.tmp")
    prev = None

    with open(input_file, "rb") as f_in, open(temp_path, "wb") as f_out:
        while True:
            chunk = f_in.read(CHUNK_SIZE)
            if not chunk:
                break
            processed = preprocess_chunk(chunk, prev)
            f_out.write(processed)
            prev = chunk

    with py7zr.SevenZipFile(output_file, 'w', filters=[{
        "id": py7zr.FILTER_LZMA2,
        "preset": 9,
        "dict_size": 1 << 27
    }]) as archive:
        archive.write(temp_path, arcname="data.bin")

    os.remove(temp_path)
    return str(output_file)

# FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
