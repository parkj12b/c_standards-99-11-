-include .config

VENV = ./.venv/bin
GENCONFIG = $(VENV)/genconfig
OLDDEFCONFIG = $(VENV)/olddefconfig
MENUCONFIG = $(VENV)/menuconfig

# Collect all enabled build directories based on Kconfig
BUILD_DIRS =
ifeq ($(CONFIG_BUILD_C99),y)
    BUILD_DIRS += c_99
endif
ifeq ($(CONFIG_BUILD_C11),y)
    BUILD_DIRS += c_11
endif

# The default target
all: config.h
	@for dir in $(BUILD_DIRS); do \
		$(MAKE) -C $$dir all; \
	done

# Automatically update .config if Kconfig changes
.config: Kconfig
	$(OLDDEFCONFIG)

# Automatically generate config.h if .config or Kconfig changes
config.h: .config Kconfig
	$(GENCONFIG) --header-path config.h

menuconfig:
	$(MENUCONFIG)
	$(GENCONFIG) --header-path config.h

run: all
	@if [ "$(CONFIG_BUILD_C99)" = "y" ]; then \
		if [ -f ./c_99/inline ]; then printf "\033[92mrunning test inline\033[0m\n"; ./c_99/inline; fi; \
		if [ -f ./c_99/bool ]; then printf "\033[92mrunning test bool\033[0m\n"; ./c_99/bool; fi; \
		if [ -f ./c_99/complex ]; then printf "\033[92mrunning test complex\033[0m\n"; ./c_99/complex; fi; \
		if [ -f ./c_99/flexible_member_array ]; then printf "\033[92mrunning test flexible_member_array\033[0m\n"; ./c_99/flexible_member_array; fi; \
		if [ -f ./c_99/designated_initializer ]; then printf "\033[92mrunning test designated_initializer\033[0m\n"; ./c_99/designated_initializer; fi; \
		if [ -f ./c_99/compound_literal ]; then printf "\033[92mrunning test compound_literal\033[0m\n"; ./c_99/compound_literal; fi; \
		if [ -f ./c_99/variadic_macro ]; then printf "\033[92mrunning test variadic_macro\033[0m\n"; ./c_99/variadic_macro; fi; \
	fi
	@if [ "$(CONFIG_BUILD_C11)" = "y" ]; then \
		if [ -f ./c_11/thread ]; then printf "\033[92mrunning test thread\033[0m\n"; ./c_11/thread; fi; \
		if [ -f ./c_11/align ]; then printf "\033[92mrunning test align\033[0m\n"; ./c_11/align; fi; \
		if [ -f ./c_11/noreturn ] && [ -f ./c_11/return ]; then \
			printf "\033[92mComparing disassembly of noreturn and return:\033[0m\n"; \
			objdump -d ./c_11/noreturn | sed -n '/<main>:/,/^$$/p' > ./c_11/noreturn.dis; \
			objdump -d ./c_11/return | sed -n '/<main>:/,/^$$/p' > ./c_11/return.dis; \
			if diff -u ./c_11/return.dis ./c_11/noreturn.dis; then \
				printf "\033[93mNo disassembly differences found in main.\033[0m\n"; \
			else \
				printf "\033[91mDifferences found in disassembly (shown above).\033[0m\n"; \
			fi; \
		fi; \
		if [ -f ./c_11/generic ]; then printf "\033[92mrunning test generic\033[0m\n"; ./c_11/generic; fi; \
		if [ -f ./c_11/float ]; then printf "\033[92mrunning test float\033[0m\n"; ./c_11/float; fi; \
		if [ -f ./c_11/anonymous ]; then printf "\033[92mrunning test anonymous\033[0m\n"; ./c_11/anonymous; fi; \
		if [ -f ./c_11/static_assert ]; then printf "\033[92mrunning test static_assert\033[0m\n"; ./c_11/static_assert; fi; \
	fi

test: run

clean:
	rm -f config.h
	@for dir in c_99 c_11; do \
		if [ -d $$dir ]; then $(MAKE) -C $$dir clean; fi; \
	done

.PHONY: all menuconfig run test clean
