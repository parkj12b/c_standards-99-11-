-include ../.config

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I..

ifeq ($(CONFIG_DEBUG_MODE),y)
	CFLAGS += -g
endif

# Set optimization level based on Kconfig choice
OPT_LEVEL = $(CONFIG_OPTIMIZATION_LEVEL)
ifeq ($(OPT_LEVEL),)
	OPT_LEVEL = 0
endif
CFLAGS += -O$(OPT_LEVEL)

# Targets to build based on Kconfig
TARGETS =
ifeq ($(CONFIG_RUN_INLINE_BENCHMARK),y)
	TARGETS += inline
endif
ifeq ($(CONFIG_RUN_BOOL_EXAMPLE),y)
	TARGETS += bool
endif
ifeq ($(CONFIG_RUN_COMPLEX_EXAMPLE),y)
	TARGETS += complex
endif
ifeq ($(CONFIG_RUN_FLEXIBLE_MEMBER_EXAMPLE),y)
	TARGETS += flexible_member_array
endif
ifeq ($(CONFIG_RUN_DESIGNATED_INITIALIZER_EXAMPLE),y)
	TARGETS += designated_initializer
endif
ifeq ($(CONFIG_RUN_COMPOUND_LITERAL_EXAMPLE),y)
	TARGETS += compound_literal
endif
ifeq ($(CONFIG_RUN_VARIADIC_MACRO_EXAMPLE),y)
	TARGETS += variadic_macro
endif

all: $(TARGETS)

# Compilation and linking
$(TARGETS): %: %.c ../config.h
ifeq ($(CONFIG_KEEP_OBJECTS),y)
	$(CC) $(CFLAGS) -c $< -o $@.o
	$(CC) $(CFLAGS) $@.o -o $@
else
	$(CC) $(CFLAGS) $< -o $@
endif

clean:
	rm -f inline bool complex flexible_member_array designated_initializer compound_literal variadic_macro *.o

.PHONY: all clean
