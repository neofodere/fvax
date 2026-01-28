#   Makefile
#    ________ ___      ___ ________     ___    ___ 
#   |\  _____\\  \    /  /|\   __  \   |\  \  /  /|
#   \ \  \__/\ \  \  /  / | \  \|\  \  \ \  \/  / /
#    \ \   __\\ \  \/  / / \ \   __  \  \ \    / / 
#     \ \  \_| \ \    / /   \ \  \ \  \  /     \/  
#      \ \__\   \ \__/ /     \ \__\ \__\/___/\__\  
#       \|__|    \|__|/       \|__|\|__/___/ /\ _\ 
#    
#    FVAX and all related titles and logos are trademarks of FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
#    FVAX is licensed under the AGPLv3. More information at "https://github.com/neofodere/fvax/blob/main/LICENSE".

NAME = fvax

SRC =	fvax.c \
		encoder.c \
		decoder.c

OBJ = $(SRC:.c=.o)

CC ?= gcc
CFLAGS = -Wall -Wextra -Werror -D_FILE_OFFSET_BITS=64

ifeq ($(OS),Windows_NT)
	EXE = $(NAME).exe
else
	EXE = $(NAME)
endif

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) *.fvaxtmp

fclean: clean
	rm -f $(EXE)

re: fclean all

.PHONY: all clean fclean re
# FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
