# Malloc

## Author

[nkouris][nk]

[nk]: https://github.com/nkouris

## Brief Overview

This is an implementation of malloc that focuses on efficient defragmentation of memory and precise management of resources, 
using a red-black tree to manage the free spaces in mmaped regions and provide efficient lookup for regions that can fit requested 
memory blocks.

*	Regions of memory are tagged on the inital call to malloc(), and handed out from a "free tree" that tracks 
	regions that are unused.

	`An initial call to malloc() requesting n bytes will allocate a certain number of pages, tag the head of the region, offset by the 
	alignment value + n, place another tag that identifies how much free memory follows the tag, and add it to the "free tree"`
	
*	Pointers returned with free() are checked for validity, the pointer is offset by `- sizeof(tag)`, "free" bit is flipped, 
	the "free" bit is checked on links preceeding and succeeding the tag, and contiguous free segments are combined; the final 
	free tag is added to the "free tree"
