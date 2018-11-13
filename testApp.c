#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int fd, res, count;

	if (argc < 2){
		fprintf(stderr, "FORMAT: %s <my-num>\n", argv[0]);
		exit(1);
	}

	if ((fd = open("/dev/mydrv", O_RDWR)) < 0){
		perror("open error");
		return -1;
	}

	res = read(fd, &count, sizeof(count));

	if (res==sizeof(count))
		printf("Read size matches.\n");

	printf("Task-%s is awakened at %d-th order.\n", argv[1], count);

	close(fd);
	return(0);
}

