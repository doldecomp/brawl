extern "C" {

typedef struct ExtabIndexInfo {
    unsigned long size;
    struct ExtabIndexInfo* extab;
    unsigned long extabend;
} ExtabIndexInfo;

extern const ExtabIndexInfo _eti_init_info[];

int __register_fragment(const ExtabIndexInfo* info, char* toc);
void __unregister_fragment(int fragmentID);
void __destroy_global_chain(void);

// The unit owns 8 bytes of .sdata but only the first word is ever read, and a
// lone int leaves the section 4 bytes short of the split. Pairing the id with
// its trailing word reproduces the section exactly.
static struct {
    int id;
    int pad;
} fragment = { -2, 0 };

void __init_cpp_exceptions(void)
{
    // __register_fragment takes the TOC in r2, which has no C spelling.
    register char* toc;
    if (fragment.id == -2) {
        asm { mr toc, r2 }
        fragment.id = __register_fragment(_eti_init_info, toc);
    }
}

void __fini_cpp_exceptions(void)
{
    if (fragment.id != -2) {
        __unregister_fragment(fragment.id);
        fragment.id = -2;
    }
}

#pragma section ".ctors$10"
__declspec(section ".ctors$10")
    extern void* const __init_cpp_exceptions_reference = (void*) __init_cpp_exceptions;

#pragma section ".dtors$10"
__declspec(section ".dtors$10") __declspec(weak)
    extern void* const __destroy_global_chain_reference = (void*) __destroy_global_chain;

#pragma section ".dtors$15"
__declspec(section ".dtors$15")
    extern void* const __fini_cpp_exceptions_reference = (void*) __fini_cpp_exceptions;

}
