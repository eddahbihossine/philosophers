cc = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g 
SRC = philosophers.c \
			utils.c  \

all: $(SRC)
	$(cc) $(CFLAGS) $(SRC) -o philo


clean:
	rm -f *.o
make fclean: clean
	rm -f philo

make re: fclean all
