.. _git:

Using Git For Revision Control
==============================

What is Git?
------------

Git is a revision control system.
It was designed to be used to keep track of the history of a code project and allow multiple people to work simultaneously on the same project.

What is Git not?
^^^^^^^^^^^^^^^^

A file hosting tool.
Git can only properly track text-based files -- you should not include binaries (8XPs, EXEs, ZIPs, etc.) or the output of a compiler.
It's fine to track images and other manually-generated non-text files, but Git doesn't track their history in the same way.

What is GitHub?
---------------

GitHub is an online service that hosts Git repositories so that multiple people can easily access them.

What is GitHub not?
^^^^^^^^^^^^^^^^^^^

Git - You can use Git without GitHub, and you should probably familiarize yourself with Git before using GitHub.
Nor is GitHub a file hosting service - Most of the benefits of GitHub over another site (say, Mediafire, or Google Drive) come from Git.
If your GitHub repositories are not proper Git repositories, you might as well be using another service!

Downloading Git
---------------

You can download Git `here <https://git-scm.com/downloads>`_.

How does Git work?
------------------

Git keeps track of changes to files using *commits*.
Each commit contains information about what files were changed since the last commit, who made the changes, when the changes were made, and a message to help you remember what changed with that commit.
You can easily restore a previous commit, or just see what the code looked like at that point.
All projects that use Git contain data called a *repository*, which is stored in a hidden metadata folder named *.git*.
To use any Git commands, you must first create a repository.

Using Git and GitHub
--------------------

Creating a Repository
^^^^^^^^^^^^^^^^^^^^^

For CE toolchain projects, navigate to your project's directory (the directory you run *make* from), and execute :code:`git init`.

You can also make a copy of a repository that is already on GitHub using :code:`git clone (URL)`.
This command downloads the repository and its associated files into a new folder.
For example, :code:`git clone https://github.com/commandblockguy/dino-run-ce.git` would create the folder dino-run-ce, and download the source for Dino Run CE into it.
You can then :code:`cd dino-run-ce`, and run :code:`make` without any further setup.
This is what makes Git significantly more convenient than a zip with the source.

The .gitignore file
^^^^^^^^^^^^^^^^^^^

You generally want Git to ignore automatically generated/binary files (8XPs, EXEs, the output of convimg, etc.).
You don't have to store these files as you can regenerate them from the source, and the files are likely to change with every commit.
This makes the repository much larger and commits harder to read, and requires you to manually add them to each commit.
Luckily, Git includes an easy way to do this -- .gitignore files.
To use them, just create a file called *.gitignore* and add a list of files/folders you want to ignore.
I recommend the following .gitignore file, as it should match all non-source files:

    .. indent with spaces
    .. code-block:: bash

        obj/
        bin/
        src/gfx/*.c
        src/gfx/*.h
        src/gfx/*.8xv
        .DS_Store
        convimg.yaml.lst

Now, from Git's perspective, these files basically no longer exist - you won't be asked to add them to commits and it will keep your repository clean.

Making commits
^^^^^^^^^^^^^^

Now that we are ignoring the right files, how do we add the ones we actually care about to the repository?
Before making a commit, you have to add the files that you want to include in the commit.
To get a list of the files that you can add, run :code:`git status` -- The files that you have already added are in green, and the files that have changed but that will not be included in the next commit are in red.
To add the files to the next commit, run :code:`git add (file1) (file2) (file3) (etc)`.
Once you are done adding files, you can create the commit by running :code:`git commit -m "Some message for the commit"`.


Adding a repository to GitHub
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Right now, the repository exists on your local computer and can be used with all Git commands, but it is not backed up to GitHub so that others can access it.
To do that, you must first `create a new repository on GitHub <https://github.com/new>`_.
Leave the "Initialize this repository with a README" box unchecked.
This will make a blank repository on GitHub that we can write our local changes to.
Next, we add the GitHub repository as a "remote" that we can save our local changes to.
To do this, run :code:`git remote add origin https://github.com/<user>/<repo>.git`, substituting with your user and repository names.
The final step is to synchronize the changes in your local repository with the remote GitHub repository by "pushing".
This is done via the command :code:`git push origin master`.
The remote repository will only be updated with your code and commits when you push.

Before pushing, it is good practice to run :code:`git pull --rebase origin master` to prevent conflicts.
You do not have to push after every commit - Git is running on your computer, and you can still use all of its features without pushing your code to GitHub.
You only need to push when you want to share the code on your computer with others.

Avoid using the GitHub web interface as much as possible.
Although it may initially seem more convenient, it makes it much easier to accidentally use Git in a way that it wasn't intended for.
This only applies to your actual code - the web interface is the only way to create a repository, view the issues, create a wiki, and add releases.
Any action besides these should be done in the Git command line.
If you are unsure how to do something, feel free to ask in our IRC channel!

Adding releases to GitHub
^^^^^^^^^^^^^^^^^^^^^^^^^

Since it's poor practice to include binaries in a Git repository, GitHub has another way of hosting them - the Releases tab.
To access the Releases tab, open your repository on the GitHub website and click on the Releases button above the file list.
From there, you create a release by clicking "Draft a new release".
Give it a tag like "v1.0" and a name and a description.
Then, you can add 8XPs or a ZIP file to the file upload area by clicking and dragging or by clicking the upload area and selecting a file.
