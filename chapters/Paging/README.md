**Paging: Introduction**

- Correspondingly, we view
  physical memory as an array of fixed-sized slots called page frames; each
  of these frames can contain a single virtual-memory page.

![1739919526615](image/README/1739919526615.png)

In the example, the OS
has placed virtual page 0 of the address space (AS) in physical frame 3,
virtual page 1 of the AS in physical frame 7, page 2 in frame 5, and page
3 in frame 2. Page frames 1, 4, and 6 are currently free.

- To record where each virtual page of the address space is placed in
  physical memory, the operating system usually keeps a per-process data
  structure known as a page table.
  - The major role of the page table is to
    store address translations for each of the virtual pages of the address
    space, thus letting us know where in physical memory each page resides.
    For our simple example (Figure 18.2, page 2), the page table would thus
    have the following four entries: (Virtual Page 0 → Physical Frame 3),
    (VP 1 → PF 7), (VP 2 → PF 5), and (VP 3 → PF 2).
  - It is important to remember that this page table is a per-process data
    structure (most page table structures we discuss are per-process structures; an exception we’ll touch on is the inverted page table). If another
    process were to run in our example above, the OS would have to manage
    a different page table for it, as its virtual pages obviously map to different
    physical pages (modulo any sharing going on).
- movl , %eax
  - Specifically, let’s pay attention to the explicit load of the data from
    address  into the register eax (and thus ignore the
    instruction fetch that must have happened prior).
  - To translate this virtual address that the process generated, we have
    to first split it into two components: the virtual page number (VPN), and
    the offset within the page. For this example, because the virtual address
    space of the process is 64 bytes, we need 6 bits total for our virtual address
    (2
    6 = 64). Thus, our virtual address can be conceptualized as follows:
    ![1739920330476](image/README/1739920330476.png)
  - In this diagram, Va5 is the highest-order bit of the virtual address, and
    Va0 the lowest-order bit. Because we know the page size (16 bytes), we
    can further divide the virtual address as follows:
    ![1739920519523](image/README/1739920519523.png)
- When a process generates a virtual address, the OS and hardware
  must combine to translate it into a meaningful physical address. For example, let us assume the load above was to virtual address 21:
  movl 21, %eax
  - Turning “21” into binary form, we get “010101”, and thus we can examine this virtual address and see how it breaks down into a virtual page
    number (VPN) and offset:
    ![1739920656973](image/README/1739920656973.png)
  - Thus, the virtual address “21” is on the 5th (“0101”th) byte of virtual
    page “01” (or 1). With our virtual page number, we can now index our
    page table and find which physical frame virtual page 1 resides within. In
    the page table above the physical frame number (PFN) (also sometimes
    called the physical page number or PPN) is 7 (binary 111). Thus, we can
    translate this virtual address by replacing the VPN with the PFN and then
    issue the load to physical memory (Figure 18.3).
    ![1739920784549](image/README/1739920784549.png)
  - ![1739920856740](image/README/1739920856740.png)
  - Note the offset stays the same (i.e., it is not translated), because the
    offset just tells us which byte within the page we want. Our final physical
    address is 1110101 (117 in decimal), and is exactly where we want our
    load to fetch data from (Figure 18.2, page 2).
- Where Are Page Tables Stored?
  - Page tables can get terribly large, much bigger than the small segment
    table or base/bounds pair we have discussed previously. For example,
    imagine a typical 32-bit address space, with 4KB pages. This virtual address splits into a 20-bit VPN and 12-bit offset (recall that 10 bits would
    be needed for a 1KB page size, and just add two more to get to 4KB).
  - A 20-bit VPN implies that there are 2
    20 translations that the OS would
    have to manage for each process (that’s roughly a million); assuming we
    need 4 bytes per page table entry (PTE) to hold the physical translation
    plus any other useful stuff, we get an immense 4MB of memory needed
    for each page table! That is pretty large. Now imagine there are 100
    processes running: this means the OS would need 400MB of memory
    just for all those address translations!
  - Because page tables are so big, we don’t keep any special on-chip hardware in the MMU to store the page table of the currently-running process.
    Instead, we store the page table for each process in memory somewhere.
    Let’s assume for now that the page tables live in physical memory that
    the OS manages; later we’ll see that much of OS memory itself can be virtualized, and thus page tables can be stored in OS virtual memory (and
    even swapped to disk), but that is too confusing right now, so we’ll ignore it. In Figure 18.4 (page 5) is a picture of a page table in OS memory;
    see the tiny set of translations in there?
  - One of the most important data structures in the memory management
    subsystem of a modern OS is the page table. In general, a page table
    stores virtual-to-physical address translations, thus letting the system
    know where each page of an address space actually resides in physical
    memory. Because each address space requires such translations, in general there is one page table per process in the system. The exact structure
    of the page table is either determined by the hardware (older systems) or
    can be more flexibly managed by the OS (modern systems).
- What’s Actually In The Page Table?
  - The page table is just
    a data structure that is used to map virtual addresses (or really, virtual
    page numbers) to physical addresses (physical frame numbers)
  - The OS indexes the array by the virtual page
    number (VPN), and looks up the page-table entry (PTE) at that index in
    order to find the desired physical frame number (PFN)
