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

SRC =   fvax.c \
        encoder.c \
		decoder.c \

OBJ = $(SRC:.c=.o)

CC ?= gcc
CFLAGS = -Wall -Wextra -Werror

ifeq (, $(shell command -v $(CC)))
	CC := /usr/bin/gcc
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
# FODSOFT(TM). Neo Fodere de Frutos. All rights reserved.
