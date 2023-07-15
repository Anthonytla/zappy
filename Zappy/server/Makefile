CC		=	g++

CFLAGS	=	-Wall -Werror -Wextra -pedantic -std=c++14 -ggdb

LDFLAGS =   -lsfml-network -lsfml-system -lsfml-graphics -lsfml-window

SRC	=	main.cpp server.cpp utils/gemstone.cpp utils/map.cpp utils/actions.cpp utils/player.cpp ../player/player.cpp ../../ZappyMap/window.cpp ../gemstone/gemstone.cpp

OBJ	=	${SRC:.cpp=.o}

TARGET = server

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

all: $(TARGET)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(TARGET)

re: fclean all

.PHONY:	all re clean fclean
