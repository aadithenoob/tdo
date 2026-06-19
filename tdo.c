#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static void get_last_line(char *last_line) {
    FILE *fptr = fopen("tasks.md", "r");

    if (fptr == NULL) {
        return;
    }

    char content[1024];

    while (fgets(content, sizeof(content), fptr) != NULL) {
        strcpy(last_line, content);
    }
    fclose(fptr);
}

static int get_task_number() {
    int t_no = 0;
    char last_line[1024];
    get_last_line(last_line);

    if (strlen(last_line) == 0) {
        return 0;
    }

    int index = strcspn(last_line, " ");
    char *delim = &last_line[index];
    *delim = '\0';

    t_no = atoi(last_line);

    return t_no;
}

static void parse_cmd(char *cmd, const char *value) {
    if (strcmp(cmd, "add") == 0) {
        if (strcmp(value, "") == 0) {
            fprintf(stderr, "error: task cannot be empty.\n\n");
            return;
        }

        int t_no = get_task_number();
        
        t_no++;
        FILE *fptr; 

        fptr = fopen("tasks.md", "a");
        fprintf(fptr, "%d %s\n", t_no, value);
        printf("Task added.\n\n");
        fclose(fptr);
    } else if (strcmp(cmd, "view") == 0) {
        FILE *fptr; 
        char content[1024];

        fptr = fopen("tasks.md", "r");

        while (fgets(content, sizeof(content), fptr) != NULL) {
            printf("%s", content);
        }
        printf("\n");

        fclose(fptr);
    } else if (strcmp(cmd, "delete") == 0) {
        if (strcmp(value, "") == 0) {
            fprintf(stderr, "error: task number of task to be deleted cannot be empty.\n\n");
            return;
        }

        if (strcmp(value, "lt") == 0) {
            FILE *src = fopen("tasks.md", "r");

            if (strcmp) {
                fprintf(stderr, "error: file is empty or it has not been created.\n\n");
                return;
            }

            char current_line[1024];

            fgets(current_line, sizeof(current_line), src);

            char next_line[1024];
            FILE *temp = fopen("temp.md", "w");
            

            while (fgets(next_line, sizeof(next_line), src) != NULL) {
                fprintf(temp, "%s", current_line);
                strcpy(current_line, next_line);
            }

            fclose(src);
            fclose(temp);

            remove("tasks.md");
            rename("temp.md", "tasks.md");

            printf("Task deleted.\n\n");
        } else {
            int task = atoi(value);
        }
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