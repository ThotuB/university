#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _header{
	char file_name[28];
	unsigned file_size;
}header;

header make_header(char* fileName, FILE* file){
	header hdr;

	strncpy(hdr.file_name, fileName, sizeof(hdr.file_name)-1);
	fseek(file, 0, SEEK_END);
	hdr.file_size = ftell(file);

	return hdr;
}

void print_header(header hdr){
	printf("Name: %-27s", hdr.file_name);
	printf("Size: %-u\n", hdr.file_size);
}

void write_header_to_archive(header hdr, FILE* archive){
	fseek(archive, 0, SEEK_END);
	fwrite(&hdr, sizeof(header), 1, archive);
}

void write_contents_to_archive(header hdr, FILE* file, FILE* archive){
	fseek(file, 0, SEEK_SET);
	fseek(archive, 0, SEEK_END);

	unsigned char buf[hdr.file_size];
	fread(buf, hdr.file_size, 1, file);
	fwrite(buf, hdr.file_size, 1, archive);
}

void write_contents_to_file(header hdr, FILE* file, unsigned char contents[]){
	fseek(file, 0, SEEK_SET);

	fwrite(contents, hdr.file_size, 1, file);
}

int check_duplicate(char* fileName, FILE* archive){
	header hdr;
	fseek(archive, 0, SEEK_SET);

	while ( fread(&hdr, sizeof(header), 1, archive) == 1 ){
		if ( strcmp(hdr.file_name, fileName) == 0 ){
			return 1;
		}
		fseek(archive, hdr.file_size, SEEK_CUR);
	}

	return 0;
}

void add_to_archive(char *fileName, FILE* archive){
	FILE *file = fopen( fileName, "rb");

	fseek(archive, 0, SEEK_END);

	if ( !file ){
		fprintf(stderr, "No file of that name!\n");
		exit(0);
	}

	header fileH = make_header(fileName, file);

	write_header_to_archive(fileH, archive);
	write_contents_to_archive(fileH, file, archive);
}

void extract_from_archive(char *fileName, FILE* archive){
	header hdr;
	unsigned fileFound = 0;

	fseek(archive, 0, SEEK_SET);

	while ( fread(&hdr, sizeof(header), 1, archive) == 1 ){
		if ( strcmp(hdr.file_name, fileName) == 0 ){
			unsigned char contents[hdr.file_size];
			FILE* file = fopen(fileName, "wb");

			fread(contents, hdr.file_size, 1, archive);


			write_contents_to_file(hdr, file, contents);

			fileFound = 1;
			fclose(file);
			break;
		}

		fseek(archive, hdr.file_size, SEEK_CUR);
	}

	if ( !fileFound ){
		printf("%s - file not found\n", fileName);
	}
	else {
		printf("%s - file extracted\n", fileName);
	}
}

void list_files(FILE* archive){
	header hdr;
	unsigned i = 1;

	while ( fread(&hdr, sizeof(header), 1, archive) == 1 ){
		printf("%3u.", i);
		print_header(hdr);
		fseek(archive, hdr.file_size, SEEK_CUR);
		i++;
	}
}

int main(int argc, char **argv){
	if ( argc == 1 ){
		fprintf(stderr, "Not enough arguments!\n");
    	return 0;
	}

	FILE* archive_file = fopen("archive.arh", "r+b");
	if ( !archive_file ){
		archive_file = fopen("archive.arh", "w+b");
	}

	if ( strcmp(argv[1], "archive") == 0){
		for ( unsigned i = 2 ; i < argc ; i++){
			if ( strcmp(argv[i], "archive.arh") == 0 ){
				continue;
			}
			if ( !check_duplicate(argv[i], archive_file) ){
				add_to_archive(argv[i], archive_file);
			}
			else {
				printf("%s - file already archived\n", argv[i]);
			}
		}
	}
	else if ( strcmp(argv[1], "extract") == 0){
		for ( unsigned i = 2 ; i < argc ; i++){
			extract_from_archive(argv[i], archive_file);
		}

	}
	else if ( strcmp(argv[1], "list") == 0){
		list_files(archive_file);
	}


	return 0;
}
