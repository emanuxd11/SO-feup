#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>


#define BUF_SIZE 512

//Format time string given by ctime()
//to make it look like ls -l output
char *format_timeStr(time_t time) {
    char *timeString = ctime(&time);
    if(timeString == NULL) {
        return NULL;
    }

    timeString[strlen(timeString) - 9] = '\0';
    timeString += 4;
    timeString[0] = tolower(timeString[0]);
    
    return timeString;
}

int printLongFormat(const char *filename, const char *dir_name) {
    char buf[BUF_SIZE];
    sprintf(buf, "%s/%s", dir_name, filename);

    struct stat info;
    if(stat(buf, &info) == -1) {
        printf("failure statting file %s\n", filename);
        return EXIT_FAILURE;
    }

    //file type
    switch (info.st_mode & S_IFMT) {
        case S_IFBLK:  
            printf("b"); break;
        case S_IFCHR:  
            printf("c"); break;
        case S_IFDIR:  
            printf("d"); break;
        case S_IFIFO:  
            printf("p"); break;
        case S_IFLNK:  
            printf("l"); break;
        case S_IFREG:  
            printf("-"); break;
        case S_IFSOCK: 
            printf("s"); break;
        default:     
            printf("?");
    }

    //file permissions
    printf("%c", info.st_mode & S_IRUSR ? 'r' : '-');
    printf("%c", info.st_mode & S_IWUSR ? 'w' : '-');
    printf("%c", info.st_mode & S_IXUSR ? 'x' : '-');
    printf("%c", info.st_mode & S_IRGRP ? 'r' : '-');
    printf("%c", info.st_mode & S_IWGRP ? 'w' : '-');
    printf("%c", info.st_mode & S_IXGRP ? 'x' : '-');
    printf("%c", info.st_mode & S_IROTH ? 'r' : '-');
    printf("%c", info.st_mode & S_IWOTH ? 'w' : '-');
    printf("%c", info.st_mode & S_IXOTH ? 'x' : '-');

    //number of hard links
    printf(" %d", (int)info.st_nlink);

    //user and group id
    struct passwd *pwd;
    pwd = getpwuid(info.st_uid);
    struct group *grp;
    grp = getgrgid(info.st_gid);

    printf(" %s", pwd->pw_name);
    printf(" %s", grp->gr_name);

    //file size in bytes
    printf(" %7lld", (long long int)info.st_size);

    //modification date use info.st_mtim
    char *time = format_timeStr(info.st_mtim.tv_sec);
    if(time == NULL) return EXIT_FAILURE;
    printf(" %s", time);

    //filename goes last
    printf(" %s\n", filename);

    return EXIT_SUCCESS;
}

int listDirectory(DIR *directory, const char *dir_name) {
    struct dirent *p;

    while((p = readdir(directory)) ) {
        //We don't want to print dot files
        if(p->d_name[0] == '.') {
            continue;
        }

        if(printLongFormat(p->d_name, dir_name) == EXIT_FAILURE) {
            return EXIT_FAILURE;        
        }
    }

    return EXIT_SUCCESS;
}

//To improve, what can be done is to put every line in
//a string array to get total size, biggest length
//of size, number of hard links beforehand, so as to line 
//things up properly. For now, though, this is good enough
//and I don't feel like refactoring now :)
int main(int argc, char* argv[0]) {
    DIR *q;
    
    if(argc < 1) {
        printf("usage: %s dirname\n", argv[0]);
        return EXIT_FAILURE;
    }

    if(argc == 1) {
        q = opendir(".");
        if (q == NULL) {
            fprintf(stderr, "%s: Cannot open current directory\n",
            argv[0]);
            return EXIT_FAILURE;
        }

        listDirectory(q, ".");
        closedir(q);

        return EXIT_SUCCESS;
    }

    for(int i = 1; i < argc; i++) {
        q = opendir(argv[i]);
        if (q == NULL) {
            fprintf(stderr, "%s: Cannot open directory '%s'\n",
            argv[0], argv[i]);
            return EXIT_FAILURE;
        }

        listDirectory(q, argv[i]);
        closedir(q);
    }

    return EXIT_SUCCESS;
}      