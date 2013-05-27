;
; Linux kernel interface (based on kernel 2.6.35.4).
; Should be compatible with the x32 ABI.
; You can learn more at https://sites.google.com/site/x32abi/home
;
; $Id: kernel.asm,v 1.3 2012/02/18 19:39:28 david Exp $
; $Log: kernel.asm,v $
; Revision 1.3  2012/02/18 19:39:28  david
; Minor cleanup work.
;
; Revision 1.1  2012/02/07 14:16:38  david
; Replaced the system call interface.
;
;

segment .data

; "errno" is a Standard C variable set by the syscall interface
global errno
errno	dd 0

segment	.text

%macro __save_context 0
  push  ebx
  push  ecx
  push  edx
  push  esi
  push  edi
  push  ebp
%endmacro

%macro __restore_context 0
  pop ebp
  pop edi
  pop esi
  pop edx
  pop ecx
  pop ebx
%endmacro

; _syscall number, #args, name
%macro __syscall 3
align 4
global sys_%3
sys_%3:
  __save_context

  mov eax, %1
  mov ebx, [esp+28]
  mov ecx, [esp+32]
  mov edx, [esp+36]
  mov esi, [esp+40]
  mov ebp, [esp+42]

  int 0x80

  __restore_context

  or  eax, eax
  js  .errno         ; jump if signed
  clc                ; clear carry flag
  ret

.errno:
  neg eax
  mov [errno], eax   ; set C-like errno variable
  stc                ; set carry flag
  ret
%endmacro

; list of syscalls in Linux kernel 2.6.35.4.

__syscall 1 , 2 , exit
__syscall 2 , 2 , fork
__syscall 3 , 4 , read
__syscall 4 , 4 , write
__syscall 5 , 4 , open
__syscall 6 , 2 , close
__syscall 7 , 4 , waitpid
__syscall 8 , 3 , creat
__syscall 9 , 3 , link
__syscall 10  , 2 , unlink
__syscall 11  , 5 , execve
__syscall 12  , 2 , chdir
__syscall 13  , 2 , time
__syscall 14  , 4 , mknod
__syscall 15  , 3 , chmod
__syscall 16  , 4 , lchown16
;__syscall 17  , 1 , not implemented
__syscall 18  , 3 , stat
__syscall 19  , 4 , lseek
__syscall 20  , 1 , getpid
__syscall 21  , 6 , mount
__syscall 22  , 2 , oldumount
__syscall 23  , 2 , setuid16
__syscall 24  , 1 , getuid16
__syscall 25  , 2 , stime
__syscall 26  , 5 , ptrace
__syscall 27  , 2 , alarm
__syscall 28  , 3 , fstat
__syscall 29  , 1 , pause
__syscall 30  , 3 , utime
;__syscall 31  , 1 , not implemented
;__syscall 32  , 1 , not implemented
__syscall 33  , 3 , access
__syscall 34  , 2 , nice
;__syscall 35  , 1 , not implemented
__syscall 36  , 1 , sync
__syscall 37  , 3 , kill
__syscall 38  , 3 , rename
__syscall 39  , 3 , mkdir
__syscall 40  , 2 , rmdir
__syscall 41  , 2 , dup
__syscall 42  , 2 , pipe
__syscall 43  , 2 , times
;__syscall 44  , 1 , not implemented
__syscall 45  , 2 , brk
__syscall 46  , 2 , setgid16
__syscall 47  , 1 , getgid16
__syscall 48  , 3 , signal
__syscall 49  , 1 , geteuid16
__syscall 50  , 1 , getegid16
__syscall 51  , 2 , acct
__syscall 52  , 3 , umount
;__syscall 53  , 1 , not implemented
__syscall 54  , 4 , ioctl
__syscall 55  , 4 , fcntl
;__syscall 56  , 1 , not implemented
__syscall 57  , 3 , setpgid
;__syscall 58  , 1 , not implemented
__syscall 59  , 2 , olduname
__syscall 60  , 2 , umask
__syscall 61  , 2 , chroot
__syscall 62  , 3 , ustat
__syscall 63  , 3 , dup2
__syscall 64  , 1 , getppid
__syscall 65  , 1 , getpgrp
__syscall 66  , 1 , setsid
__syscall 67  , 4 , sigaction
__syscall 68  , 1 , sgetmask
__syscall 69  , 2 , ssetmask
__syscall 70  , 3 , setreuid16
__syscall 71  , 3 , setregid16
__syscall 72  , 4 , sigsuspend
__syscall 73  , 2 , sigpending
__syscall 74  , 3 , sethostname
__syscall 75  , 3 , setrlimit
__syscall 76  , 3 , old_getrlimit
__syscall 77  , 3 , getrusage
__syscall 78  , 3 , gettimeofday
__syscall 79  , 3 , settimeofday
__syscall 80  , 3 , getgroups16
__syscall 81  , 3 , setgroups16
__syscall 82  , 2 , old_select
__syscall 83  , 3 , symlink
__syscall 84  , 3 , lstat
__syscall 85  , 4 , readlink
__syscall 86  , 2 , uselib
__syscall 87  , 3 , swapon
__syscall 88  , 5 , reboot
__syscall 89  , 4 , old_readdir
__syscall 90  , 2 , old_mmap
__syscall 91  , 3 , munmap
__syscall 92  , 3 , truncate
__syscall 93  , 3 , ftruncate
__syscall 94  , 3 , fchmod
__syscall 95  , 4 , fchown16
__syscall 96  , 3 , getpriority
__syscall 97  , 4 , setpriority
;__syscall 98  , 1 , not implemented
__syscall 99  , 3 , statfs
__syscall 100 , 3 , fstatfs
__syscall 101 , 4 , ioperm
__syscall 102 , 3 , socketcall
__syscall 103 , 4 , syslog
__syscall 104 , 4 , setitimer
__syscall 105 , 3 , getitimer
__syscall 106 , 3 , newstat
__syscall 107 , 3 , newlstat
__syscall 108 , 3 , newfstat
__syscall 109 , 2 , uname
__syscall 110 , 3 , iopl
__syscall 111 , 1 , vhangup
;__syscall 112 , 1 , not implemented
__syscall 113 , 3 , vm86old
__syscall 114 , 5 , wait4
__syscall 115 , 2 , swapoff
__syscall 116 , 2 , sysinfo
__syscall 117 , 1 , ipc
__syscall 118 , 2 , fsync
__syscall 119 , 2 , sigreturn
__syscall 120 , 6 , clone
__syscall 121 , 3 , setdomainname
__syscall 122 , 2 , newuname
__syscall 123 , 4 , modify_ldt
__syscall 124 , 2 , adjtimex
__syscall 125 , 4 , mprotect
__syscall 126 , 4 , sigprocmask
;__syscall 127 , 1 , not implemented
__syscall 128 , 4 , init_module
__syscall 129 , 3 , delete_module
;__syscall 130 , 1 , not implemented
__syscall 131 , 5 , quotactl
__syscall 132 , 2 , getpgid
__syscall 133 , 2 , fchdir
__syscall 134 , 3 , bdflush
__syscall 135 , 4 , sysfs
__syscall 136 , 2 , personality
;__syscall 137 , 1 , not implemented
__syscall 138 , 2 , setfsuid16
__syscall 139 , 2 , setfsgid16
__syscall 140 , 6 , llseek
__syscall 141 , 4 , getdents
__syscall 142 , 6 , select
__syscall 143 , 3 , flock
__syscall 144 , 4 , msync
__syscall 145 , 4 , readv
__syscall 146 , 4 , writev
__syscall 147 , 2 , getsid
__syscall 148 , 2 , fdatasync
__syscall 149 , 2 , sysctl
__syscall 150 , 3 , mlock
__syscall 151 , 3 , munlock
__syscall 152 , 2 , mlockall
__syscall 153 , 1 , munlockall
__syscall 154 , 3 , sched_setparam
__syscall 155 , 3 , sched_getparam
__syscall 156 , 4 , sched_setscheduler
__syscall 157 , 2 , sched_getscheduler
__syscall 158 , 1 , sched_yield
__syscall 159 , 2 , sched_get_priority_max
__syscall 160 , 2 , sched_get_priority_min
__syscall 161 , 3 , sched_rr_get_interval
__syscall 162 , 3 , nanosleep
__syscall 163 , 6 , mremap
__syscall 164 , 4 , setresuid16
__syscall 165 , 4 , getresuid16
__syscall 166 , 4 , vm86
;__syscall 167 , 1 , not implemented
__syscall 168 , 4 , poll
__syscall 169 , 4 , nfsservctl
__syscall 170 , 4 , setresgid16
__syscall 171 , 4 , getresgid16
__syscall 172 , 6 , prctl
__syscall 173 , 2 , rt_sigreturn
__syscall 174 , 5 , rt_sigaction
__syscall 175 , 5 , rt_sigprocmask
__syscall 176 , 3 , rt_sigpending
__syscall 177 , 5 , rt_sigtimedwait
__syscall 178 , 4 , rt_sigqueueinfo
__syscall 179 , 3 , rt_sigsuspend
__syscall 180 , 5 , pread64
__syscall 181 , 5 , pwrite64
__syscall 182 , 4 , chown16
__syscall 183 , 3 , getcwd
__syscall 184 , 3 , capget
__syscall 185 , 3 , capset
__syscall 186 , 4 , sigaltstack
__syscall 187 , 5 , sendfile
;__syscall 188 , 1 , not implemented
;__syscall 189 , 1 , not implemented
__syscall 190 , 2 , vfork
__syscall 191 , 3 , getrlimit
__syscall 192 , 1 , mmap_pgoff
__syscall 193 , 3 , truncate64
__syscall 194 , 3 , ftruncate64
__syscall 195 , 3 , stat64
__syscall 196 , 3 , lstat64
__syscall 197 , 3 , fstat64
__syscall 198 , 4 , lchown
__syscall 199 , 1 , getuid
__syscall 200 , 1 , getgid
__syscall 201 , 1 , geteuid
__syscall 202 , 1 , getegid
__syscall 203 , 3 , setreuid
__syscall 204 , 3 , setregid
__syscall 205 , 3 , getgroups
__syscall 206 , 3 , setgroups
__syscall 207 , 4 , fchown
__syscall 208 , 4 , setresuid
__syscall 209 , 4 , getresuid
__syscall 210 , 4 , setresgid
__syscall 211 , 4 , getresgid
__syscall 212 , 4 , chown
__syscall 213 , 2 , setuid
__syscall 214 , 2 , setgid
__syscall 215 , 2 , setfsuid
__syscall 216 , 2 , setfsgid
__syscall 217 , 3 , pivot_root
__syscall 218 , 4 , mincore
__syscall 219 , 4 , madvise
__syscall 220 , 4 , getdents64
__syscall 221 , 4 , fcntl64
;__syscall 222 , 1 , not implemented
;__syscall 223 , 1 , not implemented
__syscall 224 , 1 , gettid
__syscall 225 , 4 , readahead
__syscall 226 , 6 , setxattr
__syscall 227 , 6 , lsetxattr
__syscall 228 , 6 , fsetxattr
__syscall 229 , 5 , getxattr
__syscall 230 , 5 , lgetxattr
__syscall 231 , 5 , fgetxattr
__syscall 232 , 4 , listxattr
__syscall 233 , 4 , llistxattr
__syscall 234 , 4 , flistxattr
__syscall 235 , 3 , removexattr
__syscall 236 , 3 , lremovexattr
__syscall 237 , 3 , fremovexattr
__syscall 238 , 3 , tkill
__syscall 239 , 5 , sendfile64
__syscall 240 , 1 , futex
__syscall 241 , 4 , sched_setaffinity
__syscall 242 , 4 , sched_getaffinity
__syscall 243 , 2 , set_thread_area
__syscall 244 , 2 , get_thread_area
__syscall 245 , 3 , io_setup
__syscall 246 , 2 , io_destroy
__syscall 247 , 6 , io_getevents
__syscall 248 , 4 , io_submit
__syscall 249 , 4 , io_cancel
__syscall 250 , 5 , fadvise64
;__syscall 251 , 1 , not implemented
__syscall 252 , 2 , exit_group
__syscall 253 , 4 , lookup_dcookie
__syscall 254 , 2 , epoll_create
__syscall 255 , 5 , epoll_ctl
__syscall 256 , 5 , epoll_wait
__syscall 257 , 6 , remap_file_pages
__syscall 258 , 2 , set_tid_address
__syscall 259 , 4 , timer_create
__syscall 260 , 5 , timer_settime
__syscall 261 , 3 , timer_gettime
__syscall 262 , 2 , timer_getoverrun
__syscall 263 , 2 , timer_delete
__syscall 264 , 3 , clock_settime
__syscall 265 , 3 , clock_gettime
__syscall 266 , 3 , clock_getres
__syscall 267 , 5 , clock_nanosleep
__syscall 268 , 4 , statfs64
__syscall 269 , 4 , fstatfs64
__syscall 270 , 4 , tgkill
__syscall 271 , 3 , utimes
__syscall 272 , 5 , fadvise64_64
;__syscall 273 , 1 , not implemented
__syscall 274 , 1 , mbind
__syscall 275 , 6 , get_mempolicy
__syscall 276 , 4 , set_mempolicy
__syscall 277 , 5 , mq_open
__syscall 278 , 2 , mq_unlink
__syscall 279 , 6 , mq_timedsend
__syscall 280 , 6 , mq_timedreceive
__syscall 281 , 3 , mq_notify
__syscall 282 , 4 , mq_getsetattr
__syscall 283 , 5 , kexec_load
__syscall 284 , 6 , waitid
;__syscall 285 , 1 , not implemented
__syscall 286 , 6 , add_key
__syscall 287 , 5 , request_key
__syscall 288 , 6 , keyctl
__syscall 289 , 4 , ioprio_set
__syscall 290 , 3 , ioprio_get
__syscall 291 , 1 , inotify_init
__syscall 292 , 4 , inotify_add_watch
__syscall 293 , 3 , inotify_rm_watch
__syscall 294 , 5 , migrate_pages
__syscall 295 , 5 , openat
__syscall 296 , 4 , mkdirat
__syscall 297 , 5 , mknodat
__syscall 298 , 6 , fchownat
__syscall 299 , 4 , futimesat
__syscall 300 , 5 , fstatat64
__syscall 301 , 4 , unlinkat
__syscall 302 , 5 , renameat
__syscall 303 , 6 , linkat
__syscall 304 , 4 , symlinkat
__syscall 305 , 5 , readlinkat
__syscall 306 , 4 , fchmodat
__syscall 307 , 4 , faccessat
__syscall 308 , 1 , pselect6
__syscall 309 , 6 , ppoll
__syscall 310 , 2 , unshare
__syscall 311 , 3 , set_robust_list
__syscall 312 , 4 , get_robust_list
__syscall 313 , 1 , splice
__syscall 314 , 5 , sync_file_range
__syscall 315 , 5 , tee
__syscall 316 , 5 , vmsplice
__syscall 317 , 1 , move_pages
__syscall 318 , 4 , getcpu
__syscall 319 , 1 , epoll_pwait
__syscall 320 , 5 , utimensat
__syscall 321 , 4 , signalfd
__syscall 322 , 3 , timerfd_create
__syscall 323 , 2 , eventfd
__syscall 324 , 5 , fallocate
__syscall 325 , 5 , timerfd_settime
__syscall 326 , 3 , timerfd_gettime
__syscall 327 , 5 , signalfd4
__syscall 328 , 3 , eventfd2
__syscall 329 , 2 , epoll_create1
__syscall 330 , 4 , dup3
__syscall 331 , 3 , pipe2
__syscall 332 , 2 , inotify_init1
__syscall 333 , 6 , preadv
__syscall 334 , 6 , pwritev
__syscall 335 , 5 , rt_tgsigqueueinfo
__syscall 336 , 6 , perf_event_open
__syscall 337 , 6 , recvmmsg

; a few more exist in later kernels and will eventually be included in this list
