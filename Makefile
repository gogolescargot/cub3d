# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggalon <ggalon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 00:56:29 by ggalon            #+#    #+#              #
#    Updated: 2024/04/29 18:01:24 by ggalon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# DIRECTORIES ==================================================================

LIBFT_DIR	=	libft/

SRCS_DIR	=	src/

OBJS_DIR	=	.obj/

INCL_DIR	=	inc/

MLX_DIR		=	mlx/

# FILES ========================================================================

NAME_	=	cub3d

NAME_B	=	cub3d

LIBFT	=	$(LIBFT_DIR)libft.a

MLX		=	$(MLX_DIR)libmlx_Linux.a

FILE_C	=	cub3d file map_1 map_2 map_3 camera window input asset_1 asset_2 asset_3 draw_1 draw_2 draw_3 draw_4 bool_1 bool_2 utils_1 utils_2

FILE_CB	=	cub3d file map_1 map_2 map_3 camera window input asset_1 asset_2 asset_3 draw_1 draw_2 draw_3 draw_4 bool_1 bool_2 utils_1 utils_2

FILE_H	=	cub3d

FILE_HB	=	cub3d

SRCS	=	$(addsuffix .c, $(addprefix $(SRCS_DIR), $(FILE_C)))

OBJS	=	$(addsuffix .o, $(addprefix $(OBJS_DIR), $(FILE_C)))

INCL	=	$(addsuffix .h, $(addprefix $(INCL_DIR), $(FILE_H)))

# COMMANDS =====================================================================

CC			=	cc

CC_FLAGS	=	-Wall -Wextra -Werror -g3 -I $(INCL_DIR) -I $(LIBFT_DIR)$(INCL_DIR) -I $(MLX_DIR)

MLX_FLAGS	=	-lXext -lX11 -lm

NORM		=	norminette $(SRCS_DIR) $(INCL_DIR)

# RULES ========================================================================

all:
	@ echo "\n${BBlue}Checking Norminette...${NC}"
	@ $(NORM) | grep -q Error && $(NORM) | grep Error || echo "\n${BGreen}Norminette OK !${NC}"
	@ echo "\n${BBlue}Compilation of minilibX...${NC}"
	@ $(MAKE) --no-print-directory -C $(MLX_DIR)
	@ echo "\n${BGreen}minilibX Ready !${NC}"
	@ $(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@ echo "\n${BBlue}Compilation of project source files...${NC}"
	@ mkdir -p $(OBJS_DIR)
	@ $(MAKE) --no-print-directory $(NAME_)
	@ echo "\n${BGreen}Project Ready !${NC}\n"

bonus:
	@$(MAKE) --no-print-directory NAME_="$(NAME_B)" FILE_C="$(FILE_CB)" FILE_H="$(FILE_HB)"

$(NAME_): $(OBJS) $(LIBFT) $(MLX)
	@ echo "\n${BCyan}Creating the executable...${NC}"
	$(CC) $(CC_FLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME_)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(INCL) Makefile
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	@ echo "\n${BRed}minilibX deletion...${NC}"
	@ $(MAKE) --no-print-directory -C $(MLX_DIR) clean
	@ $(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@ echo "\n${BRed}Project binary deletion...${NC}"
	rm -rf $(OBJS_DIR)
	@ echo

fclean:
	@ echo "\n${BRed}minilibX deletion...${NC}"
	@ $(MAKE) --no-print-directory -C $(MLX_DIR) clean	
	@ $(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@ echo "\n${BRed}Project deletion...${NC}"
	rm -rf $(OBJS_DIR)
	rm -f $(NAME_) $(NAME_B)
	@ echo

re: fclean all

.PHONY: all clean fclean re bonus

# COLORS =======================================================================

# Reset
NC=\033[0m

# Regular
Black=\033[0;90m
Red=\033[0;91m
Green=\033[0;92m
Yellow=\033[0;93m
Blue=\033[0;94m
Purple=\033[0;95m
Cyan=\033[0;96m
White=\033[0;97m

# Bold
BBlack=\033[1;90m
BRed=\033[1;91m
BGreen=\033[1;92m
BYellow=\033[1;93m
BBlue=\033[1;94m
BPurple=\033[1;95m
BCyan=\033[1;96m
BWhite=\033[1;97m

# Background
BGBlack=\033[0;100m
BGRed=\033[0;101m
BGGreen=\033[0;102m
BGYellow=\033[0;103m
BGBlue=\033[0;104m
BGPurple=\033[0;105m
BGCyan=\033[0;106m
BGWhite=\033[0;107m
