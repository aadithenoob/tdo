#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static int get_task_number() {
    FILE *file = fopen("tasks.md", "r");

    if (file == NULL) {
        return 0;
    }

    char content[1024];
    char last_line[256];
    int t_no = 0;

    while (fgets(content, sizeof(content), file) != NULL) {
        strcpy(last_line, content);
    }
    fclose(file);
    
    int index = strcspn(last_line, " ");
    char *delim = &last_line[index];
    *delim = '\0';

    t_no = atoi(last_line);

    return t_no;
}

static void parse_cmd(char *cmd, const char *value) {
    if (strcmp(cmd, "add") == 0) {
        int t_no = get_task_number();
        
        t_no++;
        FILE *file; 

        file = fopen("tasks.md", "a");
        fprintf(file, "%d %s\n", t_no, value);
        printf("Task added.\n\n");
        fclose(file);
    } else if (strcmp(cmd, "view") == 0) {
        FILE *file; 
        char content[1024];

        file = fopen("tasks.md", "r");

        while (fgets(content, sizeof(content), file) != NULL) {
            printf("%s", content);
        }
        printf("\n");

        fclose(file);
    } else {
        fprintf(stderr, "error: command '%s' not found.\n\n", cmd);
    }
}

int main() {
    printf("--- Task Manager ---\n\n");

    while(1) {
        char input[256];
 
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "") == 0) {
            continue;
        }

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

            parse_cmd(cmd, value);
        }
    }

    return 0;
}
