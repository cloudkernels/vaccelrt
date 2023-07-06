project('vaccel', 'c', 'cpp',
  default_options: ['c_std=c11'],
  license: 'Apache-2.0')


vaccel_cargs = ['-Wall','-Wextra','-Werror']
plugins_cargs = ['-Wno-unused']

vaccel_version = run_command('scripts/generate-version.sh',
  meson.source_root(),
  check: false).stdout().strip()

libvaccel_version = vaccel_version.split('-')[0]

cmake = import('cmake')
cmake_opts = cmake.subproject_options()
cmake_opts.add_cmake_defines({'CMAKE_POSITION_INDEPENDENT_CODE': true})
slog_subproj = cmake.subproject('slog', options: cmake_opts)
slog_dep = slog_subproj.dependency('slog')

subdir('src')

subdir('plugins')
subdir('python')
