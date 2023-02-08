##
## EPITECH PROJECT, 2023
## source_cpp
## File description:
## Makefile
##

GREEN 			= 	\033[1;32m
LIGHT_GREEN 	= 	\033[1;32m
LIGHT_CYAN 		= 	\033[1;36m
RED 			= 	\033[1;31m
MAGENTA 		= 	\033[1;35m
BLUE 			= 	\033[1;34m
RESET 			= 	\033[0m

TARGET 			= 	nanotekspice

SRC 			=	src/main.cpp						\
					src/Handler.cpp						\
					src/Components/AComponent.cpp		\
					src/Components/AndGate.cpp			\
					src/Components/ComponentFactory.cpp	\
					src/Components/Input.cpp			\
					src/Pin/Pin.cpp						\
					src/Pin/PinLink.cpp					\
					src/FileParser.cpp

INCLUDES 		=	-Iinclude -Isrc/Pin -Isrc/Components -std=c++20

CXXFLAGS 		= 	$(INCLUDES) -Wall -Wextra -Wpedantic -std=c++23

LDFLAGS 		=

DEP 			=	$(OBJ:%.o=%.d)

OBJ 			=	$(SRC:%.cpp=%.o)

$(TARGET): $(OBJ)
	g++ $(OBJ) -o $(TARGET) $(LDFLAGS)
	@echo -e "$(BLUE)Finished compiling with\
	\nCompilations flags $(CXXFLAGS)\
	\nLinking flags $(LDFLAGS)$(RESET)"

-include $(DEP)

%.o: %.cpp
	@g++ $(CXXFLAGS) -MMD -c $< -o $@\
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

re: fclean $(TARGET)
