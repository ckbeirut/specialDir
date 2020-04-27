#include <iostream>
#include <io.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <windows.h>


/********************************************/
bool DirectoryExists( const char* absolutePath ){

    if( _access( absolutePath, 0 ) == 0 ){

        struct stat status;
        stat( absolutePath, &status );

        return (status.st_mode & S_IFDIR) != 0;
    }
    return false;
}

/*******************************************/
char* replace(const char *s){

char* p = new char[strlen(s)+1];
int i=0;

	for (i=0;s[i];i++)	
	if (s[i]=='\\')	
		p[i] ='/';
	else
		p[i]=s[i];

	if (p[i-1] == '/')
		p[i]='\0';
	else
	{	p[i]='/';
		p[i+1]='\0';
	}

return p;
}

/*******************************************/
void dirc (const char* destpath){

HANDLE hFind;
WIN32_FIND_DATA FindFileData;
char filename[256];
size_t i=1;

if((hFind = FindFirstFile(destpath, &FindFileData)) != INVALID_HANDLE_VALUE)
	{
	do	{
		sprintf (filename, "echo %d-%s", i, FindFileData.cFileName);
		system (filename);
		}
	while(FindNextFile(hFind, &FindFileData));

	FindClose(hFind);
	}
}


/*******************************************/
int main(int argc, char**argv) {
	
const char* path = argv[1];
char* fspath;
	
	if (argv[1] == NULL)
		std::cout <<"No path provided"<<std::endl;
	else
		if ( DirectoryExists(path) )
			std::cout <<"Provided path is "<<path<<std::endl;
		else
			std::cout <<"Path doesn't exist"<<std::endl;

/***********************************************/
fspath = replace(path);

std::cout <<"Modified path: "<<fspath<<std::endl;

char* destpath = (char *) malloc (strlen(fspath)+6);
destpath = strcat (fspath,"*.mp4");
std::cout <<"Destination path "<<destpath<<std::endl;
std::cout<<"Destination path length "<<strlen(destpath)<<std::endl;
dirc (destpath);
/*********************************************/
return 0;
}