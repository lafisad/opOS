# opScript Module Definition Format

## Overview

opScript is a simple, declarative language used to define modules in opOS. This document describes the syntax and structure of module definition files.

## File Structure

An opScript file defines one or more modules and follows this basic structure:

```opScript
begin FILE module_list -
    begin ENTRY module_name -
        TYPE [module_type]
        NAME 'module_display_name'
        DESC 'Module description'
        LANG 'programming_language'
        LOCATION 'path/to/module'
        PERMISSIONS 'permission_levels'
        VERSION 'x.y.z'
    - end ENTRY module_name
- end FILE module_list
```

## Directives

### `begin FILE`

Starts a module list definition.

- **Parameters**:
  - `module_list`: Identifier for the module list
  - `-`: Required terminator

### `begin ENTRY`

Defines a new module entry.

- **Parameters**:
  - `module_name`: Unique identifier for the module
  - `-`: Required terminator

### `TYPE`

Specifies the module type.

- **Values**:
  - `[volatileModule]`: System-critical module loaded at boot
  - `[module]`: Regular module loaded on demand

### `NAME`

Human-readable name for the module.

- **Format**: Single-quoted string

### `DESC`

Brief description of the module's purpose.

- **Format**: Single-quoted string

### `LANG`

Programming language used to implement the module.

- **Common Values**: 'c', 'rust', 'asm'

### `LOCATION`

Filesystem path where the module's source code is located.

- **Format**: Single-quoted path

### `PERMISSIONS`

Access permissions for the module.

- **Format**: Single-quoted string of permission levels
- **Example**: `'0' + '99'` (root access + device read)

### `VERSION`

Module version number following semantic versioning.

- **Format**: Single-quoted string (e.g., '1.0.0')

## Complete Example

```opScript
begin FILE module_list -
    begin ENTRY booter -
        TYPE [volatileModule]
        NAME 'System Booter'
        DESC 'Handles system initialization and module loading'
        LANG 'c'
        LOCATION 'sysmodules/booter'
        PERMISSIONS '0'
        VERSION '1.0.0'
    - end ENTRY booter

    begin ENTRY network -
        TYPE [module]
        NAME 'Network Stack'
        DESC 'Implements TCP/IP networking'
        LANG 'c'
        LOCATION 'modules/network'
        PERMISSIONS '50'
        VERSION '0.5.2'
    - end ENTRY network
- end FILE module_list
```

## Best Practices

1. **Versioning**: Always increment version numbers following semantic versioning
2. **Descriptions**: Provide clear, concise descriptions
3. **Permissions**: Follow the principle of least privilege
4. **Formatting**: Maintain consistent indentation (4 spaces recommended)
5. **Comments**: Use `#` for single-line comments

## Validation

The opScript parser enforces:

- Required fields are present
- Proper nesting of blocks
- Valid syntax for all values
- No duplicate module names

## Error Handling

Common errors include:

- Missing required fields
- Invalid module types
- Permission format errors
- Version number format issues
