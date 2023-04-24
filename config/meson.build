# Create config.h with constants that use to come from autoconf.
conf_h_dep = declare_dependency(
    include_directories: include_directories('.'),
    sources: configure_file(
        input: 'config.h.meson',
        output: 'config.h',
        command: ['cp', '@INPUT@', '@OUTPUT@'],
    )
)
