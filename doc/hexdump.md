# hexdump module

## Introduction

Dump memory in hex+ASCII format, good helper for debuging in binary mode.

Usually, we want to check what is the content in a particular region of
memory. Absolutely, GDB is a good tool to do such a job. But the fact is
that you can't always add -g option at the compile time, and it's very
inconvenience to run GDB each time.

## Global Variables

```
const char hex_asc[]
```

Char array to convert integer type of number to hex correspond chars.

```
hex_asc_upper[]
```

Same as hex_asc[] but in upper case.

## API

```
int hex_to_bin(char ch)
```

Convert a hex digit to its real value.

- `ch`: is an ascii char represents hex digit.
- RETURN: if `ch` is not a valid hex char, -1 will be return.


```
int hex2bin(u8 *dst, const char *src, size_t count)
```

Convert an ascii hexadecimal string to its binary representation.

- `dst`: binary result.
- `src`: ascii hexadecimal string.
- `count`: result length.
- RETURN: 0 on success, -1 in case of bad input.


```
char *bin2hex(char *dst, const void *src, size_t count)
```

Convert binary data to an ascii hexadecimal string.

- `dst`: ascii hexadecimal result.
- `src`: binary data.
- `count`: binary data length in bytes.
- RETURN: `dst` string.


```
void hex_dump_to_buffer(const void *buf, size_t len, int rowsize,
                            int groupsize, char *linebuf, size_t linebuflen,
                            bool ascii)
```

Convert a blob of data to "hex ASCII" in memory. hex_dump_to_buffer() works on
one "line" of output at a time, i.e., 16 or 32 bytes of input data converted
to hex + ASCII output.

- `buf`: data blob to dump.
- `len`: number of bytes in `buf`.
- `rowsize`: number of bytes to print per line; MUST be 16 or 32.
- `groupsize`: number of bytes to print at a time, it cant be one of 1, 2, 4, 8,
               represents byte, half word, word and guant, default = 1.
- `linebuf`: where to put the converted data.
- `linebuflen`: total size of `linebuf`, including space for terminating NULL.
- `ascii`: include ASCII after the hex output.


```
void fprint_hex_dump(FILE *fp, const char *level, const char *prefix_str,
                         int prefix_type, int rowsize, int groupsize,
                         const void *buf, size_t len, bool ascii)
```

Print a text hex dump to a file pointer, Given a buffer of u8 data,
fprint_hex_dump() prints a hex + ASCII dump to the kernel log at the
specified kernel log level, with an optional leading prefix.

- `fp`: the FILE* pointer to which hex text dump.
- `level`: kernel log level (e.g. KERN_DEBUG)
- `prefix_str`: string to prefix each line with;
                caller supplies trailing spaces for alignment if desired
- `prefix_type: controls whether prefix of an offset, address, or none
                is printed, avaiable values are: DUMP_PREFIX_OFFSET,
                DUMP_PREFIX_ADDRESS, DUMP_PREFIX_NONE
- `rowsize: number of bytes to print per line; must be 16 or 32
- `groupsize: number of bytes to print at a time (1, 2, 4, 8; default = 1)
- `buf: data blob to dump
- `len: number of bytes in the @buf
- `ascii: include ASCII after the hex output


```
print_hex_dump(level, prefix_str, prefix_type, rowsize,
                   groupsize, buf, len, ascii)
```

Same as fprint_hex_dump() but used stdout.

