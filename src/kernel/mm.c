#include <kernel/mm.h>
#include <kernel/pmm.h>

extern pmm_page_t 					pmm_allocated[PHYS_MAX_BLOCKS];   
extern unsigned 					pmm_bitmap[PHYS_MAX_PAGE];                   
extern unsigned 					pmm_page_number;                                            
extern uint32_t 					pmm_total; 

int mm_init(uint32_t mem)
{
	pmm_init(mem);
	return 0;
}
intptr_t *mm_alloc(size_t size)
{       
	return (void *)pmm_alloc(size);
}
void mm_free(void *addr)
{
    pmm_free(addr);
}

uint32_t mm_get_total_mem()
{ 
	return pmm_total;
}

uint32_t mm_get_used_mem()
{ 
	return ((pmm_page_number - pmm_get_free_pages()) );
}
uint32_t mm_get_usable_size(void *addr)
{
	for(int i = 0; i < PHYS_MAX_BLOCKS; i++)
	{
		if(pmm_allocated[i].address == addr)
		    return pmm_allocated[i].dim;
	}
	return 0;
}