## Contributing Guidelines

In order to maintain consistency and neatness across files, here are the guidlines when adding to particular source files:

## eZ80 Assembly Sources

* Spaces are evil. Use 1 tab to the opcode, and 1 tab to the operand.

* Comments should be tabbed out to the same location for all comments in the same file.

* Use snake_case for label and variable names.

* When using index registers or offsets from a label, add a space paritition in the arithmetic operation, e.g. `(ix + 9)`, `OP1 + 1`

* Use local labels.

* Comments should be all lowercase, including the first letter.

* Internal routines shall be prefixed with `util_`.

* SMC labels shall be prefixed with `.smc_`, e.g. `.smc_label := $-3`, and always offset backwards.

* Hexadecimal literals shall be lowercase, prefixed with `$`, e.g. `$3f`

## C Sources

* Tabs are evil. Use 4 spaces.

* Use camelCase for function names.

* Comments should always use /* */, never //

* Comments should never be placed in line with code, always above or below.

* Comments should be all lowercase, including the first letter.

