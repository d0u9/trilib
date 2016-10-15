# trilib
My wheels.

GNU Linux Kernel is a gold mine for C developers who want tested, robust and generic functions. Lots of functions in this repo are ported from GNU Linux Kernel, and thus are licensed under GPL 2.0.

Due to the fact that GNU Linux Kernel is compiled with GNU gcc, functions and routines here exploit the attributes of GNU gcc. This means that if you want to use this repo in Windows Visual Studio, necessary modifications is needed.

Best regards.

# Flags for compiling

It is necessary to compile with `-std=gnu99` flag to avoid warnings and errors. As described above, some GNU gcc's extension are used here.

Also, some library uses `pthread`, `-lpthread` flags is needed as well.

---

# License

trilib by d0u9 is licensed under a [GNU General Public License, version 2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html).
