#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

int printLongFormat(const char *filename) {
    struct stat info;
    if(stat(filename, &info) == -1) {
        return EXIT_FAILURE;
    }
    //for getting user and group id
    struct passwd *pwd;
    pwd = getpwuid(info.st_uid);
    struct group *grp;
    grp = getgrgid(info.st_gid);

    //file permissions
    printf("%c", '-'); //must check if file is directory
    printf("%c", info.st_mode & S_IRUSR ? 'r' : '-');
    printf("%c", info.st_mode & S_IWUSR ? 'w' : '-');
    printf("%c", info.st_mode & S_IXUSR ? 'x' : '-');
    printf("%c", info.st_mode & S_IRGRP ? 'r' : '-');
    printf("%c", info.st_mode & S_IWGRP ? 'w' : '-');
    printf("%c", info.st_mode & S_IXGRP ? 'x' : '-');
    printf("%c", info.st_mode & S_IROTH ? 'r' : '-');
    printf("%c", info.st_mode & S_IWOTH ? 'w' : '-');
    printf("%c", info.st_mode & S_IXOTH ? 'x' : '-');

    printf(" %d", 1); //must figure out second column

    //user and group id
    printf(" %s", pwd->pw_name);
    printf(" %s", grp->gr_name);

    //file size in bytes
    printf(" %7d", (int)info.st_size);

    //modification date
    printf(" date-of-mod-hour");

    //filename goes last
    printf(" %s\n", filename);

    return EXIT_SUCCESS;
}

void listDirectory(DIR *directory) {
    struct dirent *p;

    while((p = readdir(directory)) ) {
        //We don't want to print dot files
        if(p->d_name[0] == '.') {
            continue;
        }

        printLongFormat(p->d_name);
    }
}

int main(int argc, char** argv) {
    DIR *q;
    
    if(argc < 1) {
        fprintf (stderr, "usage: %s dirname\n", argv[0]);
        return EXIT_FAILURE;
    }

    for(int i = 1; i < argc; i++) {
        q = opendir(argv[i]);
        if (q == NULL) {
            fprintf(stderr, "%s: Cannot open directory '%s'\n",
            argv[0], argv[i]);
            return EXIT_FAILURE;
        }

        listDirectory(q);

        closedir(q);
    }

    return EXIT_SUCCESS;
}      