set(local_module example)
aux_source_directory(. local_source)
set(local_dependency SpdlogHelper spdlog)
build_executable()