**Interlude: Memory API**

- malloc
  - The malloc() call is quite simple: you pass it a size asking for some
    room on the heap, and it either succeeds and gives you back a pointer to
    the newly-allocated space, or fails and returns NULL
  - From this information, you can see that all you need to do is include
    the header file stdlib.h to use malloc. In fact, you don’t really need to
    even do this, as the C library, which all C programs link with by default,
    has the code for malloc() inside of it; adding the header just lets the
    compiler check whether you are calling malloc() correctly (e.g., passing
    the right number of arguments to it, of the right type).
  - The single parameter malloc() takes is of type size t which simply describes how many bytes you need. However, most programmers
    do not type in a number here directly (such as 10); indeed, it would be considered poor form to do so. Instead, various routines and macros are
    utilized. For example, to allocate space for a double-precision floating
    point value, you simply do this: double *d = (double *) malloc(sizeof(double));
  - This invocation of malloc() uses the
    sizeof() operator to request the right amount of space; in C, this is
    generally thought of as a compile-time operator, meaning that the actual
    size is known at compile time and thus a number (in this case, 8, for a
    double) is substituted as the argument to malloc(). For this reason,
    sizeof() is correctly thought of as an operator and not a function call
    (a function call would take place at run time)
- The free() Call
  - The routine takes one argument, a pointer returned by malloc().
    Thus, you might notice, the size of the allocated region is not passed in
    by the user, and must be tracked by the memory-allocation library itself.


- When you write a short-lived program, you might allocate some space
  using malloc(). The program runs and is about to complete: is there
  need to call free() a bunch of times just before exiting? While it seems
  wrong not to, no memory will be “lost” in any real sense. The reason is
  simple: there are really two levels of memory management in the system.
  The first level of memory management is performed by the OS, which
  hands out memory to processes when they run, and takes it back when
  processes exit (or otherwise die). The second level of management
  is within each process, for example within the heap when you call
  malloc() and free(). Even if you fail to call free() (and thus leak
  memory in the heap), the operating system will reclaim all the memory of
  the process (including those pages for code, stack, and, as relevant here,
  heap) when the program is finished running. No matter what the state
  of your heap in your address space, the OS takes back all of those pages
  when the process dies, thus ensuring that no memory is lost despite the
  fact that you didn’t free it.
  Thus, for short-lived programs, leaking memory often does not cause any
  operational problems (though it may be considered poor form). When
  you write a long-running server (such as a web server or database management system, which never exit), leaked memory is a much bigger issue, and will eventually lead to a crash when the application runs out of
  memory. And of course, leaking memory is an even larger issue inside
  one particular program: the operating system itself. Showing us once
  again: those who write the kernel code have the toughest job of all..


- tools
  - purify
  - valgrind
- Underlying OS Support
  - You might have noticed that we haven’t been talking about system
    calls when discussing malloc() and free(). The reason for this is simple: they are not system calls, but rather library calls. Thus the malloc library manages space within your virtual address space, but itself is built
    on top of some system calls which call into the OS to ask for more memory or release some back to the system.
    One such system call is called brk, which is used to change the location of the program’s break: the location of the end of the heap. It takes
    one argument (the address of the new break), and thus either increases or
    decreases the size of the heap based on whether the new break is larger
    or smaller than the current break. An additional call sbrk is passed an
    increment but otherwise serves a similar purpose.
    Note that you should never directly call either brk or sbrk. They
    are used by the memory-allocation library; if you try to use them, you
    will likely make something go (horribly) wrong. Stick to malloc() and
    free() instead.
    Finally, you can also obtain memory from the operating system via the
    mmap() call. By passing in the correct arguments, mmap() can create an
    anonymous memory region within your program — a region which is not
    associated with any particular file but rather with swap space, something
    we’ll discuss in detail later on in virtual memory. This memory can then
    also be treated like a heap and managed as such. Read the manual page
    of mmap() for more details.
- Other Calls
  - There are a few other calls that the memory-allocation library supports. For example, calloc() allocates memory and also zeroes it before returning; this prevents some errors where you assume that memory
    is zeroed and forget to initialize it yourself (see the paragraph on “uninitialized reads” above). The routine realloc() can also be useful, when
    you’ve allocated space for something (say, an array), and then need to
    add something to it: realloc() makes a new larger region of memory,
    copies the old region into it, and returns the pointer to the new region.
