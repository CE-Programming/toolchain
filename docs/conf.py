import subprocess, os

breathe_projects = {}

project = 'CE C Toolchain'
copyright = '2015-2020'
author = 'CE Developers'

release = 'v9.0-devel'

extensions = ['breathe']
exclude_patterns = ['build', 'Thumbs.db', '.DS_Store']
html_theme = 'sphinx_rtd_theme'
html_theme_options = {
    'display_version': True,
    'prev_next_buttons_location': 'bottom',
    'style_external_links': False,
    'logo_only': False,
    'collapse_navigation': True,
    'sticky_navigation': True,
    'navigation_depth': 4,
    'includehidden': True,
    'titles_only': False
}

breathe_default_project = 'CE C Toolchain'
subprocess.call('doxygen doxyfile', shell=True)
breathe_projects['CE C Toolchain'] = 'doxygen/xml'

