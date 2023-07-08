test_sources = ['test_backend.cpp']
test_sources += [vaccel_plugin_source, vaccel_headers]

e = executable('backend_tests',
  sources : test_sources,
  c_args : vaccel_cargs,
  include_directories : vaccel_src_includes,
  dependencies : [libvaccel_deps, gtest_main_dep])

#test('backends_tests', e, protocol : 'gtest')
