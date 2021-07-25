SRC		:=	so_long.c

SRC_DIR :=	sources
INC_DIR :=	headers
OBJ_DIR :=	objects

INCLS   :=	$(INC_DIR)
SRCS	:=	$(addprefix $(SRC_DIR)/,$(SRC))
OBJS    :=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC		:=	clang

CFLAGS	+=	-Wall -Wextra -Werror -pedantic
IFLAGS	+=	-I.
LFLAGS	+=	-L.
TFLAGS	+=	-fsanitize=address -g3
MFLAGS	+=	-lmlx_Linux -lXext -lX11 -lft
OFLAGS	+=	-O3 -pthread

RM		:=	rm -rf

NAME	:=	so_long

MLX_DIR	:=	minilibx

LFT_DIR	:=	libft


all:		obj mlx lft $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
			$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@ $(IFLAGS)/$(INCLS) $(IFLAGS)/$(MLX_DIR) $(IFLAGS)/$(LFT_DIR)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LFLAGS)/$(MLX_DIR) $(LFLAGS)/$(LFT_DIR) $(MFLAGS) -o $(NAME)

clean:
			$(MAKE) -C $(LFT_DIR) clean
			$(MAKE) -C $(MLX_DIR) clean
			$(RM) $(OBJS) $(OBJ_DIR)

fclean: 	clean
			$(MAKE) -C $(LFT_DIR) fclean
			$(RM) $(NAME)

re: 		fclean all

mlx:
			$(MAKE) -C $(MLX_DIR)

lft:
			$(MAKE) -C $(LFT_DIR)

obj:
			mkdir -p $(OBJ_DIR)

.PHONY: 	all clean fclean re obj tests mlx lft
