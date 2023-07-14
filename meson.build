project('vaccel', 'c', 'cpp',
  meson_version : '>=1.1',
  default_options : ['c_std=c11'],
  license : 'Apache-2.0',
  license_files : 'LICENSE',
  version : run_command('scripts/generate-version.sh',
    '', '--no-dirty', check: false).stdout().strip())

vaccel_cargs = ['-Wall','-Wextra','-Werror']
plugins_cargs = ['-Wno-unused']

vaccel_version = run_command('scripts/generate-version.sh',
  meson.project_source_root(),
  check: false).stdout().strip()

libvaccel_version = vaccel_version.split('-')[0]

slog_subproj = subproject('slog')
#libslog_dep = slog_subproj.get_variable('libslog_dep')
libslog_dep = dependency('slog')

gtest_subproj = subproject('gtest') 
#gtest_main_dep = gtest_subproj.get_variable('gtest_main_dep') 
gtest_main_dep = dependency('gtest_main')

subdir('src')
subdir('plugins')
subdir('python')

opt_examples = get_option('examples')
if opt_examples.enabled()
  subdir('examples')
endif

opt_tests = get_option('tests')
if opt_tests.enabled()
  subdir('test')
endif

summary({
  'Build the exec plugin': opt_plugin_exec,
  'Build the no-op debugging plugin': opt_plugin_noop,
  'Build the examples': opt_examples,
  'Enable testing': opt_tests,
  },
  section : 'Configuration',
  bool_yn : true)

meson.add_dist_script(
  'scripts/dist.sh',
  'vaccel',
  'plugin-exec',
  opt_plugin_exec.enabled() ? 'enabled' : 'disabled',
  'plugin-noop',
  opt_plugin_noop.enabled() ? 'enabled' : 'disabled',
  'examples',
  opt_examples.enabled() ? 'enabled' : 'disabled',
  'tests',
  opt_tests.enabled() ? 'enabled' : 'disabled')
