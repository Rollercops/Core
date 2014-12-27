NAME		= test_SMaker

ROOT_DIR	= ../../

SUB_DIR		= test/SMaker/

SRC_DIR		= $(ROOT_DIR)source/

SRC		= $(SRC_DIR)$(SUB_DIR)main.cpp	\
		  $(SRC_DIR)Excpt.cpp		\
		  $(SRC_DIR)SMaker.cpp

OBJ_DIR		= $(ROOT_DIR)object/

OBJ		= $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

		  ## $(patsubst %, $(OBJ_DIR)%, $(notdir $(SRC:%.cpp=%.o)))
		  ## $(notdir $(SRC))

CC		= g++

RM		= rm -f

LIB_DIR		= ##$(ROOT_DIR)lib/

LIB		= ##-L$(ROOT_DIR)/lib

INC_DIR		= $(ROOT_DIR)include/

FLAGS		= -I$(INC_DIR) -I$(INC_DIR)$(SUB_DIR)

CDFLAGS		= -W -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJ)
		@$(CC) $(OBJ) -o $(NAME) $(LIB) $(FLAGS) $(CDFLAGS)
		@echo "Compilation done."

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
		@$(CC) -c -o $@ $< $(LIB) $(FLAGS) $(CDFLAGS)
		@echo "Object files generated."

clean:
		@$(RM) $(OBJ)
		@echo "Object's files removed."

fclean:		clean
		@$(RM) $(NAME)
		@echo "Program removed."

re:		fclean	\
		all

test:
		@echo $(OBJ)
