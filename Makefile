CC          := cc

#цвета
GREEN 				=	\033[0;32m
RED					=	\033[0;31m
RESET				=	\033[0m

NAME     := minishell

SRCDIR      := sources
INCDIR      := includes
BUILDDIR    := objects
TARGETDIR   := bin
RESDIR      :=
SRCEXT      := c
DEPEXT      := d
OBJEXT      := o

CFLAGS      :=  -Wall -Wextra -Werror -O3
INC         := -I$(INCDIR)
INCDEP      := -I$(INCDIR)
LIBFT_DIR	:=	./libft
LIBFT		:=	$(LIBFT_DIR)/libft.a
CPPFLAGS	=	"-I/Users/$(USER)/.brew/opt/readline/include" #change here
LDFLAGS		=	"-L/Users/$(USER)/.brew/opt/readline/lib" #change here
LIB         :=	-lreadline -lft -L $(LIBFT_DIR) $(CPPFLAGS) $(LDFLAGS)

SOURCES     := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

CHECK_NAME	:= ./$(TARGETDIR)/$(NAME)
SRC_COUNT_TOT := $(shell expr $(shell echo -n $(SOURCES) | wc -w) - $(shell ls -l $(BUILDDIR) 2>&1 | grep ".o" | wc -l) + 6)
ifeq ($(shell test $(SRC_COUNT_TOT) -le 0; echo $$?),0)
	SRC_COUNT_TOT = $(shell expr $(shell echo -n $(SOURCES) | wc -w) - 1)
endif
SRC_COUNT	:= 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))
PRINTF = LC_NUMERIC="en_US.UTF-8" printf


all: resources $(CHECK_NAME)

re: fclean all

resources: directories

directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

clean:
	@$(RM) -rf $(BUILDDIR)
	@echo "$(NAME): $(RED)Okay, you're right, it was worth removing$(RESET)"

fclean: clean
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@$(RM) -rf $(TARGETDIR)
	@echo "$(NAME): $(RED)after everything that happened between us, you just deleted me?🤬$(RESET)"

-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

$(CHECK_NAME): $(LIBFT) $(OBJECTS)
	@$(CC) -o $(TARGETDIR)/$(NAME) $(OBJECTS) -lreadline -lft -L $(LIBFT_DIR) $(CPPFLAGS) $(LDFLAGS)
	@echo "$(GREEN)\ngood boy.$(RESET)"

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(GREEN)$<$(RESET)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIR) 
	
.PHONY: all re clean fclean resources