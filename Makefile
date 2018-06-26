NAME = wolf3d

SRCS = 	wolf3d.c		\
		reading.c		\
		utilitaries.c	\
		utilitaries2.c	\
		utilitaries3.c	\
		menu.c			\
		colors.c		\
		raycasting.c	\
		texture.c		\
		events.c		\
		draw.c			\
		minimap.c		\
		dot.c			\
		draw_line.c		\
		move_tab.c		\

SRCO = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

FRMW = -framework OpenGL -framework Appkit -lpthread

LIB =	./libft/libft.a			\
		./minilibx_macos/libmlx.a	\

SRC_PATH = srcs

OBJ_PATH = compiled_objects

SRC = $(addprefix $(SRCS_PATH)/,$(SRCS))

OBJ = $(addprefix $(OBJ_PATH)/,$(SRCO))

INCLUDES = includes

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIB) $(FRMW)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc -c $(FLAGS) -I$(INCLUDES) -o $@ -c $<

$(LIB):
	make -C libft
	make -C minilibx_macos

clean:
	rm -rf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	make -C libft clean
	make -C minilibx_macos clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all
