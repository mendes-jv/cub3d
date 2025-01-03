# Variables
NAME					:= cub3D

BUILD_DIR				:= build/
SOURCES_DIR				:= sources/
OBJECTS_DIR				:= objects/
LIBRARIES_DIR			:= libraries/
LIBFT_DIR				:= $(addprefix $(LIBRARIES_DIR), libft/)
MLX_DIR					:= $(addprefix $(LIBRARIES_DIR), mlx/)

TEST_NAME				:= test_cub3D
TEST_DIR				:= tests/

# Flags
MAKE					:= make
MAKE_LIBS				:= make -sC
CC						:= cc
CFLAGS					:= -Wall -Werror -Wextra -Wunreachable-code -Ofast -g3
MKDIR					:= mkdir -p
RM						:= rm -rf
CMAKE					:= cmake

# MLX42
MLX_FILE				:= libmlx42.a
LIB_MLX_FLAGS 			:= -Iinclude -ldl -lglfw -pthread -lm
LIB_MLX_SRCS 			:= MLX42/build/libmlx42.a
MLX_BUILD				:= $(addprefix $(MLX_DIR), $(BUILD_DIR))
MLX						:= $(addprefix $(MLX_BUILD), $(MLX_FILE))

# Sources
FILES					:=  algorithm \
						 	cast_rays \
						 	check_file \
						 	check_identifiers \
							dda \
							draw \
							getters \
							load_scene \
							main \
							mlx_handler \
							player_movements \
							textures \
							wall_calculations

OBJECTS					:= $(addprefix $(OBJECTS_DIR), $(addsuffix .o, $(FILES)))
LIBFT_FILE				:= libft.a
LIBFT 					:= $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))

# Tests
TEST_FILES 				:= test_execution

TEST_SOURCES			:= $(addprefix $(TEST_DIR), $(addsuffix .c, $(TEST_FILES)))
TEST_FLAGS				:= -lcriterion

MESSAGE1 := "-----------------.cub3d Compiled Successfully----------------"

all: libraries $(NAME)

$(NAME): $(OBJECTS)
	@ $(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX) $(LIB_MLX_FLAGS) -o $(NAME)
	@ echo $(MESSAGE1)

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@ $(MKDIR) $(OBJECTS_DIR)
	@ $(CC) $(CFLAGS) -c $< -o $@

libraries :  $(LIBFT) $(MLX)

$(LIBFT):
	@ $(MAKE_LIBS) $(LIBFT_DIR)

$(MLX):
	@ $(CMAKE) $(MLX_DIR) -B $(MLX_BUILD) && $(MAKE_LIBS) $(MLX_BUILD) -j4

clean: cleanlibs
	@ $(RM) $(OBJECTS_DIR)

cleanlibs: cleanmlx cleanlibft

cleanlibft:
	@ $(MAKE_LIBS) $(LIBFT_DIR) clean

cleanmlx:
	@ $(RM) $(MLX_BUILD)

fclean: clean
	@ $(RM) $(NAME) $(LIBFT)

re: fclean all

bonus: all

test: $(NAME) $(TEST_SOURCES)
	@$(CC) $(CFLAGS) $(TEST_FLAGS) $(TEST_SOURCES) $(LIBFT) -o $(TEST_NAME) $(HEADERS)
	@./$(TEST_NAME)
	@$(RM) $(TEST_NAME)

# Rules
.PHONY: all clean fclean re bonus libraries test
