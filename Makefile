
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
	$(RM) $(OBJECTS) $(TESTS_OBJECTS) $(TESTS_NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests: $(NAME)
	$(CC) -o $(TESTS_NAME) $(TESTS) -L. -lparser -lcriterion --coverage -I includes

run_tests: tests
	export LD_LIBRARY_PATH=. && ./$(TESTS_NAME)
