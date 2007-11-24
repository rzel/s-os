#ifndef KERNEL_H
#define	KERNEL_H

int main(struct multiboot *mboot_ptr);

extern "C"
{
	int __cxa_atexit(void (*f)(void *), void *p, void *d);
	void __cxa_finalize(void *d);
};

void construct();
void destruct();

#endif
