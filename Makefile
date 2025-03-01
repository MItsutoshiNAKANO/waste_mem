#! /usr/bin/make -f

## 
# @file
# @copyright
#   2025 Mitsutoshi Nakano <ItSANgo@gmail.com>
#   SPDX-License-Identifier: AGPL-3.0

TARGETS=waste_mem
waste_mem_SRCS=waste_mem.c error.c
waste_mem_DEPS=error.h
waste_mem_OBJS=$(waste_mem_SRCS:.c=.o)

CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -g

.PHONY: all format clean

all: $(TARGETS)
waste_mem: $(waste_mem_OBJS)
waste_mem.o: waste_mem.c $(waste_mem_DEPS)
error.o: error.c $(waste_mem_DEPS)
format:
	clang-format -i $(waste_mem_SRCS) $(waste_mem_DEPS)
clean:
	$(RM) $(TARGETS) $(waste_mem_OBJS)
