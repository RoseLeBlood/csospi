typedef void (*func_ptr) (void);

#define NULL 0

static func_ptr __CTOR_END__[1] __attribute__ ((section (".ctors"))) = {
        (func_ptr)(NULL)
};
static func_ptr __DTOR_END__[1] __attribute__ ((section (".dtors"))) = {
        (func_ptr)(NULL)
};