#include <bits/ensure.h>
#include <mlibc/debug.hpp>
#include <mlibc/all-sysdeps.hpp>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <asm/ioctls.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/syscall.h>

namespace mlibc {

void sys_libc_log(const char *message) {
	/*
	ssize_t unused;
	char new_line = '\n';
	sys_write(1, message, strlen(message), &unused);
	sys_write(1, &new_line, 1, &unused);
	*/
	(void)message;
	return;
}

void sys_libc_panic() {
	ssize_t unused;
	char const *message = "mlibc panicked unrecoverably\n";
	SYSCALL0(SYS_LIBC_PANIC);
}

void sys_exit(int status) {
	int ret, errno;
	SYSCALL1(SYS_DELETE_);
	__builtin_unreachable();
}

int sys_tcb_set(void *pointer) {
	//int ret, errno;
	//SYSCALL1(SYSCALL_SET_TCB, pointer);
	return 0; //errno;
}

int sys_open(const char *path, int flags, mode_t mode, int *fd) {
	int ret, errno;
	(void)mode;

	SYSCALL2(SYS_OPEN_FILE, path, flags);
	*fd = ret;
	return errno;
}

int sys_open_dir(const char *path, int *handle) {
	return sys_open(path, O_RDONLY, 0660, handle);
}

int sys_close(int fd) {
	int ret, errno;
	SYSCALL1(SYS_CLOSE_FILE, fd);
	return errno;
}

int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
	ssize_t ret;
	int errno;
	SYSCALL3(SYS_READ_FILE, fd, buf, count);
	*bytes_read = ret;
	return errno;
}

int sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written) {
	/*ssize_t ret;
	int errno;
	SYSCALL3(SYSCALL_WRITE, fd, buf, count);
	*bytes_written = ret;
	return errno;*/
    return 0;
}

int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
	ssize_t ret;
	int errno;
	SYSCALL3(SYS_SEEK_FILE, fd, offset, whence);
	*new_offset = ret;
	return errno;
}

int sys_anon_allocate(size_t size, void **pointer) {
    int errno;
    SYSCALL2(SYS_ANON_ALLOC, size, pointer);
    return errno;
	//return sys_vm_map(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON, 0, 0, pointer);
}

int sys_anon_free(void *pointer, size_t size) {
    int errno;
    SYSCALL2(SYS_ANON_FREE, size, pointer);
	return sys_vm_unmap(pointer, size);
}

int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window) {
	void *ret;
	int errno;
	SYSCALL3(SYS_VM_MAP, hint, size, flags);
	*window = ret;
	return errno;
}

int sys_vm_unmap(void *pointer, size_t size) {
	int ret;
	int errno;
	SYSCALL2(SYSCALL_UNMAP, pointer, size);
	if (ret != 0) {
		return errno;
	} else {
		return 0;
	}
}

} // namespace mlibc
