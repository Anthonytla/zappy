CC		=	g++

CFLAGS	=	-Wall -Werror -Wextra -pedantic -std=c++14 -g -fsanitize=address

LDFLAGS =   -lsfml-network -lsfml-system -lsfml-graphics -lsfml-window

SRC	=	main.cpp window.cpp

OBJ	=	${SRC:.cpp=.o}

TARGET = map

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

all: $(TARGET)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(TARGET)

re: fclean all

.PHONY:	all re clean fclean
