"""`tfgen`

Functions used by scripts generating projects from templates. 
"""

#
# Copyright (c) 2013 by Pawel Tomulik <ptomulik@meil.pw.edu.pl>
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE

import argparse

def add_cli_args(argparser, input_dir, output_dir, default_template):

    argparser.add_argument('-q','--quiet', action = "store_false",
            dest = 'verbose', help = "don't print status messages to stdout")
    argparser.add_argument('-i','--input-dir', type = str, 
                           metavar = 'input_dir', action = 'store',
                           dest = 'input_dir', 
                           default = input_dir, 
                           help = 'input (template) directory (%s)' % input_dir)
    argparser.add_argument('-o','--output-dir', type = str, 
                           metavar = 'output_dir', action = 'store',
                           dest = 'output_dir', 
                           default = output_dir, 
                           help = 'output directory (%s)' % output_dir)
    argparser.add_argument('-t','--template', type = str, metavar = 'template', 
                           default = default_template, action = 'store',
                           dest = 'template',
                           help = 'project template to use (%s)'
                           % default_template)
    argparser.add_argument('project_name', metavar = 'name', action = 'store', 
                           help = 'project name, for example paper-96')

def generate_project(args, **subst):
    import re
    import string
    import os
    from sys import stderr, stdout
    from os import path, makedirs

    def cleanup(out_path, args):
        import shutil
        if args.verbose:
            stdout.write("info: trying to cleanup ... ")
        try: shutil.rmtree(out_path, True)
        except OSError: pass
        if args.verbose:
            stdout.write("done\n")

    error = 0

    if args.verbose:
        stdout.write("info: preparing to generate project %r\n" % args.project_name)
    
    tpl_path = path.join(args.input_dir, args.template)
    out_path = path.join(args.output_dir, args.project_name)
    manifest = path.join(tpl_path, 'MANIFEST')

    if not path.exists(tpl_path):
        stderr.write("error: %r: no such file or directory\n" % tpl_path)
        error = 1
    if not path.exists(manifest):
        stderr.write("error: %r: no such file or directory\n" % manifest)
        error = 1
    elif not path.isfile(manifest):
        stderr.write("error: %r: not a file\n" % manifest)
        error = 1
    if path.exists(out_path):
        stderr.write("error: %r: already exists, won't override\n" % out_path)
        error = 1 

    if not error:
        subst ['NAME'] = args.project_name

    if not error:
        _re_skip1 = re.compile(r'^\s*#.*\r?\n', re.M)
        _re_skip2 = re.compile(r'\s*(?:#.*)?$', re.M)
        _re_skip3 = re.compile(r'^\s+', re.M)
        _re_split = re.compile(r'^([^:]+)(?::(.+))?', re.M)
        if args.verbose:
            stdout.write("info: reading %r ... " % manifest)
        try:
            fh = open(manifest, 'rt')
        except IOError, e:
            if args.verbose:
                stdout.write("error\n")
            stderr.write("%s\n" % e)
            error = 1
        else:
            files = fh.read()
            if args.verbose:
                stdout.write("done\n")
            files = _re_skip1.sub('',files)
            files = _re_skip2.sub('',files)
            files = _re_skip3.sub('',files)
            files = files.split('\n')
            filemap = dict()
            for f in files:
                m = _re_split.match(f)
                if not m.group(1): continue
                ifi = path.join(tpl_path, *tuple(m.group(1).split('/'))) 
                if m.group(2):
                    ofi = path.join(out_path, *tuple(m.group(2).split('/')))
                else:
                    ofi = path.join(out_path, *tuple(f.split('/')))
                ifi = string.Template(ifi).substitute(subst)
                ofi = string.Template(ofi).substitute(subst)
                filemap[ifi] = ofi
                
    if not error:
        if args.verbose:
            stdout.write("info: creating directory %r ... " % out_path)
        try:
            makedirs(out_path)
        except os.error, e:
            if args.verbose:
                stdout.write("error\n")
            stderr.write("%s\n", e)
            error = 1
        else:    
            if args.verbose:
                stdout.write("done\n")

    if not error:
        if args.verbose:
            stdout.write("info: generating files\n")
        for (ifi, ofi) in filemap.items():
            if args.verbose:
                stdout.write("info: read %r ... " % ifi)
            try:
                contents = open(ifi,'rt').read()
            except IOError, e:
                if args.verbose:
                    stdout.write("error\n")
                stderr.write("%s\n" % e)
                cleanup(out_path, args)
                error = 1
                break
            else:
                if args.verbose:
                    stdout.write("done\n")
            template = string.Template(contents)
            contents = template.substitute(subst)
            if args.verbose:
                stdout.write("info: write %r ... " % ofi)
            try:
                open(ofi,'wt').write(contents)
            except IOError, e:
                if args.verbose:
                    stdout.write("error\n")
                stderr.write("%s\n" % e)
                cleanup(out_path, args)
                error = 1
                break
            else:
                if args.verbose:
                    stdout.write("done\n")

    return error
