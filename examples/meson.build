examples_sources = [
  'exec.c',
  'minmax_generic.c',
  'pynq_array_copy_generic.c',
  'sgemm.c',
  'classify.c',
  'exec_generic.c',
  'pynq_parallel.c',
  'sgemm_generic.c',
  'classify_generic.c',
  'exec_with_res.c',
  'pynq_parallel_generic.c',
  'tf_inference.c',
  'depth.c',
  'noop.c',
  'pynq_vector_add.c',
  'tf_model.c',
  'depth_generic.c',
  'pose.c',
  'pynq_vector_add_generic.c',
  'tf_saved_model.c',
  'detect.c',
  'pose_generic.c',
  'segment.c',
  'torch_inference.cpp',
  'detect_generic.c',
  'minmax.c',
  'pynq_array_copy.c',
  'segment_generic.c',
]

foreach e : examples_sources
  exe = executable(e.split('.')[0],
    files(e) + vaccel_utils_c + vaccel_headers,
    c_args : vaccel_cargs,
    cpp_args : vaccel_cargs,
    include_directories : vaccel_includes,
    dependencies : [libvaccel_private],
    install : true)
endforeach

mytestlib = library('mytestlib',
  files('mytestlib.c'),
  c_args : vaccel_cargs,
  install : true)

foreach d : ['models', 'images', 'input']
  install_subdir(d, install_dir : 'share/vaccel')
endforeach
