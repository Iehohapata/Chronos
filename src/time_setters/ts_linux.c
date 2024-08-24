#include "../includes.h"

int filecopy(char *src, char *trg);
void substract(const struct timespec *minued, const struct timespec *subst, struct timespec *diff);
void addtime(struct timespec *time, const struct timespec *adj);

int set_timestamp(char *filename, time_t time) {
    struct timespec curr, new;
    struct timespec op_start, op_finish;

    if (clock_gettime(CLOCK_REALTIME, &curr) == -1) {
        fprintf(stderr, "Unable to get current time");
        exit(EXIT_FAILURE);
    }

    new.tv_sec = time;
    new.tv_nsec = curr.tv_nsec;

    errno = 0;
    if (clock_settime(CLOCK_REALTIME, &new) == -1){
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    clock_gettime(CLOCK_MONOTONIC, &op_start);
    if (filecopy(filename, TEMP_NAME) != -1){
        unlink(filename);
        rename(TEMP_NAME, filename);
    }
    clock_gettime(CLOCK_MONOTONIC, &op_finish);

    struct timespec op_duration;
    substract(&op_finish, &op_start, &op_duration);
    addtime(&curr, &op_duration);
    clock_settime(CLOCK_REALTIME, &curr);

    exit(EXIT_SUCCESS);
}
void substract(const struct timespec *minued, const struct timespec *subst, struct timespec *diff){
    diff->tv_sec = minued->tv_sec - subst->tv_sec;
    diff->tv_nsec = minued->tv_nsec - subst->tv_nsec;
    if (diff->tv_nsec < 0) {
        diff->tv_sec--;
        diff->tv_nsec += SEC;
    }
}
void addtime(struct timespec *time, const struct timespec *adj) {
    long sum_nsec = time->tv_nsec + adj->tv_nsec;
    time->tv_sec += adj->tv_sec + (sum_nsec > SEC ? 1 : 0);
    time->tv_nsec =  sum_nsec % SEC;
}

int filecopy(char *src, char *trg) {
    int fd_s, fd_t, n;
    char buff[BUFSIZ];
    if ((fd_s = open(src, O_RDONLY, 0)) == -1) {
        fprintf(stderr, "Can't open file: %s\n", src);
        return -1;
    }
    if(access(trg, F_OK) == 1){
        fprintf(stderr, "%s: The file to be copied to already exists.", trg);
        return -1;
    }
    if ((fd_t = creat(trg, PERMS)) == -1) {
        fprintf(stderr, "Can't create file: %s\n", trg);
        return -1;
    }
    while((n = read(fd_s, buff, BUFSIZ)) > 0) {
        if (write(fd_t, buff, n) != n) {
            fprintf(stderr, "%s: Error while copying to the file.\n", trg);
            return -1;
        }
    }
    return 1;
}
