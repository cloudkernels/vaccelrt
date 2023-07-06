conf = configuration_data()
conf.set('VACCELRT_VERSION', vaccel_version)

vaccel_h = configure_file(input : 'vaccel.h.in',
  output : 'vaccel.h',
  configuration : conf)

vaccel_headers = files([
  'utils.h',
  'error.h',
  'log.h',
  'misc.h',
  'plugin.h',
  'session.h',
  'list.h',
  'id_pool.h',
  'resources.h',
])

vaccel_sources = files([
  'log.c',
  'misc.c',
  'plugin.c',
  'session.c',
  'resources.c',
  'vaccel.c',
  'id_pool.c',
  'utils.c',
])

subdir('include')
subdir('resources')
subdir('ops')
subdir('profiling')

vaccel_sources += vaccel_headers
vaccel_sources += vaccel_h
vaccel_includes = include_directories('include')

libvaccel_deps = [dependency('threads'), dependency('dl')]
libvaccel = library('vaccel',
  vaccel_sources,
  version: libvaccel_version,
  c_args : vaccel_cargs,
  include_directories : vaccel_includes,
  dependencies : [libvaccel_deps, slog_dep],
  install : true)

libvaccel_private = declare_dependency(
  sources : vaccel_headers,
  include_directories : vaccel_includes,
  dependencies : libvaccel_deps,
  link_with: libvaccel)

pkg_mod = import('pkgconfig')
pkg_mod.generate(libvaccel,
  libraries : libvaccel,
  version : libvaccel_version,
  name : 'vaccel',
  description : 'Hardware Acceleration for Serverless Computing')
