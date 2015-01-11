#include <stdlib.h>

static void __dtors(void);
static void __ctors(void);

typedef void (*func_ptr) (void);

void __init(void);
void __fini(void);

static func_ptr force_to_data[1] __attribute__ ((__unused__)) = { };

static func_ptr __CTOR_LIST__[2]
  __attribute__ ((__unused__, section(".ctors"), aligned(sizeof(func_ptr))))
  = { (func_ptr) (-1), (func_ptr) (-1) };


static func_ptr __DTOR_LIST__[1]
  __attribute__((section(".dtors"), aligned(sizeof(func_ptr))))
  = { (func_ptr) (-1) };

static void __dtors()
{
	unsigned long i = (unsigned long) __DTOR_LIST__[0];
	void (**p)(void);

	if (i == -1)  {
		for (i = 1; __DTOR_LIST__[i] != NULL; i++)
			;
		i--;
	}
	p = __DTOR_LIST__ + i;
	while (i--)
		(**p--)();
}

static void __ctors()
{
	unsigned long i = (unsigned long) __CTOR_LIST__[0];
	void (**p)(void) = __CTOR_LIST__ + 1;

	if (i == -1) 
	{

		if ((unsigned long) __CTOR_LIST__[1] == -1 )
			p++;

		while (*p)
		{
			(**p++)();
		}
	}
}

void __init()
{
	static int initialized = 0;

	if (!initialized) {
		initialized = 1;
		__ctors();
	}
}

void __fini()
{
	__dtors();
}

