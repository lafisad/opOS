[BITS 32]

section .text

global _start
extern kernel_main

; The bootloader defines DATA_SEG for us. It's the selector for our 32-bit data segment.
DATA_SEG equ 0x10

_start:
    ; Set up the segment registers for our 32-bit data segment.
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; The bootloader has already set up the stack.
    ; We can now directly call our C kernel.
        mov esi, msg_entry_point
    call print_string_asm

    ; Set up the segment registers for our 32-bit data segment.
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esi, msg_segments_done
    call print_string_asm

    ; We can now directly call our C kernel.
    mov esi, msg_calling_kernel
    call print_string_asm
    call kernel_main

    ; Halt the CPU if the kernel ever returns
    cli
.hang:
    hlt
    jmp .hang

; --- Assembly Print Function ---
print_string_asm:
    pusha
.loop:
    lodsb
    or al, al
    jz .done
    call io_write_char
    jmp .loop
.done:
    popa
    ret

section .data
msg_entry_point: db "[ASM] Reached 32-bit entry point.", 10, 0
msg_segments_done: db "[ASM] Segment registers initialized.", 10, 0
msg_calling_kernel: db "[ASM] Calling C kernel_main...", 10, 0

; --- Default Interrupt Handler ---
; This handler will be used for all interrupts.
interrupt_handler:
    ; Send End of Interrupt (EOI) signal to the PICs
    mov al, 0x20
    out 0xA0, al ; Slave PIC
    out 0x20, al ; Master PIC
    iretd        ; Return from interrupt

; --- IDT Setup ---
global idt_load
idt_load:
    lidt [idt_descriptor] ; Load the IDT register
    ret

idt_descriptor:
    dw idt_end - idt_start - 1 ; IDT limit
    dd idt_start             ; IDT base

section .bss
idt_start:
    resb 256 * 8 ; Reserve space for 256 IDT entries (8 bytes each)
idt_end:

section .text
global idt_init
idt_init:
    mov edi, idt_start
    mov ecx, 256
    mov edx, 0x08      ; Code segment selector
    mov eax, interrupt_handler

.loop:
    mov [edi], ax      ; Set offset (low)
    mov [edi + 2], dx  ; Set selector
    mov byte [edi + 4], 0
    mov byte [edi + 5], 0x8E ; Type/attributes
    shr eax, 16
    mov [edi + 6], ax  ; Set offset (high)
    mov eax, interrupt_handler ; Restore EAX for next loop

    add edi, 8
    dec ecx
    jnz .loop

    ret

; --- I/O Functions ---
global serial_init
global io_write_char
global io_read_char

COM1_PORT equ 0x3F8

serial_init:
    ; Configure COM1 for 9600 baud, 8N1
    mov dx, COM1_PORT + 1
    mov al, 0x00
    out dx, al   ; Disable all interrupts
    
    mov dx, COM1_PORT + 3
    in al, dx
    or al, 0x80  ; Enable DLAB
    out dx, al
    
    ; Set divisor to 12 for 9600 baud
    mov dx, COM1_PORT + 0
    mov al, 12   ; Divisor low byte
    out dx, al
    
    mov dx, COM1_PORT + 1
    mov al, 0x00 ; Divisor high byte
    out dx, al
    
    ; Set 8N1 mode
    mov dx, COM1_PORT + 3
    mov al, 0x03 ; 8 bits, no parity, one stop bit (8N1)
    out dx, al
    
    ; Enable FIFO and clear them
    mov dx, COM1_PORT + 2
    mov al, 0xC7 ; Enable FIFO, clear them, 14-byte threshold
    out dx, al
    
    ; Enable interrupts on received data
    mov dx, COM1_PORT + 1
    mov al, 0x01 ; Enable received data available interrupt
    out dx, al
    
    ret

section .bss
cursor_pos: resw 1 ; VGA cursor position (offset)

section .text
io_write_char:
    pusha
    mov edi, 0xb8000
    movzx ecx, word [cursor_pos]
    mov bl, al  ; Save the character in BL

    cmp bl, 0x0A ; Newline character
    je .newline

    ; Normal character - write to VGA
    mov ah, 0x07 ; Attribute: light grey on black
    mov al, bl   ; Restore character
    mov [edi + ecx * 2], ax
    inc word [cursor_pos]

    ; --- Write to Serial Port (COM1) ---
    mov dx, COM1_PORT + 5
.serial_wait:
    in al, dx
    test al, 0x20 ; Check if transmit buffer is empty
    jz .serial_wait

    mov dx, COM1_PORT
    mov al, bl    ; Get character from BL
    out dx, al

    jmp .done

.newline:
    mov ax, cx
    mov bl, 80
    div bl
    inc al ; Next line
    mul bl
    mov word [cursor_pos], ax

.done:
    ; TODO: Scrolling if cursor_pos > 2000
    popa
    ret

io_read_char:
    ; No keyboard driver yet, just wait for a keypress interrupt
    ; and return a placeholder. For now, we'll just hang.
.key_loop:
    in al, 0x64 ; Read keyboard controller status port
    test al, 1   ; Output buffer full?
    jz .key_loop ; Loop if not

    in al, 0x60 ; Read scancode
    ; This is a placeholder, no scancode translation.
    ; We'll just return 'X' to show it worked.
    mov al, 'X'
    ret
