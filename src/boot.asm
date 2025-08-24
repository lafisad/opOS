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

    ; Load kernel (assuming it's the next sector)
    MOV AH, 0x02        ; BIOS read sector
    MOV AL, 6           ; Number of sectors to read
    MOV CH, 0           ; Cylinder 0
    MOV CL, 2           ; Start from sector 2
    MOV DH, 0           ; Head 0
    MOV BX, 0x1000      ; Load to ES:BX (0x1000:0x0000)
    INT 0x13
    JC error

    ; Jump to kernel
    JMP 0x1000:0x0000

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

TIMES 510-($-$$) DB 0
DW 0xAA55
