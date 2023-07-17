
SOURCES		=	sources/parser.c

OBJECTS		=	$(SOURCES:.c=.o)

TESTS		=	tests/test_parser.c

TESTS_OBJECTS	=	$(TESTS:.c=.o)

TESTS_NAME	=	tests_parser

NAME		=	libparser.so

CC			=	gcc

RM			=	rm -rf

CFLAGS		=	-Wall -Wshadow -Wextra -Werror -fpic -I includes

LDFLAGS		=	-shared 

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LDFLAGS)

clean:
	$(RM) $(OBJECTS) $(TESTS_OBJECTS)

fclean: clean
	$(RM) $(NAME) $(TESTS_NAME)

re: fclean all

tests: $(TESTS_OBJECTS) $(NAME)
	$(CC) -o $(TESTS_NAME) $(TESTS_OBJECTS) -L. -lparser -lcriterion --coverage

run_tests: tests
	export LD_LIBRARY_PATH=. && ./$(TESTS_NAME)