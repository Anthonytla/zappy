CC		=	g++

CFLAGS	=	-Wall -Werror -Wextra -pedantic -std=c++14 -g

LDFLAGS =   -lsfml-network -lsfml-system -g

SRC	=	main.cpp client.cpp

OBJ	=	${SRC:.cpp=.o}

TARGET = client

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

all: $(TARGET)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(TARGET)

re: fclean all

.PHONY:	all re clean fclean
