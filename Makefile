#				███████╗████████╗       ██████╗  █████╗ ██████╗ ██████╗  █████╗ 
#				██╔════╝╚══██╔══╝       ██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗
#				█████╗     ██║          ██║  ██║███████║██║  ██║██║  ██║███████║
#				██╔══╝     ██║          ██║  ██║██╔══██║██║  ██║██║  ██║██╔══██║
#				██║        ██║ ███████╗ ██████╔╝██║  ██║██████╔╝██████╔╝██║  ██║
#				╚═╝        ╚═╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚═════╝ ╚═╝  ╚═╝
                                                              
NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -g #-I$(HOME)/sdl2-local/include/SDL2 

LIB = -Llib -l:libmlx_Linux.a -lX11 -lXext -lm # $(HOME)/sdl2-local/lib/libSDL2.a
CLIB = cub3d.a

GREEN = \033[1;32m
RESET = \033[0m

SRCS = main.c ./parsing/parsing_utils.c ./initialization/init.c events.c game.c ./parsing/parsing_utils.c ./parsing/parsing_utils2.c ./parsing/sec_file_related.c ./parsing/parsing_utils3.c ./parsing/parsing_utils4.c \
 		./parsing/sec_map_related.c ./parsing/map_related.c ./parsing/map_related2.c ./parsing/fireforce.c ./parsing/file_related.c ./raycasting/raycast.c ./raycasting/projection.c ./raycasting/minimap.c \
	   ./raycasting/move_player.c ./raycasting/keys_handle.c ./parsing/map_related3.c ./raycasting/r_draw_and_check.c ./raycasting/r_calc_c.c ./raycasting/r_calc_cvh.c \
	   ./raycasting/r_set_store.c ./initialization/texture.c ./initialization/coloring.c ./initialization/maping.c ./initialization/init_player.c ./initialization/init_texsound.c \
	   ./gaming/animation.c ./gaming/sound.c ./moves.c

LIBFT_SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
    	ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
    	ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c \
    	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
    	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
    	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
    	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

SRC_GRB = garbage.c
SRC_PFD = check_char.c p_hexa.c putnbrr_fd.c unsigned.c formats.c p_memory.c printfd.c putcharr_fd.c putstrr_fd.c upper_hexa.c
SRC_GNL = get_next_line_utils.c get_next_line.c

PFDOBJ = $(addprefix src/printfd/, $(SRC_PFD:.c=.o))
GNLOBJ = $(addprefix src/get_next_line/, $(SRC_GNL:.c=.o))
OBJGRB = $(addprefix src/gc/, $(SRC_GRB:.c=.o))
OBJS = $(addprefix src/utils/, $(SRCS:.c=.o))
LIBFTOBJ = $(addprefix src/libft/, $(LIBFT_SRC:.c=.o))

ALL_OBJS = $(PFDOBJ) $(GNLOBJ) $(OBJGRB) $(OBJS) $(LIBFTOBJ)
TOTAL := $(words $(ALL_OBJS))

# Default target
all: $(NAME)

bonus : all

define COMPILE_WITH_PROGRESS
  INDEX=`echo "$(ALL_OBJS)" | tr ' ' '\n' | grep -n "$@" | cut -d: -f1`; \
  printf "$(GREEN)[ %2s / $(TOTAL) ]$(RESET) Compiling %s\n" "$$INDEX" "$<"; \
  $(CC) $(CFLAGS) -c $< -o $@
endef

%.o: %.c
	@$(COMPILE_WITH_PROGRESS)

clean:
	rm -f $(OBJS) $(PFDOBJ) $(GNLOBJ) $(CLIB) $(OBJGRB) $(LIBFTOBJ)

fclean: clean
	rm -f $(NAME) ./src/libft/libft.a

re: fclean all

$(CLIB): $(ALL_OBJS)
	@ar rcs $(CLIB) $^

$(NAME): $(CLIB)
	@$(CC) $(CFLAGS) $(CLIB) $(LIB) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

test:
	make re && make clean && clear && ./cub3D

push :
	git add . && git commit -m "mini map is done" && git push origin dont-touch

.PHONY: all bonus clean fclean re test