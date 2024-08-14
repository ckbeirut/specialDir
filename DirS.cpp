#include <io.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <windows.h>

bool DirectoryExists( const char* absolutePath ){

if( _access( absolutePath, 0 ) == 0 ){

    struct stat status;
    stat( absolutePath, &status );

    return (status.st_mode & S_IFDIR) != 0;
}
return false;
}

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
{   
    p[i]='/';
    p[i+1]='\0';
}

printf (p);
return p;
}

void dirc (const char* destpath){

HANDLE hFind;
WIN32_FIND_DATA FindFileData;
char filename[256];
size_t i=1;

 if((hFind = FindFirstFile(destpath, &FindFileData)) != INVALID_HANDLE_VALUE)
 {
  do    {
        sprintf (filename, "echo %d-%s", i, FindFileData.cFileName);
        system (filename);
        i++;
        }
while(FindNextFile(hFind, &FindFileData));

FindClose(hFind);
}
}

int main(int argc, char**argv) {

const char* path = argv[1];
char* fspath;

if (argv[1] == NULL)
    {
    printf("No path provided\n"); //std::cout <<"No path provided"<<std::endl;
    return 0;
    }

else
    if ( DirectoryExists(path) )
        printf("Provided path %s\n"); //std::cout <<"Provided path is "<<path<<std::endl;
    else
        {
        printf("Path doesn't exist\n"); //std::cout <<"Path doesn't exist"<<std::endl;
        return 0;
        }
 fspath = replace(path);
 char* destpath = (char *) malloc (strlen(fspath)+6);
 destpath = strcat (fspath,"*.*");
 dirc (destpath);
 free (destpath);

return 0;
}