/**
 * @file multiboot.h
 * @brief Multiboot header definitions
 * @license MIT
 */

#ifndef _MULTIBOOT_H_
#define _MULTIBOOT_H_

/* How many bytes from the start of the file we search for the header. */
#define MULTIBOOT_SEARCH                        32768
#define MULTIBOOT_HEADER_ALIGN                  8

/* The magic field should contain this. */
#define MULTIBOOT2_HEADER_MAGIC                 0xe85250d6

/* This should be in %eax. */
#define MULTIBOOT2_BOOTLOADER_MAGIC             0x36d76289

/* Alignment of multiboot modules. */
#define MULTIBOOT_MOD_ALIGN                     0x00001000

/* Alignment of the multiboot info structure. */
#define MULTIBOOT_INFO_ALIGN                    0x00000008

/* Flags set in the 'flags' member of the multiboot header. */
#define MULTIBOOT_TAG_ALIGN                  8
#define MULTIBOOT_TAG_TYPE_END               0
#define MULTIBOOT_TAG_TYPE_CMDLINE           1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME  2
#define MULTIBOOT_TAG_TYPE_MODULE            3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     4
#define MULTIBOOT_TAG_TYPE_BOOTDEV           5
#define MULTIBOOT_TAG_TYPE_MMAP              6
#define MULTIBOOT_TAG_TYPE_VBE               7
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER       8
#define MULTIBOOT_TAG_TYPE_APM               10

/* The section header table for ELF. */
#define MULTIBOOT_TAG_TYPE_ELF_SECTIONS      9

/* The module section header table. */
#define MULTIBOOT_TAG_TYPE_APM              10

/* The information passed to the operating system. */
struct multiboot_tag
{
  unsigned int type;
  unsigned int size;
} __attribute__((packed));

/* The module section. */
struct multiboot_tag_module
{
  unsigned int type;
  unsigned int size;
  unsigned int mod_start;
  unsigned int mod_end;
  char cmdline[1];
} __attribute__((packed));

/* The memory map. */
struct multiboot_mmap_entry
{
  unsigned long long addr;
  unsigned long long len;
  unsigned int type;
  unsigned int zero;
} __attribute__((packed));

struct multiboot_tag_mmap
{
  unsigned int type;
  unsigned int size;
  unsigned int entry_size;
  unsigned int entry_version;
  struct multiboot_mmap_entry entries[0];
} __attribute__((packed));

#endif /* _MULTIBOOT_H_ */
