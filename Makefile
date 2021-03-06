# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dteemo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 11:58:34 by dteemo            #+#    #+#              #
#    Updated: 2020/04/13 17:00:47 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
[libdefaults]
        default_realm = MSK.21-SCHOOL.RU
        forwardable = true
        proxiable = true
        dns_lookup_kdc = no
        dns_lookup_realm = no
        allow_weak_crypto = true
        rdns = false
[realms]
        MSK.21-SCHOOL.RU = {
                kdc = ldap-kdc.msk.21-school.ru
                admin_server = ldap-kdc.msk.21-school.ru
                default_domain = msk.21-school.ru
                database_module = openldap_ldapconf
        }
[domain_realm]
        .msk.21-school.ru = MSK.21-SCHOOL.RU
        msk.21-school.ru = MSK.21-SCHOOL.RU
NAME = ft_ls

### PATH ###
SRCS_PATH = srcs/
OBJ_PATH  = obj/
LIBFT_PATH = libft/
INC_FILES = includes/ft_ls.h includes/libft.h

FLAGS = -Wall -Wextra -Werror
INC = -I ./includes/ -I ./$(LIBFT_PATH)
HEADERS = libft.h ft_ls.h

SRCS_NAME = ft_ls.c \
			files_list.c \
			helpers.c \
			print_helpers.c \
			print.c \
			read_helpers.c \
			helpers2.c \
			print_helpers2.c \
			print_helpers3.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@gcc $(FLAGS) $(OBJ) $(INC) -L $(LIBFT_PATH) -lft -o $(NAME)
	@echo "\033[32mBinary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c $(INC_FILES)
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@
	@echo "\033[34m\033[1mCompilation of \033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@
	@echo "\033[34m\033[1mCompilation of \033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\033[31mObjects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
