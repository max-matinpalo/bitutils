# bitutils

A single-header C library for type-safe bitwise manipulation, counting, scanning, and debugging.

## Requirements

* A compiler supporting C11 `_Generic` and GCC/Clang built-in functions.
* `<stdint.h>`

## API Reference

### Basic Operations
* `SET_BIT(x, n)`: Sets the *n*-th bit in *x*.
* `CLEAR_BIT(x, n)`: Clears the *n*-th bit in *x*.
* `TOGGLE_BIT(x, n)`: Flips the *n*-th bit in *x*.
* `TEST_BIT(x, n)`: Returns non-zero if the *n*-th bit in *x* is set, and zero otherwise.

### Type-Safe Counting & Scanning
These macros use C11 `_Generic` to match against `unsigned int`, `unsigned long`, and `unsigned long long`. They utilize GNU statement expressions to prevent double evaluation of arguments.

* `CLZ(x)`: Count Leading Zeros. Returns the number of leading 0-bits. Returns the bit-width of the type if *x* is exactly 0.
* `CTZ(x)`: Count Trailing Zeros. Returns the number of trailing 0-bits. Returns the bit-width of the type if *x* is exactly 0.
* `POPCNT(x)`: Population Count. Returns the total number of set bits.
* `BSR(x)`: Bit Scan Reverse. Returns the zero-based index of the highest (most significant) set bit. Returns -1 if *x* is exactly 0.

### 64-bit Destructive Scanning
* `POPLSB64(p)`: Takes a pointer to a `uint64_t`. Identifies and clears the least significant set bit in memory, returning its index. Returns -1 if the value is already 0.
* `POPMSB64(p)`: Takes a pointer to a `uint64_t`. Identifies and clears the most significant set bit in memory, returning its index. Returns -1 if the value is already 0.

### Debugging
* `LOGBITS(x)`: Prints the binary representation of *x* to standard output. Inserts a space every 8 bits for readability.

## Usage

`bitutils.h` does not contain include guards, as it is designed to be included once via a shared, auto-included project header.