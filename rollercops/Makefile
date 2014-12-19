CC=	g++

NAME=	bin

OBJ=	DateTime.cpp \
	Error.cpp \
	Logging.cpp \
	Number.cpp \
	Num.cpp \
	RCObject.cpp \
	ServerSocket.cpp \
	TcpSocket.cpp \
	test_main_kevin.cpp

LIB=	-pthread

$(NAME):
	$(CC) $(OBJ) $(LIB) -o $(NAME)

all:	$(NAME)

clean:
	rm -f *~

fclean:
	rm -f *~
	rm bin

re:	fclean all
