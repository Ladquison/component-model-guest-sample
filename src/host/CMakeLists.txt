cmake_minimum_required(VERSION 3.31)
set(TARGET_NAME HostApp)
project(${TARGET_NAME} CXX)

file(GLOB SRC_FILES
	"${CMAKE_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_SOURCE_DIR}/src/*.hpp"
)
add_executable(${TARGET_NAME} ${SRC_FILES})

set(WASMTIME_PATH "${TOOLS_PATH}/wasmtime")
target_include_directories(${TARGET_NAME} PRIVATE
	"${WASMTIME_PATH}/include"
)
target_link_libraries(${TARGET_NAME} PRIVATE
	"${WASMTIME_PATH}/lib/wasmtime.dll.lib"
)

# wasmファイルの置き場所を参照できるように定義
target_compile_definitions(${TARGET_NAME} PRIVATE
    -DWASM_PATH="${CMAKE_SOURCE_DIR}/wasm"
)

# main関数を持つプログラムをスタートアップに設定
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})

# 動的リンクするライブラリをコピー
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${WASMTIME_PATH}/lib/wasmtime.dll"
    $<TARGET_FILE_DIR:${TARGET_NAME}>
)
