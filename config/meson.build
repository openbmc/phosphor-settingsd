# Create config.h with constants that use to come from autoconf.
conf_h_inc = include_directories('.')
configure_file(
    input: 'config.h.meson',
    output: 'config.h',
    command: ['cp', '@INPUT@', '@OUTPUT@'],
)
