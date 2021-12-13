# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 13:50:48 by wetieven          #+#    #+#              #
#    Updated: 2021/12/13 09:52:00 by wetieven         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# =============== #
# === TARGETS === #
# =============== #

NAME		=	cub3d

## ~~ Folders ~~ ##

DDIR		=	deps/
ODIR		=	objs/

# =============== #
# === SOURCES === #
# =============== #

SRCS		=	cub3d.c \
				cub_data.c \
				cub_parsers.c \
				cub_map.c

## ~~ Folders ~~ ##

HDIR		=	incs/ $(LDIR:%=%/incs) libs/mlx /opt/X11/include
SDIR		=	srcs/

# ================= #
# === RESOURCES === #
# ================= #

##LDIR		=	libs/
LDIR		=	$(shell find libs -mindepth 1 -maxdepth 1 -type d)

# ==================== #
# === PLACEHOLDERS === #
# ==================== #

### ~~~ TARGETS ~~~ ###

OBJS		=	$(SRCS:%.c=$(ODIR)%.o)

DEPS		=	$(SRCS:%.c=$(DDIR)%.d)

LIBS		=	$(shell find $(LDIR) -name '*.a')
LNAMES		=	$(shell find $(LDIR) -name '*.a' -exec basename {} ';')

#BOBJ		=	$(BONUS:%=$(ODIR)%.o)

## ~~ Folders ~~ ##

SUBDIRS		=	$(ODIR) $(DDIR)

### ~~~ SOURCES ~~~ ###

INCS		=	$(shell find $(HDIR) -name '*.h')

ESRC		=	$(NAME:%=$(SRCS)%.c)

## ~~ Folders ~~ ##

SDIR		:=	$(shell find $(SDIR) -mindepth 1 -maxdepth 1 -type d)

vpath %.d $(DDIR)
vpath %.o $(ODIR)
vpath %.a $(LDIR)

vpath %.h $(HDIR)
vpath %.c $(SDIR)

# ====================== #
# === COMPILER SETUP === #
# ====================== #


CC			=	gcc
WRNFL		=	-Wall -Wextra -Werror
OPTFL		=	-O3 -march=native -fno-builtin
DBGFL		=	-g
CFLGS		=	$(WRNFL)#$(OPTFL) $(DBGFL)
DEPFL		=	-MT $@ -MMD -MP -MF $(DDIR)$*.d

CINCS		=	$(addprefix -I, $(HDIR))
CLDIR		=	$(addprefix -L, $(LDIR))
# CLIBS		=	$(LNAMES:lib%.a=-l%) -framework OpenGL -framework AppKit # Apple
CLIBS		=	$(LNAMES:lib%.a=-l%) -lmlx -lX11 -lXext # Linux

# ============= #
# === RULES === #
# ============= #

# ~~~ Default ~~~ #

all			:	make_libs $(SUBDIRS) $(NAME)

$(SUBDIRS)	:
				mkdir -p $(SUBDIRS)

# ~~~ Objects Compiling  ~~~ #

$(ODIR)%.o	:	%.c $(DDIR)%.d $(LIBS)
				$(CC) $(CFLGS) $(CINCS) $(DEPFL) -c $< -o $@

# ~~~ Library archiving ~~~ #

#(LIBS)		:	make_libs

make_libs	:
				$(MAKE) -C libs/libft
				$(MAKE) -C libs/mlx
#				for dir in $(LDIR); do $(MAKE) -C $$dir; done <- for versatility
#				ln -sf libs/mlx/libmlx.dylib <- for mlx beta

# ~~~ Executables Compiling  ~~~ #

$(NAME)		:	$(OBJS)
				$(CC) $^ -o $@ $(CLDIR) $(CLIBS)

# ~~~ Actions ~~~ #

bonus		:	all

norm		:
				norminette incs srcs

clean		:	$(LDIR)
				rm -rf $(ODIR)
				$(MAKE) -C libs/libft clean
				$(MAKE) -C libs/mlx clean

fclean		:	$(LDIR) clean
				$(RM) $(NAME)
				$(RM) $(LIBS)
				rm -rf $(DDIR)
				$(MAKE) -C libs/libft fclean
				$(MAKE) -C libs/mlx clean

re			:	fclean all

.PHONY : all norm clean fclean re#bonus make_libs

$(DEPS)		:
include $(wildcard $(DEPS))
