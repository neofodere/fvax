import sys
from pack import compress

def main():
  if len(sys.argv) < 2:
    print("Uso: python fvax.py <archivo_de_video>")
    return
    
  input_path = sys.argv[1]
  output_path = compress(input_path)
  print(f"Archivo comprimido como: {output_path}")

if __name__ == "__main__":
  main()

# FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
