#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void printColored (const char *color, const char *text)
{
    printf("%s%s%s", color, text, ANSI_COLOR_RESET);
}

void printBold(const char *text){
    printf("\033[1m");
    printf(text);
    printf("\033[0m");
}

void printColoredBold(const char *color, const char *text) {
    printf("%s", color);
    printBold(text);
    printf(ANSI_COLOR_RESET);
}