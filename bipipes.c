#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	char* progs[2];
	for (int i = 1, j = 0; i < argc; ++i) {
		if (*argv[i] != '~') {
			progs[j] = argv[i];
			++j;
			if (j == 2) break;
		}
	}
	if (argc < 3) {
		printf("Usage: arg1 ~ arg2\n");
		exit(1);
	} else {
		printf("Set up bidirectional connection from %s to %s\n", progs[0], progs[1]);
	}

    int sv[2]; /* the pair of socket descriptors */
    char buf; /* for data exchange between processes */

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
        perror("socketpair");
        exit(1);
    }

    if (!fork()) {  /* child */ 
        read(sv[1], &buf, 1);
        printf("child: read '%c'\n", buf);
        buf = toupper(buf);  /* make it uppercase */
        write(sv[1], &buf, 1);
        printf("child: sent '%c'\n", buf);

    } else { /* parent */
        write(sv[0], "b", 1);
        printf("parent: sent 'b'\n");
        read(sv[0], &buf, 1);
        printf("parent: read '%c'\n", buf);
        wait(NULL); /* wait for child to die */
    }

    return 0;
}
