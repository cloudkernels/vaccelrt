examples_sources = files([
  'classify.c',
  'classify_generic.c',
  'detect.c',
  'detect_generic.c',
  'segment.c',
  'segment_generic.c',
  'pose.c',
  'pose_generic.c',
  'depth.c',
  'depth_generic.c',
  'exec.c',
  'exec_with_res.c',
  'exec_generic.c',
  'noop.c',
  'sgemm.c',
  'sgemm_generic.c',
  'minmax.c',
  'minmax_generic.c',
  'single_model.c',
  'tf_saved_model.c',
  'tf_inference.c',
  'tflite_inference.c',
  'torch_inference.cpp',
  'pynq_vector_add.c',
  'pynq_vector_add_generic.c',
  'pynq_parallel.c',
  'pynq_parallel_generic.c',
  'pynq_array_copy.c',
  'pynq_array_copy_generic.c',
  'exec_helpers.c',
  'exec_helpers_nonser.c',
  'mbench.c',
  'local_and_virtio.c',
])

examples = []
foreach e : examples_sources
  examples += executable(fs.stem(e),
    sources : [e, vaccel_utils_c, vaccel_headers],
    c_args : vaccel_cargs,
    cpp_args : vaccel_cargs + vaccel_cppargs,
    include_directories : vaccel_includes,
    dependencies : [libvaccel_private],
    install : true)
endforeach

mytestlib = library('mytestlib',
  files('mytestlib.c'),
  c_args : vaccel_cargs,
  include_directories : vaccel_includes,
  dependencies : [libvaccel_private],
  install : true)

foreach d : ['models', 'images', 'input']
  install_subdir(d, install_dir : 'share/vaccel')
endforeach
