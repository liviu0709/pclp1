#pragma once

#include <stdint.h>
#include <stdlib.h>

#define BLUE        "\033[34m"
#define CLEAR       "\033[0m"
#define BLUE_SPEC   BLUE "%c" CLEAR

void demo_bitwise();
char* binary_representation(void *p, int n) __attribute__((nonnull(1)));
void print_binary_rep(void *p, int n) __attribute__((nonnull(1)));
void pointers_demo();