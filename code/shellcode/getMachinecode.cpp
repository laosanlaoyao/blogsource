/*
insert your shellcode to the place of TODO
*/

#include <windows.h>
#include <stdio.h>

ULONG get_shellcode_addr() {
    ULONG beginning_addr = 0;

    __asm {
        call    beginning                // will push the address of beginning

beginning:
        pop     eax                      // will pop the address of beginning to eax
        mov     beginning_addr,eax
        jmp     end_of_shellcode
    }

    __asm {
begin_of_shellcode:
        // TODO, insert your ASM shellcode here, it must not contain NOP!
    }

    // TODO, insert your C++ shellcode here

    __asm {
end_of_shellcode:
        nop
    }

    return (beginning_addr + 1 + 3 + 5); // the address of begin_of_shellcode
}

int main() {
    ULONG shellcode_addr = get_shellcode_addr();

    int count = 0;
    unsigned char shellcode[1024];
    while(true) {
        BYTE db = *((BYTE *)(shellcode_addr + count));
        if(db == 0x90) {
            shellcode[count] = '\0';
            break;
        }
        else {
            shellcode[count++] = db;
        }
    }

    printf("%d bytes of shellcode:\n", count);
    for(int i = 0; i < count; i++) {
        if(i % 16 == 0) printf("\"\n\"");
        printf("\\x%02X", shellcode[i]);
    }

    return 0;
}