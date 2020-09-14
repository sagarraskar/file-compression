/* FILE COMPRESSION AND DECOMPRESSION */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void compress(int fd, int fwd);

void decompress(int fd, int fwd);

int main(int argc, char* argv[]){
	char ch, flag = 0;
	int fd, fwd;

	/* to check the validity of arguments */
	if(argc != 4){
		errno = EINVAL;
		perror("Inalid arguments");
		return errno;		
	}

	fd = open(argv[2], O_RDONLY);                                /*opens the file to be compressed*/
	if(fd == -1){
		perror("Error opening file");
		return errno;
	}
	
	/* to check if the file is empty */	
	while(read(fd, &ch, 1)){
		flag = 1;
		break;
	}

	if(!flag){
		printf("file is empty\n");
		return 0;	
	}

	/* to bring the file descriptor at the beginning of the file */
	lseek(fd, 0, SEEK_SET);

	fwd = open(argv[3], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
	
	if(fwd == -1){
		perror("Error creating file");
		return errno;
	}


	if(!strcmp(argv[1], "-c")){
		compress(fd, fwd);
	}
	
	else if(!strcmp(argv[1], "-dc")){
		decompress(fd, fwd);
	}
	
	else{
		errno = EINVAL;
		perror("Invalid arguments");
		return errno;
	}
	
	close(fd);
	
	close(fwd);
	
	return 0;
}

