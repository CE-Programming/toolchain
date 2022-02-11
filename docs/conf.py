import subprocess, os

project = 'CE C/C++ Toolchain'
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
    'sphinx.ext.imgconverter',
]

html_theme_options = {
    'display_version': True,
    'titles_only': False
}

latex_engine = 'pdflatex'
latex_elements = {
  'papersize': 'letterpaper',
  'figure_align': 'H',
  'extraclassoptions': 'openany,oneside',
  'fncychap': r'\usepackage[Sonny]{fncychap}',
  'pointsize': '11pt',
  'preamble': r'''
    \usepackage{charter}
    \usepackage[defaultsans]{lato}
    \usepackage{inconsolata}
  ''',
}

templates_path = ['templates']
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
   html_context['versions'].append( (version, '/toolchain/' + version + '/index.html') )

breathe_projects = {}
breathe_default_project = 'CE C/C++ Toolchain'
subprocess.call('doxygen doxyfile', shell=True)
breathe_projects['CE C/C++ Toolchain'] = 'doxygen/xml'
