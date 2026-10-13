#include <stddef.h>

typedef struct DestructorChain
{
    struct DestructorChain *next;
    void *destructor;
    void *object;
} DestructorChain;


DestructorChain *__global_destructor_chain;

extern void *__register_global_object(void *object, void *destructor, DestructorChain *chain)
{
    chain->next = __global_destructor_chain;
    chain->destructor = destructor;
    chain->object = object;
    __global_destructor_chain = chain;
    return object;
}

void __destroy_global_chain(void)
{
    DestructorChain *dc;

    while ((dc = __global_destructor_chain) != NULL)
    {
        __global_destructor_chain = dc->next;
        ((void (*)())dc->destructor)(dc->object, -1);
    }
}

// With MWCC we use their special section directive
// to trigger the compiler's handling of global_destructor_chain.
// For Clang, we emulate it's behavior by placing two references manually.
#ifdef __MWERKS__
#pragma section ".dtors$10"
__declspec(section ".dtors$10") __declspec(weak) 
    extern void * const __destroy_global_chain_reference = __destroy_global_chain;
#else
__attribute__((section(".dtors"))) __attribute__((weak))
    void * const __destroy_global_chain_reference = __destroy_global_chain;

__attribute__((section(".dtors"))) __attribute__((weak)) 
    void * const __destroy_global_chain_reference2 = __destroy_global_chain;
#endif
