#				███████╗████████╗       ██████╗  █████╗ ██████╗ ██████╗  █████╗ 
#				██╔════╝╚══██╔══╝       ██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗
#				█████╗     ██║          ██║  ██║███████║██║  ██║██║  ██║███████║
#				██╔══╝     ██║          ██║  ██║██╔══██║██║  ██║██║  ██║██╔══██║
#				██║        ██║ ███████╗ ██████╔╝██║  ██║██████╔╝██████╔╝██║  ██║
#				╚═╝        ╚═╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚═════╝ ╚═╝  ╚═╝
                                                              
NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -g

LIB = -Lminilibx-linux -l:libmlx_Linux.a -lX11 -lXext -lm
CLIB = cub3d.a
LIBFT = src/libft/libft.a

SRCS = main.c parsing_utils.c init.c events.c game.c

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

all: $(NAME)

bonus : $(NAME)

clean:
	rm -f $(OBJS) $(PFDOBJ) $(GNLOBJ) $(CLIB) $(OBJGRB)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(CLIB): $(OBJGRB) $(PFDOBJ) $(GNLOBJ) $(OBJS)
	ar rcs $(CLIB) $^

$(NAME): $(CLIB)
	cc $(CFLAGS) $(LIBFT) $(CLIB) $(LIB) -o $(NAME)

test :
	make re && make clean && clear && ./cub3D
push :
	git add . && git commit -m "mini map is done" && git push origin dont-touch