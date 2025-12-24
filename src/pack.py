import py7zr
from pathlib import Path

def compress(input_path: str) -> str:
  input_file = Path(input_path)

  if not input_file.exists():
    raise FileNotFoundError(f"No existe el archivo: {input_file}")

  output_file = input_file.with_suffix(".fvax")

  with py7zr.SevenZipFile(output_file, 'w') as archive:
    archive.write(input_file, arcname=input_file.name)

  return str(output_file)
