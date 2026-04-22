-include ../.config

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I..

ifeq ($(CONFIG_DEBUG_MODE),y)
	CFLAGS += -g
endif

OPT_LEVEL = $(CONFIG_OPTIMIZATION_LEVEL)
ifeq ($(OPT_LEVEL),)
	OPT_LEVEL = 0
endif
CFLAGS += -O$(OPT_LEVEL)

# Targets to build based on Kconfig
TARGETS =
ifeq ($(CONFIG_RUN_ALIGN_EXAMPLE),y)
	TARGETS += align
endif
ifeq ($(CONFIG_RUN_NORETURN_EXAMPLE),y)
	TARGETS += noreturn
endif
ifeq ($(CONFIG_RUN_RETURN_EXAMPLE),y)
	TARGETS += return
endif
ifeq ($(CONFIG_RUN_GENERIC_EXAMPLE),y)
	TARGETS += generic
endif
ifeq ($(CONFIG_RUN_THREAD_EXAMPLE),y)
	TARGETS += thread
endif
ifeq ($(CONFIG_RUN_FLOAT_EXAMPLE),y)
	TARGETS += float
endif
ifeq ($(CONFIG_RUN_ANONYMOUS_EXAMPLE),y)
	TARGETS += anonymous
endif
ifeq ($(CONFIG_RUN_STATIC_ASSERT_EXAMPLE),y)
	TARGETS += static_assert
endif

all: $(TARGETS)

$(TARGETS): %: %.c ../config.h
ifeq ($(CONFIG_KEEP_OBJECTS),y)
	$(CC) $(CFLAGS) -c $< -o $@.o
	$(CC) $(CFLAGS) $@.o -o $@ $(if $(findstring thread,$@),-lpthread)
else
	$(CC) $(CFLAGS) $< -o $@ $(if $(findstring thread,$@),-lpthread)
endif

clean:
	rm -f align noreturn return generic thread float anonymous static_assert *.o *.dis

.PHONY: all clean
