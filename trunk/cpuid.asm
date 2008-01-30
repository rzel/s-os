[GLOBAL get_cpuid_ebx]
[GLOBAL get_cpuid_edx]
[GLOBAL get_cpuid_ecx]

get_cpuid_ebx:
	mov eax, [esp+4]
	cpuid
	mov eax, ebx
	ret

get_cpuid_edx:
	mov eax, [esp+4]
	cpuid
	mov eax, edx
	ret

get_cpuid_ecx:
	mov eax, [esp+4]
	cpuid
	mov eax, ecx
	ret
