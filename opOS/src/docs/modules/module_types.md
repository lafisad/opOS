# Module Types in opOS

## Overview

opOS supports different types of modules that can be loaded at different stages of the system's lifecycle. This document describes the available module types and their characteristics.

## Module Types

### 1. Volatile Modules (`volatileModule`)

Volatile modules are essential system components that are loaded during the early boot process and remain active until system shutdown.

**Characteristics:**
- Loaded during system initialization
- Cannot be unloaded during runtime
- Have higher privileges than normal modules
- Critical for system operation

**Examples:**
- `booter`: Handles the initial boot process
- `terminal`: Provides system console functionality
- `memory`: Manages system memory

### 2. Normal Modules (`module`)

Normal modules are loaded on-demand during runtime and can be dynamically loaded/unloaded.

**Characteristics:**
- Loaded when requested by the system or other modules
- Can be unloaded when not in use
- Have restricted permissions by default
- Can be developed by third-party developers

**Examples:**
- `network`: Network stack implementation
- `filesystem`: File system drivers
- `graphics`: Display and input handling

## Module Lifecycle

### Volatile Modules
1. Loaded by the bootloader
2. Initialized during system startup
3. Active for the entire system uptime
4. Shut down during system power-off

### Normal Modules
1. Loaded on demand
2. Initialized when first used
3. Can be unloaded when not in use
4. Proper cleanup on unload

## Best Practices

1. **Minimal Dependencies**: Keep module dependencies to a minimum
2. **Resource Management**: Always clean up resources when unloading
3. **Error Handling**: Implement robust error handling
4. **Documentation**: Document module interfaces and requirements
