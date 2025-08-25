#include "opScript.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#define SKIP_WHITESPACE(ptr) while (isspace(*ptr)) ptr++

static bool parse_entry(const char **ptr, module_entry_t *entry);
static bool parse_key_value(const char **ptr, char *key, char *value, size_t max_len);
static void trim_string(char *str);

void module_list_init(module_list_t *list) {
    list->entries = NULL;
    list->count = 0;
    list->capacity = 0;
}

void module_list_free(module_list_t *list) {
    if (list->entries) {
        free(list->entries);
        list->entries = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

bool parse_opscript(const char *script, module_list_t *list) {
    if (!script || !list) return false;

    const char *ptr = script;
    bool in_module = false;
    module_entry_t current = {0};
    bool success = true;

    while (*ptr) {
        SKIP_WHITESPACE(ptr);
        if (strncmp(ptr, "begin", 5) == 0) {
            ptr += 5;
            SKIP_WHITESPACE(ptr);
            
            if (strncmp(ptr, "FILE", 4) == 0) {
                ptr += 4;
                // Skip file name for now
                while (*ptr && *ptr != '-') ptr++;
                if (*ptr == '-') ptr++;
            }
            else if (strncmp(ptr, "ENTRY", 5) == 0) {
                ptr += 5;
                SKIP_WHITESPACE(ptr);
                
                // Parse entry type
                const char *type_start = ptr;
                while (*ptr && !isspace(*ptr) && *ptr != '-') ptr++;
                char type[32] = {0};
                strncpy(type, type_start, ptr - type_start);
                trim_string(type);
                
                if (strcmp(type, "module") == 0 || strcmp(type, "booter") == 0) {
                    in_module = true;
                    memset(&current, 0, sizeof(current));
                    strncpy(current.name, type, sizeof(current.name) - 1);
                }
                
                // Skip to end of line
                while (*ptr && *ptr != '\n') ptr++;
            }
        }
        else if (in_module && *ptr == 'T' && strncmp(ptr, "TYPE", 4) == 0) {
            ptr += 4;
            SKIP_WHITESPACE(ptr);
            
            if (*ptr == '[') {
                ptr++;
                const char *type_start = ptr;
                while (*ptr && *ptr != ']') ptr++;
                if (*ptr == ']') {
                    char type_str[32] = {0};
                    strncpy(type_str, type_start, ptr - type_start);
                    current.type = get_module_type(type_str);
                    ptr++;
                }
            }
        }
        else if (in_module && strncmp(ptr, "NAME", 4) == 0) {
            ptr += 4;
            SKIP_WHITESPACE(ptr);
            if (*ptr == '\'') {
                ptr++;
                const char *name_start = ptr;
                while (*ptr && *ptr != '\'') ptr++;
                if (*ptr == '\'') {
                    strncpy(current.name, name_start, 
                           MIN(ptr - name_start, sizeof(current.name) - 1));
                    ptr++;
                }
            }
        }
        else if (in_module && strncmp(ptr, "DESC", 4) == 0) {
            ptr += 4;
            SKIP_WHITESPACE(ptr);
            if (*ptr == '\'') {
                ptr++;
                const char *start = ptr;
                while (*ptr && *ptr != '\'') ptr++;
                if (*ptr == '\'') {
                    strncpy(current.description, start, 
                           MIN(ptr - start, sizeof(current.description) - 1));
                    ptr++;
                }
            }
        }
        else if (in_module && strncmp(ptr, "LANG", 4) == 0) {
            ptr += 4;
            SKIP_WHITESPACE(ptr);
            if (*ptr == '\'') {
                ptr++;
                const char *start = ptr;
                while (*ptr && *ptr != '\'') ptr++;
                if (*ptr == '\'') {
                    strncpy(current.language, start, 
                           MIN(ptr - start, sizeof(current.language) - 1));
                    ptr++;
                }
            }
        }
        else if (in_module && strncmp(ptr, "LOCATION", 8) == 0) {
            ptr += 8;
            SKIP_WHITESPACE(ptr);
            if (*ptr == '\'') {
                ptr++;
                const char *start = ptr;
                while (*ptr && *ptr != '\'') ptr++;
                if (*ptr == '\'') {
                    strncpy(current.location, start, 
                           MIN(ptr - start, sizeof(current.location) - 1));
                    ptr++;
                }
            }
        }
        else if (in_module && strncmp(ptr, "PERMISSIONS", 11) == 0) {
            ptr += 11;
            SKIP_WHITESPACE(ptr);
            if (*ptr == '\'') {
                ptr++;
                const char *start = ptr;
                while (*ptr && *ptr != '\'') ptr++;
                if (*ptr == '\'') {
                    strncpy(current.permissions, start, 
                           MIN(ptr - start, sizeof(current.permissions) - 1));
                    ptr++;
                }
            }
        }
        else if (in_module && strncmp(ptr, "VERSION", 7) == 0) {
            ptr += 7;
            SKIP_WHITESPACE(ptr);
            if (*ptr == '\'') {
                ptr++;
                const char *start = ptr;
                while (*ptr && *ptr != '\'') ptr++;
                if (*ptr == '\'') {
                    strncpy(current.version, start, 
                           MIN(ptr - start, sizeof(current.version) - 1));
                    ptr++;
                }
            }
        }
        else if (strncmp(ptr, "- end ENTRY", 10) == 0) {
            if (in_module) {
                // Add current module to list
                if (list->count >= list->capacity) {
                    size_t new_capacity = list->capacity ? list->capacity * 2 : 4;
                    module_entry_t *new_entries = realloc(list->entries, 
                                                        new_capacity * sizeof(module_entry_t));
                    if (!new_entries) {
                        success = false;
                        break;
                    }
                    list->entries = new_entries;
                    list->capacity = new_capacity;
                }
                list->entries[list->count++] = current;
                in_module = false;
            }
            // Skip to end of line
            while (*ptr && *ptr != '\n') ptr++;
        }
        else {
            // Skip to next line
            while (*ptr && *ptr != '\n') ptr++;
            if (*ptr == '\n') ptr++;
        }
    }

    return success;
}

module_type_t get_module_type(const char *type_str) {
    if (strcmp(type_str, "volatileModule") == 0) {
        return MODULE_TYPE_VOLATILE;
    } else if (strcmp(type_str, "module") == 0) {
        return MODULE_TYPE_NORMAL;
    }
    return MODULE_TYPE_UNKNOWN;
}

static bool parse_key_value(const char **ptr, char *key, char *value, size_t max_len) {
    if (!ptr || !*ptr || !key || !value) return false;
    
    const char *p = *ptr;
    
    // Parse key
    while (*p && isspace(*p)) p++;
    const char *key_start = p;
    while (*p && !isspace(*p) && *p != '=') p++;
    if (p == key_start) return false; // No key found
    
    size_t key_len = p - key_start;
    strncpy(key, key_start, MIN(key_len, max_len - 1));
    key[MIN(key_len, max_len - 1)] = '\0';
    
    // Skip to value
    while (*p && isspace(*p)) p++;
    if (*p != '=') return false;
    p++;
    while (*p && isspace(*p)) p++;
    
    // Parse value (can be quoted or unquoted)
    const char *value_start = p;
    size_t value_len = 0;
    
    if (*p == '\'') {
        p++; // Skip opening quote
        value_start = p;
        while (*p && *p != '\'') p++;
        if (*p != '\'') return false; // Unmatched quote
        value_len = p - value_start;
        p++; // Skip closing quote
    } else {
        // Unquoted value
        while (*p && !isspace(*p)) p++;
        value_len = p - value_start;
    }
    
    strncpy(value, value_start, MIN(value_len, max_len - 1));
    value[MIN(value_len, max_len - 1)] = '\0';
    
    *ptr = p;
    return true;
}

static void trim_string(char *str) {
    if (!str) return;
    
    char *end;
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;
    
    if(*str == 0) return;
    
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    
    // Write new null terminator
    *(end+1) = 0;
}