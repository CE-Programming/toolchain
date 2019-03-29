## Contributing Guidelines

In order to maintain consistency and neatness across files, here are the guidlines when adding to particular source files:

## eZ80 Assembly Sources

* Spaces are evil. Use 1 tab to the opcode, and 1 tab to the operand:

    	ld	iy,(iy + 6)

* Comments should be tabbed out to the same location for all comments in the same file.

* Use fasmg syntax for label and variable names.

* Add a space between any arithmetic operation, e.g. `(ix + 9)`, `OP1 + 1`

* Use local labels.

* Internal routines shall be prefixed with `util.`.

* Hexadecimal literals shall be lowercase, prefixed with `$`, e.g. `$3f`

## C Sources

* Tabs are evil. Use 4 spaces.

* Use camelCase for function names.

* Comments should always use /* */, never //

* Comments should never be placed in line with code, always above or below.


