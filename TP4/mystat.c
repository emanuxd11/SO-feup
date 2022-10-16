#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pwd.h>

/******************************************************************/
int timespec2str(char *buf, uint len, struct timespec *ts) {
    int ret;
    struct tm t;

    tzset();
    if (localtime_r(&(ts->tv_sec), &t) == NULL)
        return 1;

    ret = strftime(buf, len, "%F %T", &t);
    if (ret == 0)
        return 2;
    len -= ret - 1;

    ret = snprintf(&buf[strlen(buf)], len, ".%09ld", ts->tv_nsec);
    if (ret >= len)
        return 3;

    return 0;
}
/******************************************************************/

int main(int argc, char* argv[]) {
    struct stat info;

    if(argc < 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        return EXIT_FAILURE;
    }

    int total_size = 0;
    int total_blck = 0;

    for(int i = 1; i < argc; i++) {
        if(stat(argv[i], &info) == -1) {
            fprintf(stderr, "fsize: Can't stat %s\n", argv[1]);
            return EXIT_FAILURE;
        }

        printf("  File: %s\n", argv[1]);
        printf("  Size: %d bytes, disk_blocks: %d\n",
        (int)info.st_size, (int)info.st_blocks);

        /******************************************************************/
        char *str;
        const uint TIME_FMT = strlen("9999-12-31 12:59:59.123456789") + 1;
        char timestr[TIME_FMT];
        if (timespec2str(timestr, sizeof(timestr), &info.st_mtim) != 0) {
            printf("timespec2str failed!\n");
            return EXIT_FAILURE;
        } else {
            printf("Modify: time=%s\n", timestr);
        }
        /******************************************************************/
        
        /******************************************************************/
        struct passwd *pwd;
        pwd = getpwuid(info.st_uid);
        if(pwd == NULL) return EXIT_FAILURE;
        printf("   Uid: ( %d/    %s)\n", info.st_uid, pwd->pw_name);
        /******************************************************************/

        total_size += (int)info.st_size;
        total_blck += (int)info.st_blocks;
    }

    if(argc > 2) {
        printf("Total file size: %d bytes, total disk_blocks: %d\n",
        total_size, total_blck);
    }

    return EXIT_SUCCESS;
}