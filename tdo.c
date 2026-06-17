#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static int parse_cmd(int task_number, const char *cmd, const char *value) {
    int t_no = task_number;

    if (strcmp(cmd, "add") == 0) {
        t_no++;
        FILE *file; 

        file = fopen("tasks.md", "a");
        fprintf(file, "%d %s\n", t_no, value);
        printf("Task added.\n");
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

    return t_no;
}

int main() {
    printf("--- Task Manager ---\n");
    int t_no = 0;

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
            
            for (int i = 0; i < strlen(input); i++) {
                input[i] = tolower(input[i]);
            }
            
            char *cmd = input;
            char *value = delim + 1;

            t_no = parse_cmd(t_no, cmd, value);
        }
    }

    return 0;
}
