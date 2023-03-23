My second project in university: A terminal Pokemon tile-matching game

Libraries used:

- cstdint	*(access to uint8_t, uint16_t,...)*
- cstdio	*(access to printf)*
- cstdlib	*(access to system)*
- cstring	*(access to memcpy, memset)*

Additionally, based on the operating system which this repository is built on, some more libraries are included to detect keypress. Specifically:

- Linux: `termios.h`, `sys/ioctl.h`, `sys/select.h`
- Windows: `conio.h`
