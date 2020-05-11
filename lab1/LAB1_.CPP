#include <iostream.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

int isConsist(char* str ,char* part)
{
	int i=0;
	while(part[i]!='\0')
	{
		if(str[i]=='\0')
			return 0;
		if(toupper(part[i])!=toupper(str[i]) )
		{
			return 0;
		}
	i++;
	}
	return 1;
}

void WriteFileToFile(char* fileName,FILE* fileResult){
    FILE *fileFinded;
    char buffer[257];
    fileFinded = fopen(fileName, "r");
	while((fgets(buffer, 256, fileFinded))!=NULL)
		fprintf(fileResult, buffer);

	fclose(fileFinded);
}

int main(void)
{
    char path[255];
	char searchedPart[100]="";
	char debStr[100]="";
	char rezFileName[100]="";
    gets(path);
	printf("\n");
	scanf("%s",searchedPart);
	scanf("%s",rezFileName);
    DIR *dir = opendir(path);
    if(dir)
    {
		char findedFileName[100]="";
		struct dirent *ent;
		char sumStrs[500]="";
		FILE* fileResult;
		fileResult = fopen(rezFileName, "w");
		while((ent = readdir(dir)) != NULL)
		{
		    strcpy(findedFileName,ent->d_name);
		    if(isConsist(findedFileName,searchedPart))
			{
			printf("%s \n",ent->d_name);
					sprintf(sumStrs,"%s%s",path, findedFileName);
					WriteFileToFile(sumStrs,fileResult);
			}
		}
			fclose(fileResult);
    }
    else
        printf("Error opening directory\n");
    scanf("%s",debStr);
    return 0;
}
