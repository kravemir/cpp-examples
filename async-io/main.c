#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <aio.h>
#include <signal.h>
#include <fcntl.h>

#define BUF_SIZE 4          /* Size of buffers for read operations */
#define IO_SIGNAL SIGUSR1   /* Signal used to notify I/O completion */

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define errMsg(msg)  do { perror(msg); } while (0)

static volatile sig_atomic_t gotSIGQUIT = 0;

struct aioRequest {
    int           finished;
    struct aiocb *aiocbp;
};

static void                 aioSigHandler(int sig, siginfo_t *si, void *ucontext);
static const char *         aioStatusToString(int status);
static struct aioRequest *  aioReadingStart(const char *filename);
static void                 quitHandler(int sig);

int
main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct sigaction sa;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    sa.sa_handler = quitHandler;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        errExit("sigaction");

    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = aioSigHandler;
    if (sigaction(IO_SIGNAL, &sa, NULL) == -1)
        errExit("sigaction");

    struct aioRequest *request = aioReadingStart(argv[1]);

    while (1) {
        sleep(3);       /* Delay between each monitoring step */

        if(request->finished) {
            break;
        }

        int status = aio_error(request->aiocbp);
        if (status != EINPROGRESS) {
            printf("aio_error() for request (descriptor %d): ", request->aiocbp->aio_fildes);
            printf("%s\n",aioStatusToString(status));
            break;
        }

        if (gotSIGQUIT) {
            /* On receipt of SIGQUIT, attempt to cancel I/O requests,
             * and display status returned
             * from the cancellation request */
            printf("got SIGQUIT; canceling I/O request: ");

            int s = aio_cancel(request->aiocbp->aio_fildes, request->aiocbp);
            if (s == AIO_CANCELED)
                printf("I/O canceled\n");
            else if (s == AIO_NOTCANCELED)
                printf("I/O not canceled\n");
            else if (s == AIO_ALLDONE)
                printf("I/O all done\n");
            else
                errMsg("aio_cancel");

            gotSIGQUIT = 0;
        }
    }

    printf("File reading completed\n");

    exit(EXIT_SUCCESS);
}

static
void aioSigHandler(int sig, siginfo_t *si, void *ucontext)
{
    struct aioRequest *request = si->si_value.sival_ptr;
    int bytes_read = aio_return(request->aiocbp);

    printf("I/O completion signal received %d: %.*s\n", bytes_read, bytes_read, request->aiocbp->aio_buf);

    // continue reading if whole buffer was filled
    if(bytes_read == BUF_SIZE) {
        request->aiocbp->aio_offset += bytes_read;

        if (aio_read(request->aiocbp) == -1)
            errExit("aio_read");
    } else {
        request->finished = 1;
    }
}

static
const char * aioStatusToString(int status) {
    switch (status) {
        case 0:
            return "I/O succeeded\n";
        case EINPROGRESS:
            return "In progress\n";
        case ECANCELED:
            return "Canceled\n";
        default:
            errMsg("aio_error");
            return 0;
    }
}

static
struct aioRequest * aioReadingStart(const char *filename) {
    struct aioRequest *request = malloc(sizeof(struct aioRequest));
    struct aiocb *aiocbInstance = malloc(sizeof(struct aiocb));

    if (request == NULL || aiocbInstance == NULL)
        errExit("malloc");

    request->finished = 0;
    request->aiocbp = aiocbInstance;

    request->aiocbp->aio_fildes = open(filename, O_RDONLY);
    if (request->aiocbp->aio_fildes == -1)
        errExit("open");
    printf("opened %s on descriptor %d\n", filename,
           request->aiocbp->aio_fildes);

    request->aiocbp->aio_buf = malloc(BUF_SIZE);
    if (request->aiocbp->aio_buf == NULL)
        errExit("malloc");

    request->aiocbp->aio_nbytes = BUF_SIZE;
    request->aiocbp->aio_reqprio = 0;
    request->aiocbp->aio_offset = 0;
    request->aiocbp->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    request->aiocbp->aio_sigevent.sigev_signo = IO_SIGNAL;
    request->aiocbp->aio_sigevent.sigev_value.sival_ptr = request;

    if (aio_read(request->aiocbp) == -1)
        errExit("aio_read");

    return request;
}

static void
quitHandler(int sig) {
    gotSIGQUIT = 1;
}
