ARM64_CC_PATH=/home/naren/Desktop/LINUX/Cross_Compilation/IMX8_Manual_build/downloads/toolchain/arm-gnu-toolchain-15.2.rel1-x86_64-aarch64-none-linux-gnu/bin
ARM32_CC_PATH=/home/naren/Desktop/LINUX/Cross_Compilation/bbb_manual_build/toolchain/arm-gnu-toolchain-15.2.rel1-x86_64-arm-none-linux-gnueabihf/bin

LIB_VERSION=1.0.0
ABI_VERSION=1
LIBRARY=libcalc.so

RELEASE_CFLAGS=-Iinclude -Wall -Wextra -MMD -MP
DEBUG_CFLAGS=-Iinclude -Wall -Wextra -g -MMD -MP

ARCH?=native

BUILD_DIR=build/$(ARCH)

DEBUG_DIR=$(BUILD_DIR)/debug
RELEASE_DIR=$(BUILD_DIR)/release

DEBUG_LIB_DIR=$(DEBUG_DIR)/lib
RELEASE_LIB_DIR=$(RELEASE_DIR)/lib

LIB_DIR=library


ifeq ($(ARCH),native)
	CC=gcc
	AR=ar
endif

ifeq ($(ARCH),ARM64)
	CC=$(ARM64_CC_PATH)/aarch64-none-linux-gnu-gcc
	AR=$(ARM64_CC_PATH)/aarch64-none-linux-gnu-ar
endif

ifeq ($(ARCH),ARM32)
	CC=$(ARM32_CC_PATH)/arm-none-linux-gnueabihf-gcc
	AR=$(ARM32_CC_PATH)/arm-none-linux-gnueabihf-ar
endif


DEBUG_TARGET=$(DEBUG_DIR)/myapp
RELEASE_TARGET=$(RELEASE_DIR)/myapp


.PHONY: all debug release clean

debug: $(DEBUG_TARGET)

release: $(RELEASE_TARGET)

all: $(DEBUG_TARGET)


SRC=$(wildcard src/*.c)

LIB_SRC=$(wildcard library/*.c)


DEBUG_OBJS=$(patsubst src/%.c,$(DEBUG_DIR)/%.o,$(SRC))
RELEASE_OBJS=$(patsubst src/%.c,$(RELEASE_DIR)/%.o,$(SRC))


DEBUG_DEPS=$(DEBUG_OBJS:.o=.d)
RELEASE_DEPS=$(RELEASE_OBJS:.o=.d)


# Library objects are placed in a separate directory
# so they don't conflict with src/*.c objects.

LIB_DEBUG_OBJ=$(patsubst $(LIB_DIR)/%.c,$(DEBUG_LIB_DIR)/%.o,$(LIB_SRC))
LIB_RELEASE_OBJ=$(patsubst $(LIB_DIR)/%.c,$(RELEASE_LIB_DIR)/%.o,$(LIB_SRC))


LIB_DEBUG_DEPS=$(LIB_DEBUG_OBJ:.o=.d)
LIB_RELEASE_DEPS=$(LIB_RELEASE_OBJ:.o=.d)


# --------------------------------------------------
# Versioned shared library names
# --------------------------------------------------

DEBUG_LIB_REAL=$(DEBUG_LIB_DIR)/$(LIBRARY).$(LIB_VERSION)
DEBUG_LIB_SONAME=$(DEBUG_LIB_DIR)/$(LIBRARY).$(ABI_VERSION)
DEBUG_LIB_LINK=$(DEBUG_LIB_DIR)/$(LIBRARY)

RELEASE_LIB_REAL=$(RELEASE_LIB_DIR)/$(LIBRARY).$(LIB_VERSION)
RELEASE_LIB_SONAME=$(RELEASE_LIB_DIR)/$(LIBRARY).$(ABI_VERSION)
RELEASE_LIB_LINK=$(RELEASE_LIB_DIR)/$(LIBRARY)


# --------------------------------------------------
# Application
# --------------------------------------------------

$(DEBUG_TARGET): $(DEBUG_OBJS) $(DEBUG_LIB_REAL)
	$(CC) $(DEBUG_OBJS) -L$(DEBUG_LIB_DIR) -lcalc -o $@

$(RELEASE_TARGET): $(RELEASE_OBJS) $(RELEASE_LIB_REAL)
	$(CC) $(RELEASE_OBJS) -L$(RELEASE_LIB_DIR) -lcalc -o $@


# --------------------------------------------------
# Debug shared library
# --------------------------------------------------

$(DEBUG_LIB_REAL): $(LIB_DEBUG_OBJ)
	@mkdir -p $(DEBUG_LIB_DIR)
	$(CC) -shared \
	      -Wl,-soname,$(LIBRARY).$(ABI_VERSION) \
	      -o $@ $^

	ln -sf $(LIBRARY).$(LIB_VERSION) $(DEBUG_LIB_SONAME)
	ln -sf $(LIBRARY).$(ABI_VERSION) $(DEBUG_LIB_LINK)


# --------------------------------------------------
# Release shared library
# --------------------------------------------------

$(RELEASE_LIB_REAL): $(LIB_RELEASE_OBJ)
	@mkdir -p $(RELEASE_LIB_DIR)
	$(CC) -shared \
	      -Wl,-soname,$(LIBRARY).$(ABI_VERSION) \
	      -o $@ $^

	ln -sf $(LIBRARY).$(LIB_VERSION) $(RELEASE_LIB_SONAME)
	ln -sf $(LIBRARY).$(ABI_VERSION) $(RELEASE_LIB_LINK)


# --------------------------------------------------
# Application object files
# --------------------------------------------------

$(DEBUG_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(DEBUG_CFLAGS) -c $< -o $@

$(RELEASE_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(RELEASE_CFLAGS) -c $< -o $@


# --------------------------------------------------
# Library object files
# --------------------------------------------------

$(DEBUG_LIB_DIR)/%.o: library/%.c
	@mkdir -p $(dir $@)
	$(CC) $(DEBUG_CFLAGS) -fPIC -c $< -o $@

$(RELEASE_LIB_DIR)/%.o: library/%.c
	@mkdir -p $(dir $@)
	$(CC) $(RELEASE_CFLAGS) -fPIC -c $< -o $@


# --------------------------------------------------
# Dependency files
# --------------------------------------------------

-include $(DEBUG_DEPS)
-include $(RELEASE_DEPS)

-include $(LIB_DEBUG_DEPS)
-include $(LIB_RELEASE_DEPS)


# --------------------------------------------------
# Clean
# --------------------------------------------------

clean:
	rm -rf build
