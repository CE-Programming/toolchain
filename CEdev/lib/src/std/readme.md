#### *shared*

Implementations to use regardless of linking method. Should include:

 * OS linked implementations that must be used because no static implementation
   exists.
 * Statically linked implementations that must be used because they provide
   improved/corrected behavior or substantially improved performance relative to
   the OS linked implementation.
   
#### *linked*

Implementations to use when linking against the OS. Should just be equates for
OS or boot jump table entries.

#### *static*

Implementations to use when linking statically. Should only be different from
the OS linked implementation by providing a performance improvement.

If the performance improvement combined with the frequency of this function
being called could plausibly make a meaningful overall performance improvement
in a program, or if this implementation provides improved/corrected behavior,
then this implementation should be moved to *shared*, and the corresponding
*linked* version deleted.

#### Sanity check

*linked* and *static* should include implementations for the same subset of
standard library functions. *shared* should include implementations for all
remaining standard library functions.
