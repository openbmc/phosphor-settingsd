project('phosphor-settingsd', 'cpp',
  version: '1.0',
  meson_version: '>=0.58.0',
  default_options: [
    'warning_level=3',
    'werror=true',
    'cpp_std=c++20',
  ]
)
cpp = meson.get_compiler('cpp')

python_prog = find_program('python3', native: true)

# Define dependencies
sdbusplus_dep = dependency('sdbusplus')
phosphor_dbus_interfaces_dep = dependency('phosphor-dbus-interfaces')
phosphor_logging_dep = dependency('phosphor-logging')
cereal_dep = dependency('cereal', required: false)
has_cereal = cpp.has_header_symbol(
    'cereal/cereal.hpp',
    'cereal::specialize',
    dependencies: cereal_dep,
    required: false)
if not has_cereal
    cereal_opts = import('cmake').subproject_options()
    cereal_opts.add_cmake_defines({'BUILD_TESTS': 'OFF'})
    cereal_proj = import('cmake').subproject(
        'cereal',
        options: cereal_opts,
        required: false)
    assert(cereal_proj.found(), 'cereal is required')
    cereal_dep = cereal_proj.dependency('cereal')
endif

# Generate settings_manager.hpp
settings_gen = custom_target(
    'settings_manager.hpp'.underscorify(),
    input: [
        'settings.py',
        'settings_manager.mako.hpp',
        get_option('settings_yaml'),
    ],
    output: 'settings_manager.hpp',
    command: [ python_prog, '@INPUT0@', '-i', '@INPUT2@' ],
)

subdir('config')

# Generate daemon
settings_manager_sources = [
    settings_gen,
]

settings_manager_deps = [
  cereal_dep,
  conf_h_dep,
  sdbusplus_dep,
  phosphor_dbus_interfaces_dep,
  phosphor_logging_dep,
]

executable(
    'phosphor-settings-manager',
    'settings_main.cpp',
    settings_manager_sources,
    dependencies: [
        settings_manager_deps,
    ],
    install: true,
)
