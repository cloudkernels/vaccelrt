mbench_sources = files([
  'vaccel.c',
])

libvaccel_mbench = shared_library('vaccel-mbench',
  mbench_sources,
  version: libvaccel_version,
  include_directories : include_directories('.'),
  c_args : plugins_cargs,
  dependencies : libvaccel_private,
  install : true)
