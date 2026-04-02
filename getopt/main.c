#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
int main(int argc, char *argv[]) {
    printf("Hello, World!\n");
    int opt;

    struct option long_options[] = {
        {"option-a", no_argument, 0, 'a'},
        {"option-b", no_argument, 0, 'b'},
        {"option-c", no_argument, 0, 'c'},
        {0, 0, 0, 0}
    };
    while((opt = getopt_long(argc, argv, "abc", long_options, NULL)) != -1) {
        switch(opt) {
            case 'a':
                printf("Option a is selected\n");
                break;
            case 'b':
                printf("Option b is selected\n");
                break;
            case 'c':
                printf("Option c is selected\n");
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-b] [-c]\n", argv[0]);
                return 1;
        }
    }

    return 0;
}