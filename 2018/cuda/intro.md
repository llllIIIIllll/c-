RISC
====
Instruction fetch(IF)
Instruction decode(ID)
Instruction execute(Ex)
Memory access(Mem)
Register write-back(WB)

Pipelining
======


CUDA PROGRAME STRUCTURE
======
1.Allocate GPU memories.
2.Copy date from CPU memory to GPU memory.
3.Invoke the CUDA kernel to perform programe-specific computation.
4.Copy data back from GPU memory to CPU memory.
5.Destroy GPU memory.


Shared memory
========
can be thought of as a software-managed cache, which provides great speedup
by conserving bandwidth to main memory. With shared memory, you can control the locality of
your code directly.


GUIDELINES FOR GRID AND BLOCK SIZE
=======
1.keep the number of threads per block a multiple of warp size (32).
2.Avoid samll block size: Start with at least 128 or 256 threads per block.
3.Adjust block size up or down according to kernel resource requirement.
4.Keep the number of blocks much greater than the number of SMs to expose sufficient parallelism to your device.
5.Conduct experiments to discover the best execution configuration and resource usage.

