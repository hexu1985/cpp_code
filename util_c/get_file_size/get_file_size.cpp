#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <sys/stat.h>
#include <unistd.h>

int get_file_size(const char *file_path)
{
	struct stat buf;
	if (stat(file_path, &buf) == -1) {
		printf("%s: %s error: stat\n", __func__, file_path);
		return -1;
	}

	if (buf.st_size > INT_MAX) {
		printf("%s: %s error: filesize too large\n", __func__, file_path);
		return -1;
	}

	return buf.st_size;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: a.out file_path\n");
		exit(1);
	}

	int size = get_file_size(argv[1]);
	printf("%s's size: %d\n", argv[1], size);
	return 0;
}
