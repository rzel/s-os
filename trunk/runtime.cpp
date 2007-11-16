// Sos Version 0.1
// Very Basic C++ Runtime support - Based on code from OSdev.org Wiki
// This is not operational yet - I will work on global/static objects and
// the new and delete operators once I have heap management working.
// This file is not linked to the kernel binary.

unsigned char uint_t;

extern "C" void __cxa_pure_virtual()
{
    // print error message
}

extern "C"
        {
        int __cxa_atexit(void (*f)(void *), void *p, void *d);
        void __cxa_finalize(void *d);
        };

void *__dso_handle; /*only the address of this symbol is taken by gcc*/

struct object
{
        void (*f)(void*);
        void *p;
        void *d;
} object[32] = {0};

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

/* This currently destroys all objects */
void __cxa_finalize(void *d)
{
        unsigned int i = iObject;
        for (; i > 0; --i)
        {
                --iObject;
                object[iObject].f(object[iObject].p);
        }
}


/*//overload the operator "new"
void* operator new (uint_t size)
{
	//return kmalloc(size);
	// FIXME: This needs to be implemented
}

//overload the operator "new[]"
void* operator new[] (uint_t size)
{
	// return kmalloc(size);
	// FIXME: This needs to be implemented
}

//overload the operator "delete"
void operator delete (void * p)
{
	//kfree(p);
	// FIXME: This needs to be implemented
}

//overload the operator "delete[]"
void operator delete[] (void * p)
{
	// kfree(p);
	 // FIXME: This needs to be implemented
}*/
