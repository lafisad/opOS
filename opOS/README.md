# OPOS [opOS]

## opOS - the 'operational Operating System'

opOS is a security-focused, modular operating system designed for maximum control and transparency.

## Core Principles

1. **User Control**: Nothing works without explicit user configuration. Set up every module yourself.
2. **Modularity**: The system is built from independent, replaceable components.
3. **Transparency**: Every operation is visible and auditable.
4. **Minimalism**: Include only what you need, nothing more.

## Current State

### Kernel
- [x] Basic project structure
- [x] Bootloader integration
- [ ] Memory management
- [ ] Process scheduling
- [ ] Device drivers
- [ ] Filesystem support

### System Modules
- [x] Booter module (basic implementation)
- [ ] Memory manager
- [ ] Process manager
- [ ] Device manager
- [ ] Filesystem drivers

### Security Features
- [ ] Module signing
- [ ] Memory protection
- [ ] Process isolation
- [ ] Secure boot

## Building and Running

### Prerequisites
- GCC cross-compiler for x86_64-elf
- NASM
- QEMU for emulation

### Building
```bash
make all
```

### Running in QEMU
```bash
make run
```

### Cleaning build files
```bash
make clean
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Submit a pull request

## License

MIT License - see LICENSE file for details

## Contributors

- [owner - main dev][def]

[def]: https://github.com/lafisad