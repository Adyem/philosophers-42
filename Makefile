NAME            = philo
DEBUGNAME       = philo_debug
SRCS            = check_argument.c \
                  error_managment.c \
                  free_memory.c \
                  main.c \
                  prepare_simulation.c \
                  run_simulation.c \
                  utils01.c \
				  utils02.c \
				  monitor.c \
				  check_information.c
OBJS            = $(SRCS:.c=.o)
DEBUG_OBJS      = $(SRCS:.c=_debug.o)
INCLUDE         = .
DEPS            = philosophers.h
CC              = cc
RM              = rm -f
CFLAGS          = -Wall -Wextra -Werror -pthread -g

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

%_debug.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -DDEBUG=1 -I $(INCLUDE) -c $< -o $@

all: $(NAME)

debug: CFLAGS += -DDEBUG=1
debug: $(DEBUGNAME)

$(DEBUGNAME): $(DEBUG_OBJS)
	$(CC) $(CFLAGS) -o $(DEBUGNAME) $(DEBUG_OBJS) -I $(INCLUDE)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I $(INCLUDE)

both: all debug

clean:
	$(RM) $(OBJS) $(DEBUG_OBJS)

fclean: clean
	$(RM) $(NAME) $(DEBUGNAME)

re: fclean all
