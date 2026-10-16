#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv) {
    int fd;
    char buffer[1024];
    int n;

    // borra FIFO por si existiera previamente
    unlink("/tmp/FIFO_LOGGER");
    /* crea el FIFO */
    if (mkfifo("/tmp/FIFO_LOGGER", 0600) < 0) {
        perror("No puede crearse el FIFO");
        return(1);
    }
    /* Abre el FIFO */
    if ((fd = open("/tmp/FIFO_LOGGER", O_RDONLY)) < 0) {
        perror("No puede abrirse el FIFO");
        return(1);
    }
    while ((n=read(fd, buffer, sizeof(buffer)-1)) > 0) {
    buffer[n] ='\0';
    printf("%s", buffer);
    fflush(stdout);
    }
    close(fd);
    unlink("/tmp/FIFO_LOGGER");
    return(0);
}

