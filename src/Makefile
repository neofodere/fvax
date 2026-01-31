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
CFLAGS = -std=c23 -Wall -Wextra -Werror -O2 -D_FILE_OFFSET_BITS=64

WIN_EXE = $(NAME)-win.exe
LINUX_EXE = $(NAME)-linux

ifeq ($(OS),Windows_NT)
	EXE = $(WIN_EXE)
else
	EXE = $(LINUX_EXE)
endif

all: $(EXE)

$(WIN_EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(WIN_EXE) $(OBJ)

win:
	$(MAKE) $(WIN_EXE)

$(LINUX_EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(LINUX_EXE) $(OBJ)
	@if [ -f "$(LINUX_EXE).exe" ]; then mv "$(LINUX_EXE).exe" "$(LINUX_EXE)"; fi

linux: $(LINUX_EXE)

clean:
	rm -f $(OBJ) *.fvaxtmp

fclean: clean
	rm -f $(WIN_EXE) $(LINUX_EXE)

re: fclean all

.PHONY: all win linux clean fclean re
# FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
