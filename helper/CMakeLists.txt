set(local_module SpdlogHelper)
aux_source_directory(. local_source)
set(local_dependency spdlog)
set(local_export_header ${CMAKE_CURRENT_LIST_DIR})

if (enable_spdlog)
    message(STATUS "enable SPDLOG")
    set(local_cflags -DENABLE_SPDLOG)
endif()

build_shared_library()