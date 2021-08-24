import subprocess, os

project = 'CE C Toolchain'
copyright = '2015-2021 CE Programming'
author = 'CE Programming'

current_version = os.environ['current_version']
versions = os.environ['versions'].split()

extensions = [
    'breathe',
    'sphinx_rtd_theme',
    'sphinx.ext.autodoc',
    'sphinx.ext.viewcode',
    'sphinx.ext.githubpages',
]

html_theme_options = {
    'display_version': True,
    'titles_only': False
}


templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
language = None
exclude_patterns = ['build', '_build', 'Thumbs.db', '.DS_Store']
pygments_style = None
html_theme = 'sphinx_rtd_theme'
html_show_sourcelink = False

try:
   html_context
except NameError:
   html_context = dict()
html_context['display_lower_left'] = True
html_context['current_version'] = current_version
html_context['version'] = current_version
html_context['versions'] = list()
for version in versions:
   html_context['versions'].append( (version, '/' + version + '/index.html') )

breathe_projects = {}
breathe_default_project = 'CE C Toolchain'
subprocess.call('doxygen doxyfile', shell=True)
breathe_projects['CE C Toolchain'] = 'doxygen/xml'
