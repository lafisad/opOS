; opOS Boot Sector
[BITS 16]
[ORG 0x7C00]

    ; Set up segments and stack
    CLI
    MOV AX, 0
    MOV DS, AX
    MOV ES, AX
    MOV SS, AX
    MOV SP, 0x7C00
    STI

    ; Set video mode (80x25 text mode)
    MOV AH, 0x00
    MOV AL, 0x03
    INT 0x10

    ; Print welcome message
    MOV SI, welcome_msg
    CALL print_string

    ; Enable A20 line
    MOV SI, msg_a20_start
    CALL print_string
    CALL enable_a20
    MOV SI, msg_a20_done
    CALL print_string

    ; Load kernel from disk to 0x10000
    MOV SI, msg_load_start
    CALL print_string
    MOV AH, 0x02        ; BIOS read sector function
    MOV AL, 10          ; Read 10 sectors
    MOV CH, 0           ; Cylinder 0
    MOV CL, 2           ; Start at sector 2
    MOV DH, 0           ; Head 0
    MOV BX, 0x0000      ; ES:BX = 0x1000:0x0000 = 0x10000
    MOV AX, 0x1000
    MOV ES, AX
    INT 0x13
    JC error
    MOV SI, msg_load_done
    CALL print_string

    ; Jump to kernel entry point
    MOV SI, msg_jumping
    CALL print_string

    ; --- Enter Protected Mode ---
    MOV SI, msg_gdt
    CALL print_string
    CLI          ; Disable interrupts
    LGDT [gdt_descriptor] ; Load GDT
    MOV SI, msg_a20_done ; Re-use 'OK' message
    CALL print_string
    MOV SI, msg_pmode
    CALL print_string
    MOV EAX, CR0
    OR EAX, 0x1  ; Set bit 0 of CR0 to enable protected mode
    MOV CR0, EAX
    MOV SI, msg_a20_done ; Re-use 'OK' message
    CALL print_string

    ; Far jump to flush the CPU pipeline and load CS with our 32-bit code segment
    JMP CODE_SEG:0x10000

; GDT and its descriptor
gdt_start:
    ; Null descriptor
    dd 0
    dd 0

; GDT code segment descriptor (base=0, limit=4GB, 32-bit, ring 0)
CODE_SEG equ $ - gdt_start
    dw 0xFFFF    ; Limit (low)
    dw 0         ; Base (low)
    db 0         ; Base (mid)
    db 0x9A      ; Access byte (present, ring 0, code, executable, readable)
    db 0xCF      ; Granularity (4KB pages, 32-bit) and limit (high)
    db 0         ; Base (high)

; GDT data segment descriptor (base=0, limit=4GB, 32-bit, ring 0)
DATA_SEG equ $ - gdt_start
    dw 0xFFFF    ; Limit (low)
    dw 0         ; Base (low)
    db 0         ; Base (mid)
    db 0x92      ; Access byte (present, ring 0, data, writable)
    db 0xCF      ; Granularity (4KB pages, 32-bit) and limit (high)
    db 0         ; Base (high)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; GDT limit
    dd gdt_start             ; GDT base address

enable_a20:
    CLI
    CALL a20_wait_input
    MOV AL, 0xAD
    OUT 0x64, AL ; Disable keyboard

    CALL a20_wait_input
    MOV AL, 0xD0
    OUT 0x64, AL ; Read from controller output port

    CALL a20_wait_output
    IN AL, 0x60
    PUSH AX

    CALL a20_wait_input
    MOV AL, 0xD1
    OUT 0x64, AL ; Write to controller output port

    CALL a20_wait_input
    POP AX
    OR AL, 2
    OUT 0x60, AL ; Write modified byte

    CALL a20_wait_input
    MOV AL, 0xAE
    OUT 0x64, AL ; Enable keyboard
    STI
    RET

a20_wait_input:
    IN AL, 0x64
    TEST AL, 2
    JNZ a20_wait_input
    RET

a20_wait_output:
    IN AL, 0x64
    TEST AL, 1
    JZ a20_wait_output
    RET

error:
    MOV SI, error_msg
    CALL print_string
    JMP $

print_string:
    PUSH AX
.loop:
    LODSB               ; Load next character
    OR AL, AL           ; Check if zero
    JZ .done
    MOV AH, 0x0E        ; BIOS teletype
    INT 0x10
    JMP .loop
.done:
    POP AX
    RET

welcome_msg db 'opOS loading...', 13, 10, 0
error_msg db 'Boot error!', 13, 10, 0
msg_a20_start: db 'Enabling A20... ', 0
msg_a20_done: db 'OK', 13, 10, 0
msg_load_start: db 'Loading kernel... ', 0
msg_load_done: db 'OK', 13, 10, 0
msg_jumping: db 'Jumping to kernel...', 13, 10, 0
msg_gdt: db 'Loading GDT... ', 0
msg_pmode: db 'Enabling Protected Mode... ', 0

TIMES 510-($-$$) DB 0
DW 0xAA55
