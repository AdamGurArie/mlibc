#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <stddef.h>

#define SYSCALL0(NUM) ({ \
	asm volatile ("int $0x80" \
				  : "=a"(ret), "=d"(errno) \
				  : "a"(NUM) \
				  : "memory"); \
})

#define SYSCALL1(NUM, ARG0) ({ \
	asm volatile ("int $0x80" \
				  : "=a"(ret), "=d"(errno) \
				  : "a"(NUM), "D"(ARG0) \
				  : "memory"); \
})

#define SYSCALL2(NUM, ARG0, ARG1) ({ \
	asm volatile ("int $0x80" \
				  : "=a"(ret), "=d"(errno) \
				  : "a"(NUM), "D"(ARG0), "S"(ARG1) \
				  : "memory"); \
})

#define SYSCALL3(NUM, ARG0, ARG1, ARG2) ({ \
	asm volatile ("int $0x80" \
				  : "=a"(ret), "=d"(errno) \
				  : "a"(NUM), "D"(ARG0), "S"(ARG1), "d"(ARG2) \
				  : "memory"); \
})

#define SYSCALL4(NUM, ARG0, ARG1, ARG2, ARG3) ({ \
	asm volatile ("int $0x80" \
				  : "=a"(ret), "=d"(errno) \
				  : "a"(NUM), "D"(ARG0), "S"(ARG1), "d"(ARG2), "c"(ARG3) \
				  : "memory"); \
})

#define SYSCALL6(NUM, ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) ({ \
	register uint64_t arg_r8 asm("r8") = (uint64_t)ARG4; \
	register uint64_t arg_r9 asm("r9") = (uint64_t)ARG5; \
	asm volatile ("int $0x80" \
				  : "=a"(ret), "=d"(errno) \
				  : "a"(NUM), "D"(ARG0), "S"(ARG1), "d"(ARG2), \
					"c"(ARG3), "r"(arg_r8), "r"(arg_r9) \
				  : "memory"); \
})

#define SYS_TEST 1
#define SYS_ANON_ALLOC 2
#define SYS_ANON_FREE 3
#define SYS_CREATE_TASK 4
#define SYS_DELETE_TASK 5
#define SYS_LIBC_LOG 6
#define SYS_LIBC_PANIC 7
#define SYS_OPEN_FILE 8
#define SYS_READ_FILE 9
#define SYS_SEEK_FILE 10
#define SYS_CLOSE_FILE 11
#define SYS_VM_MAP 12
#define SYS_VM_UNMAP 13

#endif // _SYSCALL_H
