SDIR	=	src
SRCS	=	$(shell ls $(SDIR))

ODIR	=	obj
OBJS	=	$(addprefix $(ODIR)/,$(SRCS:.cpp=.o))

IDIR	=	inc
INC		=	$(shell ls $(IDIR))
INCLUDE	=	$(addprefix $(IDIR)/,$(INC))

NAME	=	rt

CXX		=	c++

CXXFLAGS=	-std=c++17 -Wall -Wextra -Werror -g

RM		=	rm -rf

# ----------------Colors------------------------------------------------------
BLUE	=	\033[0;34m
CYAN	=	\033[1;36m
GREEN	=	\033[1;32m
RED		=	\033[0;31m
YELLOW	=	\033[1;33m
PURPLE	=	\033[1;35m
CLEAR	=	\033[m
# ----------------------------------------------------------------------------

all: $(NAME)

$(ODIR)/%.o: $(SDIR)/%.cpp $(INCLUDE)
	@mkdir -p $(@D)
	@echo "$(BLUE)Compiling $(GREEN)$(basename $(@F))$(CLEAR)"
	@$(CXX) $(CXXFLAGS) -I$(IDIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(BLUE)Building  $(CYAN)$(NAME)$(CLEAR)"
	@$(CXX) $(OBJS) -o $(NAME)

clean:
	@echo "$(RED)Deleting $(PURPLE)objects$(CLEAR)"
	@$(RM) $(ODIR)

fclean:	clean
	@echo "$(RED)Deleting $(YELLOW)$(NAME)$(CLEAR)"
	@$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
