#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

int _close(int fd) { return 0; }

int _execve(const char *path, char *const argv[], char *const envp[]) {
  errno = EACCES;
  return -1;
}

_Noreturn void _exit(int status) {
  register size_t a0 asm("a0") = status;
  register size_t a7 asm("a7") = 0;
  asm volatile("ecall" : : "r"(a0), "r"(a7));
  __builtin_unreachable();
}

int _fork(void) {
  errno = EAGAIN;
  return -1;
}

int _fstat(int fd, struct stat *buf) {
  buf->st_mode = S_IFCHR;
  return 0;
}

pid_t _getpid(void) {
  register size_t a0 asm("a0");
  register size_t a7 asm("a7") = 5;
  asm volatile("ecall" : "=r"(a0) : "r"(a7));
  return a0;
}

int _gettimeofday(struct timeval *tv, void *tz) { return 0; }

int _isatty(int fd) { return 1; }

int _kill(pid_t pid, int sig) {
  errno = EPERM;
  return -1;
}

int _link(const char *path1, const char *path2) {
  errno = EACCES;
  return -1;
}

_off_t _lseek(int fd, _off_t offset, int whence) {
  errno = ESPIPE;
  return -1;
}

int _open(const char *name, int flags, int mode) {
  errno = EACCES;
  return -1;
}

ssize_t _read(int fd, void *buf, size_t size) {
  register size_t a0 asm("a0") = fd;
  register size_t a1 asm("a1") = (size_t)buf;
  register size_t a2 asm("a2") = size;
  register size_t a7 asm("a7") = 1;
  asm volatile("ecall" : "+r"(a0) : "r"(a1), "r"(a2), "r"(a7));
  if ((int)a0 < 0) {
    errno = -((int)a0);
    return -1;
  }
  return a0;
}

void *_sbrk(ptrdiff_t incr) {
  static char heap[0x400000];
  static char *end = heap;
  char *prev_end = end;
  end += incr;
  return prev_end;
}

clock_t _times(struct tms *buf) { return -1; }

int _unlink(const char *path) {
  errno = EACCES;
  return -1;
}

pid_t _wait(int *status) {
  register size_t a0 asm("a0") = (size_t)status;
  register size_t a7 asm("a7") = 7;
  asm volatile("ecall" : "+r"(a0) : "r"(a7));
  if ((int)a0 < 0) {
    errno = -((int)a0);
    return -1;
  }
  return a0;
}

ssize_t _write(int fd, const void *buf, size_t size) {
  register size_t a0 asm("a0") = fd;
  register size_t a1 asm("a1") = (size_t)buf;
  register size_t a2 asm("a2") = size;
  register size_t a7 asm("a7") = 2;
  asm volatile("ecall" : "+r"(a0) : "r"(a1), "r"(a2), "r"(a7));
  if ((int)a0 < 0) {
    errno = -((int)a0);
    return -1;
  }
  return a0;
}
