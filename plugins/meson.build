opt_plugin_noop = get_option('plugin-noop')
opt_plugin_exec = get_option('plugin-exec')
opt_plugin_mbench = get_option('plugin-mbench')

if opt_plugin_noop.enabled()
  subdir('noop')
endif
if opt_plugin_exec.enabled()
  subdir('exec')
endif
if opt_plugin_mbench.enabled()
  subdir('mbench')
endif
