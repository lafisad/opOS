# Module Permissions in opOS

## Overview

opOS implements a fine-grained permission system to control module access to system resources. This document explains the permission levels and how to use them effectively.

## Permission Levels

### Root Level (0)

The highest privilege level in the system.

**Capabilities:**

- Full system access
- Can modify any memory location
- Can access all hardware registers
- Can load/unload any module
- Can modify system configuration

**Use Cases:**

- Kernel modules
- System initialization
- Hardware abstraction layer

**Example:**

```opScript
PERMISSIONS '0'
```

### User Level (10)

Default permission level for user modules.

**Capabilities:**

- Basic system access
- Can use system calls
- Limited hardware access
- Can access user-owned resources

**Use Cases:**

- Application modules
- User-space drivers
- System utilities

**Example:**

```opScript
PERMISSIONS '10'
```

### Custom Levels (11-98)

Configurable permission levels for fine-grained access control.

**Capabilities:**

- Custom access rights as defined in system configuration
- Can be combined for complex permission schemes
- System administrator configurable

**Use Cases:**

- Service modules
- Multi-tenant applications
- Security-sensitive operations

**Example:**

```opScript
PERMISSIONS '20' + '30'  # Combines permissions from levels 20 and 30
```

## Hardware Permissions

### HW0

Read-only access to device registers.

**Capabilities:**

- Read-only access to device registers
- No system modification privileges
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Hardware monitoring
- Sensor access

**Example:**

```opScript
PERMISSIONS 'HW0'
```

### HW1

Write access to device registers.

**Capabilities:**

- Write access to device registers
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'HW1'
```

### HW2

Read and write access to device registers.

**Capabilities:**

- Read and write access to device registers
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'HW2'
```

### HW3

Full access to device registers.

**Capabilities:**

- Full access to device registers
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'HW3'
```

### CPU0

Read access to CPU registers.

**Capabilities:**

- Read access to CPU registers
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'CPU0'
```

### CPU1

Write access to CPU registers.

**Capabilities:**

- Write access to CPU registers
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'CPU1'
```

### CPU2

Read and write access to CPU registers.

**Capabilities:**

- Read and write access to CPU registers
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'CPU2'
```

### CPU3

Full access to CPU registers.

**Capabilities:**

- Full access to CPU registers
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'CPU3'
```

### GPU0

Read access to GPU registers.

**Capabilities:**

- Read access to GPU registers
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'GPU0'
```

### GPU1

Write access to GPU registers.

**Capabilities:**

- Write access to GPU registers
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'GPU1'
```

### GPU2

### GPU3

### RAM0
Write access to RAM.

**Capabilities:**

- Write access to RAM
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'RAM0'
```

### RAM1
Read access to RAM.

**Capabilities:**

- Read access to RAM
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'RAM1'
```

### RAM2
Read and write access to RAM.

**Capabilities:**

- Read and write access to RAM
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'RAM2'
```

### RAM3
Full access to RAM.

**Capabilities:**

- Full access to RAM
- Limited to hardware interaction

**Use Cases:**

- Device drivers
- Sensor access

**Example:**

```opScript
PERMISSIONS 'RAM3'
```


## Misc. Permissions

### OP

**Capabilities:**

- Full system access
- Can modify any memory location
- Can access all hardware registers
- Can load/unload any module
- Can modify system configuration

**Use Cases:**

- Kernel modules
- System initialization
- Hardware abstraction layer

**Example:**

```opScript
PERMISSIONS 'OP'
```
