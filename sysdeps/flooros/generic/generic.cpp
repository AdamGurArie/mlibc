#include "stddef.h"
#include "mlibc/options/internal/include/bits/off_t.h"
#include <userspace/syscalls/syscalls.h>

#include "src/memoryManager/paging.h"

void sys_libc_log(const char *message){
    syscall_1(SYS_LIBC_LOG, (uint64_t)message);
}

[[noreturn]] void sys_libc_panic(){
    syscall_1(SYS_LIBC_PANIC, (uint64_t)0);
}

int sys_tcb_set(void *pointer){
    
}

[[gnu::weak]] int sys_futex_tid(){
    return 0;
}

int sys_futex_wait(int *pointer, int expected, const struct timespec *time){
    return 0;
}

int sys_futex_wake(int *pointer){
    return 0;
}

int sys_anon_allocate(size_t size, void **pointer){
    syscall_2(SYS_ANON_ALLOC, size, (uint64_t)pointer);
    int out;
    asm volatile("movq %%rax, %[Var]" : [Var] "=r" (out));
}
int sys_anon_free(void *pointer, size_t size){
    syscall_2(SYS_ANON_FREE, (uint64_t)pointer, size);
    int out;
    asm volatile("movq %%rax, %[Var]" : [Var] "=r" (out));
}

int sys_open(const char *pathname, int flags, mode_t mode, int *fd){
    syscall_2(SYS_OPEN_FILE, (uint64_t)pathname, flags, mode);
    int out;
    asm volatile("movq %%rax, %[Var]" : [Var] "=r" (out));
}

int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read){
    syscall_3(SYS_READ_FILE, fd, (uint64_t)buf, count);
    int out;
    asm volatile("movq %%rax, %[Var]" : [Var] "=r" (out));
}

int sys_seek(int fd, off_t offset, int whence, off_t *new_offset){
    syscall_2(SYS_SEEK_FILE, fd, offset);
    int out;
    asm volatile("movq %%rax, %[Var]" : [Var] "=r" (out));
}

int sys_close(int fd){
    syscall_1(SYS_CLOSE_FILE, fd);
    int out;
    asm volatile("movq %%rax, %[Var]" : [Var] "=r" (out));
}