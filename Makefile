CC     := gcc
CFLAGS := -Wall -Wextra -O2 -MMD -MP -Iinclude
LIBS   := -lSDL3 -lSDL3_image -lm
TARGET := build/main

SRCS := $(shell find src -type f -name '*.c')
OBJS := $(patsubst src/%.c,build/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $^ -o $@ $(LIBS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

run: $(TARGET)
	@./$(TARGET)

clean:
	rm -rf build

.PHONY: all run clean
