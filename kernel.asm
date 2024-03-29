;
; kernel.asm -- Kernel start location. Also defines multiboot header.
; Based on Bran's kernel development tutorial file start.asm, and James Molloy's tutorials
;

MBOOT_PAGE_ALIGN    equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value

; NOTE: We do not use MBOOT_AOUT_KLUDGE. It means that GRUB does not
; pass us a symbol table.

MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]		; We're in Protected Mode

[GLOBAL mboot]                  ; Make 'mboot' accessible from C.
[EXTERN code]                   ; Start of the '.text' section.
[EXTERN bss]                    ; Start of the .bss section.
[EXTERN end]                    ; End of the last loadable section.


mboot:
  dd  MBOOT_HEADER_MAGIC        ; GRUB will search for this value on each
                                ; 4-byte boundary in your kernel file
  dd  MBOOT_HEADER_FLAGS        ; How GRUB should load your file / settings
  dd  MBOOT_CHECKSUM            ; To ensure that the above values are correct
   
  dd  mboot                     ; Location of this descriptor
  dd  code                      ; Start of kernel '.text' (code) section.
  dd  bss                       ; End of kernel '.data' section.
  dd  end                       ; End of kernel.
  dd  start                     ; Kernel entry point (initial EIP).


[global start]

[global halt]
[global disable]
[global enable]
[global shutdown]

[extern _main]			; The main function, as declared in kernel.cpp

start:
push ebx				; Load multiboot header location

cli					; Disable interupts

call _main				; Call our main function

call halt				; Halt the processor

halt:
	jmp $
	
enable:
	sti
	ret
	
disable:
	cli
	ret
	
shutdown:
	xor eax,eax
	mov cr0,eax

	mov ax,5301h
	xor bx,bx
	int 15h
	mov ax,530Eh
	mov cx,0102h
	int 15h
	mov ax,5307h
	mov bl,0001h
	mov cx,0003h
	int 15h
	;***system will shutdown, or else there was a error***
Error:

