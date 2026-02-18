// Gitignore Adder
//
// a tiny C program which is desined to add stuff to your Gitignore file
// via the Command Line

#include <stdio.h>

#include "oscore.h"

// Check if a File exists
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

// Screaming for help
void help()
{
	printf("HELP!\n");
}

// Main Function
int main(int argc, char *argv[])
{
	// TODO
	// Pipeline
	//
	// Get the Current Path
	// char Path* = get_current_path();

	const char *folder_to_check = ".git";

	int GitFolderFound = 1;
	int GitignoreFound = 1;

	// Check if there is a Git Repository in the same Directory
	if (folder_exists_in_current(folder_to_check))
	{
		printf("Folder '%s' exists in the current directory!\n", folder_to_check);
		GitFolderFound = 0;
	}
	else
	{
		printf("Folder '%s' does NOT exist in the current directory.\n", folder_to_check);
	}

	if (GitFolderFound == 0)
	{
		if (file_exists(".gitignore") == 1)
		{
			printf("Gitignore Found\n");
			FILE *file = fopen(".gitignore", "a"); // "a" = append
			if (file == NULL)
			{
				perror("Fehler beim Öffnen der Datei");
				return 1;
			}
			for (int i = 1; i < argc; i++)
			{
				printf("argv[%d] = %s\n", i, argv[i]);
				// Zeile anhängen
				fprintf(file, "%s", argv[i]);
				fprintf(file, "\n");
			}

			// Close the File
			fclose(file);
		}
	}

	//
	//
	// if not -> go one Directory up and check again -> and go
	// up again
	//
	// If Yes -> check if there is a Gitignore file ->
	// If not -> create one
	//
	// append every argument as a new Line to the gitignore
	// file

	// printf("Hello World\n");
	return 0;
}
