/* FILE COMPRESSION
 * compresses text file
 * uses Huffman algorithm
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "compress.c"
#include "decompress.c"
#include <string.h>

int main(int argc, char* argv[]){
	int i, j, k;
	int fd, fwd;

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
		printf("Hello\n");
		errno = EINVAL;
		perror("Invalid arguments");
		return errno;
	}
	close(fd);
	close(fwd);
	return 0;
}

