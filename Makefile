##
## EPITECH PROJECT, 2023
## source_cpp
## File description:
## Makefile
##

GREEN = \033[1;32m
LIGHT_GREEN = \033[1;32m
LIGHT_CYAN = \033[1;36m
RED = \033[1;31m
MAGENTA = \033[1;35m
BLUE = \033[1;34m
RESET = \033[0m

TARGET = nanotekspice

SRC =	src/main.cpp					\
		src/Handler.cpp					\
		src/Components/AComponent.cpp	\
		src/Pin/InputPin.cpp			\
		src/Pin/OutputPin.cpp			\

INCLUDES = -Iinclude -Isrc/Pin

CPPFLAGS = $(INCLUDES) -Wall -Wextra -Wpedantic -std=c++23

LDFLAGS =

DEP = $(OBJ:%.o=%.d)

OBJ = $(SRC:%.cpp=%.o)

$(TARGET): $(OBJ)
	g++ $(OBJ) -o $(TARGET) $(LDFLAGS)
	@echo -e "$(BLUE)Finished compiling with\
	\nCompilations flags $(CPPFLAGS)\
	\nLinking flags $(LDFLAGS)$(RESET)"

-include $(DEP)

%.o: %.cpp
	@g++ $(CPPFLAGS) -MMD -c $< -o $@\
	&& echo -e "[$(MAGENTA)compiled$(RESET)] $^ => $@"\
	|| echo -e "[$(RED)error$(RESET)]" $^

.PHONY : all clean fclean re

clean:
	@rm -f $(OBJ)
	@rm -f $(DEP)
	@echo -e "$(LIGHT_GREEN)Removed .o and .d files$(RESET)"

fclean: clean
	rm -f $(TARGET)
	@echo -e "$(LIGHT_GREEN)Removed target file$(RESET)"

<<<<<<< Updated upstream
re: clean $(TARGET)
=======
re: fclean $(TARGET)

tests_run:
	echo "No tests for NOW"
>>>>>>> Stashed changes
