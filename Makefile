NAME    = libftpp

SRC     = tests.cpp \
		  srcs/data_structures/data_buffer/data_buffer.cpp \

HEADERS = libftpp.hpp \
          includes/data_structures.hpp \
          srcs/data_structures/pool/pool.hpp \
		  srcs/data_structures/data_buffer/data_buffer.hpp \

OBJ     = $(SRC:.cpp=.o)

CC      = g++
RM      = rm -f
CPPFLAGS = -Wall -Wextra -Werror -std=c++2a -pedantic

INCLUDES = -I includes -I srcs/data_structures/pool -I srcs/data_structures/data_buffer

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
