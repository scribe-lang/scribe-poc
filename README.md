# scribe-poc
Scribe Proof of Concept Implementation

## Summary

This is a proof of concept implementation for the scribe language - a practice for the actual implementation, if you will.

That said, this is a working compiler that uses C as the code generation backend.

## Building

1. Create a `build` directory (I do that within the repository) and `cd` into it.
2. Create buildfiles using the cmake command `cmake .. -DCMAKE_BUILD_TYPE=Release`.
3. Finally, the `scribe` binary can be created and installed via `make -j install`.

## Usage

Assuming the `scribe` binary is in `$PATH`, a test can be run via `scribe test/str.sc`. That will generate a file `test/str.sc.c` which is the C equivalent and can be compiled via a C11 conformant compiler.
