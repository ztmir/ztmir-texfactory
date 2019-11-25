ZTMiR-TeXFactory
================

.. |travis| image:: https://travis-ci.org/ztmir/ztmir-texfactory.svg?branch=master
   :target: https://travis-ci.org/ztmir/ztmir-texfactory
   :alt: Travis CI

.. |appveyor| image:: https://ci.appveyor.com/api/projects/status/0is3qa6oua0px8p2/branch/master?svg=true
   :target: https://ci.appveyor.com/project/ptomulik/ztmir-texfactory-8g067/branch/master
   :alt: Appveyor CI

+---------------+--------------+
|   Travis-CI   |   Appveyor   |
+===============+==============+
|  |travis|     |  |appveyor|  |
+---------------+--------------+

Repository of TeX documents developed in ztmir_

.. contents:: Table of Contents
    :depth: 3

PREREQUISITES
-------------

The following software packages are required (or helpful) to work with the
project.

INSTALLABLE PACKAGES
^^^^^^^^^^^^^^^^^^^^

The following software is usually available in form of installable packages and
is present in software repositories for easy/quick installation:

- `git`_ (optional) if you want to contribute to this repository,
- `python`_ version 3 - as required by `scons`_
- `scons`_ to drive compilation of TeX projects,
- `texlive`_ to compile TeX sources,
- `bibtool`_ (optional) to perform automated processing of **BibTeX** databases,
- `bibclean`_ (optional) to sanity check **BibTeX** databases,
- `jabref`_ to manage **BibTeX** databases,
- `gnuplot`_ to generate plots from numerical data,
- `tar`_ to generate tarballs with documents sources,
- `inkscape`_ as some documents use it to convert ``*.svg`` to other formats.

INITIALIZING PYTHON VIRTUALENV
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We recommend using python's virtualenv to work with the project. To initialize
virtualenv, type in your project's top directory::

  python3 -m venv .venv

or::

  python -m virtualenv .venv

if your "python" command is actually python 3.x interpreter.

ACTIVATING PYHON VIRTUALENV
^^^^^^^^^^^^^^^^^^^^^^^^^^^

The virtualenv should be activated, by executing::

  . .venv/bin/activate

to deactivate currently active virtualenv, use the following command::

  deactivate

INSTALLING BASIC DEPENDENCIES
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Scons and its modules can be easily installed into local virtualenv as follows
(the commands should be ran in an active virtualenv)::

  pip install -r requirements.txt

Few small modules are required locally, that are not available in the form of
installable. They may be easily downloaded with ``bin/downloads.py`` python
script::

    python bin/downloads.py

The script downloads files to local project tree, it doesn't clutter any
folders outside of this project's tree.

The downloaded files may be further deleted with::

    python bin/downloads.py --clean

By default the script downloads most recent versions of these packages directly
from source repositories (git/hg).

GENERATING DOCUMENTATION
------------------------

Texfactory framework has an API documentation and user manual. The documentation
may be generated as follows (see also `PREREQUISITES`_).

API DOCUMENTATION
^^^^^^^^^^^^^^^^^

To generate API documentation, type::

    scons api-doc

The generated API documentation will be written to ``build/doc/api/``.

USER MANUAL
^^^^^^^^^^^

To generate user manual, type::

    scons user-doc

The generated documentation will be written to ``build/doc/user/``.

HOWTO
-----

MANAGE BIBLIOGRAPHIC DATABASE
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Use jabref_ for that. Prefer single database. Use keywords to categorize
bibliographic positions.

BUILD ALL DOCUMENTS
^^^^^^^^^^^^^^^^^^^

This is done with single command::

    ptomulik@tea:$ scons

Once you have multiple projects it may take a long time. On multi-processor
machine you may run parallel build with::

    ptomulik@tea:$ scons -jN

where ``N`` is number of jobs ran in parallel.

To clean all produced files, invoke::

    ptomulik@tea:$ scons -c

BUILD SINGLE DOCUMENT
^^^^^^^^^^^^^^^^^^^^^

You have several choices. Let's say, you have to compile paper named
``paper-96`` which has sources under ``src/latex/papers/paper-96`` and its
build directory is ``build/latex/papers/paper-96``.

#. Build, when you're within source or build directory (i.e. your cwd is ``src/latex/papers/paper-96`` or  ``build/latex/papers/paper-96``)::

    ptomulik@tea:$ scons -u # Build everything
    ptomulik@tea:$ scons -u -c # Clean created files
    ptomulik@tea:$ scons -u paper-96-dvi # Create dvi
    ptomulik@tea:$ scons -u paper-96-pdf # Create dvi+pdf
    ptomulik@tea:$ scons -u paper-96-tgz # Create tarball

#. Build from top-level directory::

    ptomulik@tea:$ scons paper-96 # Build everything for the paper
    ptomulik@tea:$ scons -c paper-96 # Clean
    ptomulik@tea:$ scons paper-96-dvi # Create dvi
    ptomulik@tea:$ scons paper-96-pdf # Create dvi+pdf
    ptomulik@tea:$ scons paper-96-tgz # Create tarball

CREATE NEW PAPER PROJECT
^^^^^^^^^^^^^^^^^^^^^^^^

To generate new paper project from template, type::

    bin/newpaper <name>

where name is a symbolic name of the paper (i.e. ``paper-96`` from previous
examples). To see available options, type ``bin/newpaper -h``. Paper templates
are stored under ``template/latex/papers``. You may create your own templates
there, or in another directory (see the ``-i`` flag to ``bin/newpaper``). To
select particular template, use the ``-t`` flag.

EXTRACT BIBTEX ENTRIES FOR YOUR PAPER
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You may use jabref_'s function ``"Tools | New subdatabase based on aux file"`` or bibtool_::

    ptomulik@tea:$ bibtool -x build/latex/papers/paper/paper.aux \
                   -i path/to/common/database.bib \
                   -o src/latex/papers/paper/paper.bib

CREATE PAPER TEX DISTRIBUTION FOR PUBLISHER
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For sample paper called ``paper-96`` this is done with::

    ptomulik@tea:$ scons paper-96-tgz

This creates tarball file
``build/latex/papers/paper-96/paper-96[-<version>].tar.gz``. The ``version``
part of the name may be absent, if version in not specified in SConscript file.

DIRECTORIES
-----------

======================  =======================================================
Directory               Description
======================  =======================================================
``bin/``                several tools and scripts for writers/developers,
----------------------  -------------------------------------------------------
``build/``              where the writings are compiled, the tree structure
                        resembles that of ``src/``,
----------------------  -------------------------------------------------------
``share/``              files shared between local **TeX** projects, for
                        example custom **TeX** styles or **BibTeX** databases,
----------------------  -------------------------------------------------------
``site_scons/``         local extensions for scons_,
----------------------  -------------------------------------------------------
``src/``                main source tree with source files to be compiled,
----------------------  -------------------------------------------------------
``template/``           templates for certain types of source files,
----------------------  -------------------------------------------------------
``test/``               end-to-end tests
======================  =======================================================

LICENSE
=======

**NOTE:** Sources of ``TeX`` sub-projects found under the ``src/`` directory
and it subdirectories may be subject to their own licenses. For those parts
which are not covered by the individual licenses, the following Default License
below applies.

Default License
---------------

Copyright (c) 2015 ZTMiR

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE

.. _ztmir: http://ztmir.meil.pw.edu.pl/
.. _git: https://git-scm.com/
.. _python: https://www.python.org/
.. _scons: http://scons.org
.. _texlive: http://texlive.org
.. _bibtool: http://www.gerd-neugebauer.de/software/TeX/BibTool/index.en.html
.. _bibclean: http://www.math.utah.edu/pub/bibclean
.. _jabref: http://jabref.sourceforge.net/
.. _scons test framework: https://bitbucket.org/dirkbaechle/scons_test_framework
.. _tar: http://www.gnu.org/software/tar/
.. _epydoc: http://epydoc.sourceforge.net/
.. _SCons docbook tool: https://bitbucket.org/dirkbaechle/scons_docbook/
.. _SCons texas tool: https://github.com/ptomulik/scons-tool-texas/
.. _SCons dvipdfm tool: https://github.com/ptomulik/scons-tool-dvipdfm/
.. _SCons gnuplot tool: https://github.com/ptomulik/scons-tool-gnuplot/
.. _python-docutils: http://pypi.python.org/pypi/docutils
.. _python-pygments: http://pygments.org/
.. _docbook-xml: http://www.oasis-open.org/docbook/xml/
.. _xsltproc: http://xmlsoft.org/libxslt/
.. _gnuplot: http://www.gnuplot.info/
.. _inkscape: https://inkscape.org/
