#include "../../include/module_system.h"
#include <string.h>
#include <stddef.h>
// Removed problematic cpuid.h include

// Hardware scanner functions
int hwscan_init(void);
void hwscan_run_full_scan(void);
void hwscan_print_paranoid_status(void);

// Module definition
module_t hwscan_module = {
    .name = "hwscanner",
    .init = hwscan_init,
    .is_vital = 1
};

static struct {
    char has_intel_me;
    char has_amd_psp;
    unsigned int ram_kb;
    char cpu_vendor[13];
} hw_info;

int hwscan_init(void) {
    println("scanning hw [this is NOT a backdoor check]");
    
    // Get CPU info
        unsigned int eax, ebx, ecx, edx;
    #if defined(_MSC_VER)
        int cpu_info[4];
        __cpuid(cpu_info, 0);
        ebx = cpu_info[1];
        edx = cpu_info[3];
        ecx = cpu_info[2];
    #elif defined(__GNUC__) || defined(__clang__)
        eax = 0;
        __asm__ __volatile__ (
            "cpuid"
            : "=b"(ebx), "=c"(ecx), "=d"(edx)
            : "a"(eax)
        );
    #else
        ebx = ecx = edx = 0; // Fallback for unsupported compilers
    #endif
        *((unsigned int*)(hw_info.cpu_vendor + 0)) = ebx;
        *((unsigned int*)(hw_info.cpu_vendor + 4)) = edx;
        *((unsigned int*)(hw_info.cpu_vendor + 8)) = ecx;
        hw_info.cpu_vendor[12] = '\0';
    
    hw_info.has_intel_me = (strstr(hw_info.cpu_vendor, "Intel") != NULL);
    hw_info.has_amd_psp = (strstr(hw_info.cpu_vendor, "AMD") != NULL);
    
    // Get RAM (placeholder value, replace with platform-specific code if needed)
    hw_info.ram_kb = 0; // TODO: Implement RAM detection for your platform
    
    hwscan_print_paranoid_status();
    return 0;
}

void hwscan_run_full_scan(void) {
    println("\nscanning again");
    print("CPU: "); println(hw_info.cpu_vendor);
    
    if (hw_info.has_intel_me || hw_info.has_amd_psp) {
        println("yeah. uh. i mean honestly since this is post-2008\n you definetely have backdoors built into ur cpu, but everyone has so xD");
        println("we are all being watched. this is just for the fuckass tiktok opsec kiddies who think they can hide from the government lmao");
    }
    
    print("RAM: ");
    print_num(hw_info.ram_kb);
    println("mmmph.... yummy ram :3");
}

void hwscan_print_paranoid_status(void) {
    println("\nsec status:");
    print("CPU Vendor: ");
    println(hw_info.cpu_vendor);

    print("Intel ME present: ");
    println(hw_info.has_intel_me ? "yes" : "no");

    print("AMD PSP present: ");
    println(hw_info.has_amd_psp ? "yes" : "no");

    print("RAM (KB): ");
    print_num(hw_info.ram_kb);
    println("");
}
