project(
    'phosphor-settingsd',
    'cpp',
    version: '1.0',
    meson_version: '>=1.1.1',
    default_options: ['warning_level=3', 'werror=true', 'cpp_std=c++23'],
)
cpp = meson.get_compiler('cpp')

python_prog = find_program('python3', native: true)

# Define dependencies
sdbusplus_dep = dependency('sdbusplus', required: false)
phosphor_dbus_interfaces_dep = dependency('phosphor-dbus-interfaces')
phosphor_logging_dep = dependency('phosphor-logging')
cereal_dep = dependency('cereal', required: false)
has_cereal = cpp.has_header_symbol(
    'cereal/cereal.hpp',
    'cereal::specialize',
    dependencies: cereal_dep,
    required: false,
)
if not has_cereal
    cereal_opts = import('cmake').subproject_options()
    cereal_opts.add_cmake_defines(
        {'BUILD_TESTS': 'OFF', 'SKIP_PERFORMANCE_COMPARISON': 'ON'},
    )
    cereal_proj = import('cmake').subproject(
        'cereal',
        options: cereal_opts,
        required: false,
    )
    assert(cereal_proj.found(), 'cereal is required')
    cereal_dep = cereal_proj.dependency('cereal')
endif

# Generate settings_manager.hpp
settings_gen_env = {}
if not sdbusplus_dep.found()
    sdbusplus_proj = subproject('sdbusplus')
    sdbusplus_dep = sdbusplus_proj.get_variable('sdbusplus_dep')
    settings_gen_env = {
        'PYTHONPATH': meson.current_source_dir() / 'subprojects' / 'sdbusplus' / 'tools',
    }
endif

settings_gen = custom_target(
    'settings_manager.hpp'.underscorify(),
    input: [
        'settings.py',
        'settings_manager.hpp.mako',
        get_option('settings_yaml'),
    ],
    output: 'settings_manager.hpp',
    command: [python_prog, '@INPUT0@', '-i', '@INPUT2@'],
    env: settings_gen_env,
)

# Generate daemon
settings_manager_sources = [settings_gen]

settings_manager_deps = [
    cereal_dep,
    sdbusplus_dep,
    phosphor_dbus_interfaces_dep,
    phosphor_logging_dep,
]

executable(
    'phosphor-settings-manager',
    'settings_main.cpp',
    settings_manager_sources,
    dependencies: [settings_manager_deps],
    install: true,
)
