#define _XOPEN_SOURCE 500
#include "logger.h"
#include <sys/inotify.h>
#include <limits.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

    int inotifyFd, wd;
    int ftwFlag = 0;
    char buf[BUF_LEN];
    ssize_t numRead;
    char *p;
    struct inotify_event *event;

static int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf){
    wd = inotify_add_watch(inotifyFd, fpath, IN_ALL_EVENTS); 
    
    if(wd == -1) {
        return -1;
    }
    return 0;
}

static void displayInotifyEvent(struct inotify_event *i) {
    if (i->mask & IN_CREATE) {
        if(i->mask & IN_ISDIR) {
            infof("- [Directory - Create] - %s\n", i -> name);
        } else {
            infof("- [File  - Create] - %s\n", i -> name);
        }
    }
    if (i->mask & IN_DELETE) {
        if(i->mask & IN_ISDIR) {
            infof("- [Directory - Removal] - %s\n", i -> name);
        } else {
            infof("- [File  - Removal] - %s\n", i -> name);
        }
    }
    if (i->mask & IN_MOVED_FROM) {
        if(i->mask & IN_ISDIR) {
            infof("- [Directory - Rename from] - %s\n", i -> name);
        } else {
            infof("- [File  - Rename from] - %s\n", i -> name);
        }
    }
    if (i->mask & IN_MOVED_TO) {
        if(i->mask & IN_ISDIR) {
            infof("- [Directory - Rename to] - %s\n", i -> name);
        } else {
            infof("- [File  - Rename to] - %s\n", i -> name);
        }
    }
}

int main(int argc, char **argv){
    
    if(argc < 2){
		errorf("Incorrect number of arguments.\n");
        return 0;
	}

    printf("Starting File/Directory Monitor on %s \n", argv[1]);

    inotifyFd=inotify_init();

    if (inotifyFd == -1) {
		warnf("inotify_init failed");
        errorf("inotifyFd creation error");
		return 0;
	}

    if (argc > 2 && strchr(argv[2], 'd') != NULL) {
        ftwFlag |= FTW_DEPTH;
    }

    if (argc > 2 && strchr(argv[2], 'p') != NULL) {
        ftwFlag |= FTW_PHYS;
    }

    if (nftw((argc < 2) ? "." : argv[1], display_info, 20, ftwFlag) == -1) {
		panicf("nftw failed");
        return 0;
	}

    while (1) {
        numRead = read(inotifyFd, buf, BUF_LEN);
    
        if (numRead == 0){
            panicf("read() from inotify fd returned 0!");
            return 0;
        }

        if (numRead == -1) {
            errorf("read");
            return 0;
        }

        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *) p;
            displayInotifyEvent(event);

            p += sizeof(struct inotify_event) + event->len;
        }
    }
    return 1;
}
