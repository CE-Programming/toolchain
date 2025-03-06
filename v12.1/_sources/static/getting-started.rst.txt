.. _getting_started:

Getting Started
===============

Installing the CE Toolchain
---------------------------

Download the latest stable toolchain release below:

..

  * Windows: `CEdev-Windows.zip <https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-Windows.zip>`__
  * Linux:  `CEdev-Linux.tar.gz <https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-Linux.tar.gz>`__
  * macOS *arm*: `CEdev-macOS-arm.dmg <https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-macOS-arm.dmg>`__
  * macOS *intel*: `CEdev-macOS-intel.dmg <https://github.com/CE-Programming/toolchain/releases/latest/download/CEdev-macOS-intel.dmg>`__

..

If you would rather try the "nightly" build (which includes the latest features and bugfixes before an official release) you can find it `here <https://github.com/CE-Programming/toolchain/releases/tag/nightly>`__.

**On Windows**

    * Extract the zip to a folder **without any spaces** in the full path, e.g. :code:`C:\CEdev`.

    * Double click :code:`cedev.bat` inside the extracted *CEdev* folder to launch the toolchain environment.
      You may have to allow the script to be run depending on the user account control.

    * If you want to avoid using the :code:`cedev.bat` script, you can extend the PATH environment variable to point to the :code:`CEdev/bin` directory.
      `Here is a guide <https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/>`_.

**On Linux or Mac**

    * Extract the archive to a path **without any spaces**, e.g. :code:`/home/user/CEdev`.

    * Extend the PATH environment variable to point to :code:`CEdev/bin` by modifying either the :code:`~/.zshrc` or :code:`~/.bashrc` in your home directory.
      An example command that can be added would look similar to the following:

        .. indent with spaces
        .. code-block:: bash

            export PATH=/<insert path to the CEdev folder here>/CEdev/bin:$PATH

.. caution::

    Only update your calculator's OS to `5.4.0 <https://tiplanet.org/modules/archives/download.php?id=2236014>`_ or below. OS versions 5.5.0 and up remove the ability to natively execute C and assembly programs which results in an **Invalid Error** when attempting to run programs. On these later OSes use `arTIfiCE <https://yvantt.github.io/arTIfiCE/>`_ to restore functionality.

.. tip::

    The toolchain update process is the exact same as installation - the only extra step is to delete the current ``CEdev`` folder if it exists beforehand.

Example Programs
----------------

The toolchain includes multiple example projects inside the :code:`examples` folder.
Use these examples to learn how to write C/C++ code for the calculator.
The examples are broken out into:

standalone_examples
  These examples can be compiled directly using the manner described in `Building Programs`_.
  They do not require any external dependencies.

library_examples
  These examples use the CE Libraries, a collection of functions and macros used to make things such as graphics, filesystem access, and keypad input faster and easier.
  They are used by many existing projects - the libraries themseleves are downloadable `here <https://github.com/CE-Programming/libraries/releases/latest>`_.
  The examples are further subdivided into the specific library they are demonstrating.
  For documentation on the available library functions, see the :ref:`CE Libraries <libraries>` page.

Building Programs
-----------------

This section describes the standard flow for building CE toolchain projects, starting with the classing "Hello World" example.
Open a build session by double-clicking :code:`cedev.bat` on Windows or launching a terminal session on Linux/macOS.
Navigate to the *examples* folder using the :code:`cd examples` command.
This folder contains example projects that you can build and modify to learn how to write different programs.
Navigate to the *hello_world* example project using the command :code:`cd hello_world`.

Type :code:`make` and press enter.
This command invokes the compiler, assembler, and linker creating the program :code:`bin/DEMO.8xp`.
Use the `CEmu <https://ce-programming.github.io/CEmu>`_ emulator to run the built program, or transfer it to a real calculator using `TI Connect CE <https://education.ti.com/en/us/products/computer_software/connectivity-software/ti-connect-ce-software/tabs/overview>`_.

.. figure:: images/hello_world.png
   :align: center
   :alt: Building the Hello World example

   Building the Hello World example

.. note::

    If on Windows you encounter errors such as :code:`Missing vcruntime140.dll`, install the latest Microsoft Visual C++ Redistributable package.
    The download can be found `at this link <https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0>`_, depending on the architecture you will need to install one of either *vc_redist.x86.exe* or *vc_redist.x64.exe*.

.. tip::

    Antivirus software (e.g. Windows Defender) may flag binaries in the :code:`CEdev/bin` directory as false positives, and either quarantine/remove the files or prevent them from running.
    This may result in build errors such as being unable find/execute `fasmg`.
    Please whitelist or disable scanning in :code:`CEdev/bin` to prevent these false positives from occurring.

Project Structure
-----------------

Every CE Toolchain project has the following folder structure.
It is highly recommended to keep the same structure to ensure that your project can build with future toolchain versions.

src
  This is the directory where all source files can be placed.
  Sources are built automatically if they end in a ``.c``/``.cpp`` extension, and can be edited with any text editor or IDE.
  Subdirectories are allowed as long as they do not contain spaces.

obj
  Compiled C/C++ files are placed here, and contain intermediate assembly output.

bin
  This is where the final linked calculator program will be placed, ending with a ``.8xp`` extension.

makefile
  A text file used by :code:`make` to build the program.
  There are options for setting the program name, description, and :ref:`more <makefile_options>`.

icon.png
  This is a 16x16 icon that is displayed in shells such as `Cesium <https://github.com/mateoconlechuga/cesium/releases/latest>`_.

readme.md
  A text file that describes the program's operation.

autotest.json
  This file can be loaded into `CEmu's Autotester <https://ce-programming.github.io/CEmu>`_ to test and validate the program.
  This feature may be useful for creating testable code coverage.
