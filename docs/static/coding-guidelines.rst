.. _coding_guidelines:

General Coding Guidelines
=========================

If you are new to the C language and are looking for some pointers to improve your coding style, this page is for you!
These suggestions should help you avoid common pitfalls, and make your code easier to manage.

Style Consistency
-----------------

This is a big one.
When programming, it is important to choose a coding style that you prefer and **stick with it**.
For instance, if you prefer using 4 spaces to indent your code, use that everywhere -- don't mix tabs and spaces!
If your variables are :code:`snake_case` or :code:`camelCase` -- use the same format everywhere.
This goes for function naming too.

Some additional style guidlines:

- Try to keep lines 80 characters or less. This will promote less indentation and better coding design, as well as avoid insanely long variable names. If you have more than 3 levels of indentation, it's probably time to rethink your code.
- Use consistent bracing formats; if your braces all start on a new line, don't mix them. It is especially helpful to always use braces even on single-line conditional statements as it will avoid spurious bugs from poping up.
- Try to keep functions at 100 lines or less. Any more and the function should be broken out, as this will increase readability and make it easier for you 6 months later to understand what you wrote.
- It doesn't really matter *what* your style is as long as it is consistent! People will be more inclined to help and contribute to your code if you keep it neat.

Include File Recommendations
----------------------------

Include files can be one of the most hated aspects of C -- so it is important to use them correctly to prevent losing your mind.

Avoid Global Variables
----------------------

Global variables are **bad**.
These are variables which are defined outside of a function.

Proper Scoping
^^^^^^^^^^^^^^

Using structures
^^^^^^^^^^^^^^^^

Avoid Dynamic Allocation
------------------------

Dynamic allocation (e.g. *malloc*, *calloc*, *realloc*) should be avoided as much as possible.
This is because it is an expensive operation and uses a few kilobytes of space for the function itself.

Using the static keyword
^^^^^^^^^^^^^^^^^^^^^^^^
