// Gitignore Adder
//
// A small C program that adds entries to the .gitignore file of a Git repository via the command line.
// It recursively searches for the .git folder, creates a .gitignore if necessary, and appends the arguments as new lines.

#include <stdio.h>
#include <string.h> // for strcmp
#include "oscore.h"

// Checks if a file exists (returns 1 if it exists, 0 if not)
int file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return 1;
    }
    return 0;
}

// Prints a help message
int help()
{
    printf("GitIgnore-Adder\n"
           "Adds entries to the .gitignore of a Git repository.\n"
           "Usage: ./main <entry1> <entry2> ...\n"
           "Example: ./main build/ temp.log\n"
           "--help shows this help.\n");
    return 0;
}

// Recursively searches for the .git folder upwards from the current directory.
// found_path: buffer for the found directory
// Returns: 1 = found, 0 = not found
int find_git_root(char *found_path, int maxlen) {
    char *cwd = get_current_path();
    if (!cwd) return 0;
    while (1) {
        char git_path[PATH_MAX_LEN];
        snprintf(git_path, PATH_MAX_LEN, "%s%s.git", cwd, PATH_SEPARATOR);
        if (is_directory(git_path)) {
            strncpy(found_path, cwd, maxlen);
            free(cwd);
            return 1;
        }
        // Go up one directory (last separator)
        char *last_sep = strrchr(cwd, PATH_SEPARATOR[0]);
        if (!last_sep || last_sep == cwd) break;
        *last_sep = '\0';
    }
    free(cwd);
    return 0;
}

int main(int argc, char *argv[])
{
    // Check for arguments
    if (argc < 2) {
        printf("Please run with at least one argument or --help.\n");
        return 1;
    }

    // Show help
    if (strcmp(argv[1], "--help") == 0) {
        return help();
    }

    // Search for Git root (.git folder)
    char git_root[PATH_MAX_LEN] = {0};
    if (!find_git_root(git_root, PATH_MAX_LEN)) {
        printf("No .git folder found in the current or any parent directory.\n");
        return 1;
    }

    // Determine .gitignore path in the Git root
    char gitignore_path[PATH_MAX_LEN];
    snprintf(gitignore_path, PATH_MAX_LEN, "%s%s.gitignore", git_root, PATH_SEPARATOR);

    // If .gitignore does not exist, create it
    if (!file_exists(gitignore_path)) {
        FILE *file = fopen(gitignore_path, "w");
        if (!file) {
            perror("Error creating .gitignore file");
            return 1;
        }
        fclose(file);
        printf(".gitignore was created in directory: %s\n", git_root);
    } else {
        printf(".gitignore found in directory: %s\n", git_root);
    }

    // Append arguments (except --help) to .gitignore
    FILE *file = fopen(gitignore_path, "a");
    if (!file) {
        perror("Error opening .gitignore file for appending");
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) continue;
        fprintf(file, "%s\n", argv[i]);
        printf("%s added to .gitignore.\n", argv[i]);
    }
    fclose(file);
    return 0;
}
