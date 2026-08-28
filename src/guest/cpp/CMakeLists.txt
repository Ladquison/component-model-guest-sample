cmake_minimum_required(VERSION 3.31)
project(${TARGET_NAME} CXX)

set(CMAKE_SYSROOT "${WASI_SDK_PREFIX}/share/wasi-sysroot")

file(GLOB SRC_FILES
	"${CMAKE_SOURCE_DIR}/*.cpp"
	"${CMAKE_SOURCE_DIR}/wit/*.cpp"
)
add_executable(${TARGET_NAME} ${SRC_FILES})

target_compile_options(${TARGET_NAME} PRIVATE
    -O3
    -g
)

target_link_options(${TARGET_NAME} PRIVATE
    -mexec-model=reactor
)

file(GLOB WIT_OBJECTS
    "${CMAKE_SOURCE_DIR}/wit/*.o"
)
target_link_libraries(${TARGET_NAME} PRIVATE
    ${WIT_OBJECTS}
)

set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".wasm")

install(FILES
	"${CMAKE_BINARY_DIR}/${TARGET_NAME}.wasm"
	DESTINATION "${HOST_OUTPUT_PATH}"
)
