#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <types.h>

extern "C"
{
  int __cxa_atexit(void (*f)(void *), void *p, void *d);
  void __cxa_finalize(void *d);
};
 
void *__dso_handle;
 
struct object
{
  void (*f)(void*);
  void *p;
  void *d;
} object[32];
unsigned int iObject = 0;
 
int __cxa_atexit(void (*f)(void *), void *p, void *d)
{
  if (iObject >= 32) return -1;
  object[iObject].f = f;
  object[iObject].p = p;
  object[iObject].d = d;
  ++iObject;
  return 0;
}
 extern "C" int __aeabi_atexit(void *object, void (*destructor)(void *), void *dso_handle)
 {
 	return 0;
 } 

/* NOTE: Zerstört momentan unabhängig von d alle Objekte */
void __cxa_finalize(void *d)
{
  unsigned int i = iObject;
  for (; i > 0; --i)
  {
    --iObject;
    object[iObject].f(object[iObject].p);
  }
}
	
typedef void (*constructor)();
typedef void (*destructor)();
 
// Im Linkerskript definiert
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
 
extern "C" void initialiseConstructors();


// Ruft die Konstruktoren für globale/statische Objekte auf
void initialiseConstructors()
{
  for (constructor* i = &start_ctors;i != &end_ctors;++i)
    (*i)();
}


extern "C" void __cxa_pure_virtual()
{
	panic("pure virtual call");
}


void * __stack_chk_guard = 0;
 
extern "C" void __stack_chk_guard_setup()
{
    unsigned char * p;
    p = (unsigned char *) &__stack_chk_guard;
 
    /* If you have the ability to generate random numbers in your kernel then use them,
       otherwise for 32-bit code: */
    *p =  rand();
}
 
extern "C" void  __stack_chk_fail()
{ 
	panic("Stack cheak fail");
}
extern "C" void __aeabi_unwind_cpp_pr0(void)
{
};

extern "C" void __aeabi_unwind_cpp_pr1(void)
{
};

extern "C" void __aeabi_unwind_cpp_pr2(void)
{
};
extern "C" void __cxa_end_cleanup(void)
{

}
extern "C" void __gxx_personality_v0(void)
{

}
extern "C" void __aeabi_memcpy(void *dest, void *src, size_t n)
{
	(void) memcpy(dest, src, n);
}

extern "C" void __aeabi_memset(void *dest, size_t n, int c)
{
	(void) memset(dest, c, n);
}
extern "C" void __div0 (void)
{

}