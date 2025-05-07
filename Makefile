#				███████╗████████╗       ██████╗  █████╗ ██████╗ ██████╗  █████╗ 
#				██╔════╝╚══██╔══╝       ██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗
#				█████╗     ██║          ██║  ██║███████║██║  ██║██║  ██║███████║
#				██╔══╝     ██║          ██║  ██║██╔══██║██║  ██║██║  ██║██╔══██║
#				██║        ██║ ███████╗ ██████╔╝██║  ██║██████╔╝██████╔╝██║  ██║
#				╚═╝        ╚═╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚═════╝ ╚═╝  ╚═╝
                                                              
NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -g
LIB = -Lminilibx-linux -l:libmlx_Linux.a -lX11 -lXext

SRCS = main.c
CLIB = cub3d.a
SRC_GRB = garbage.c
SRC_PFD = check_char.c p_hexa.c putnbrr_fd.c unsigned.c formats.c p_memory.c printfd.c putcharr_fd.c putstrr_fd.c upper_hexa.c
SRC_GNL = get_next_line_utils.c get_next_line.c

PFDOBJ = $(addprefix src/printfd/, $(SRC_PFD:.c=.o))
GNLOBJ = $(addprefix src/get_next_line/, $(SRC_GNL:.c=.o))
OBJGRB = $(addprefix src/C_Garbage-Collector_v2/, $(SRC_GRB:.c=.o))
OBJS = $(SRCS:.c=.o)

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
	cc $(CFLAGS) $(CLIB) $(LIB) -o $(NAME)

test :
	make re && make clean && clear && ./cub3D