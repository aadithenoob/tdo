#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void parse_cmd(const char *cmd, const char *value) {
    if (strcmp(cmd, "add") == 0) {
        FILE *file; 

        file = fopen("tasks.md", "a");
        fprintf(file, "%s\n", value);
        fclose(file);
    } else if (strcmp(cmd, "view") == 0) {
        FILE *file; 
        char content[1024];

        file = fopen("tasks.md", "r");

        while (fgets(content, sizeof(content), file) != NULL) {
            printf("%s", content);
        }

        fclose(file);
    } else {
        fprintf(stderr, "error: command '%s' not found.\n", cmd);
    }
}

int main() {
    printf("--- Task Manager ---\n");

    while(1) {
        char input[256];
 
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        int index = strcspn(input, " ");
        char *delim = &input[index];

        if (strcmp(input, "exit") == 0) {
            return 0;
        } else if (delim != NULL) {
            *delim = '\0';
            char *cmd = input;
            char *value = delim + 1;

            parse_cmd(cmd, value);
        }
    }

    return 0;
}
