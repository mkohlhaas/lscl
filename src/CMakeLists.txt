add_executable(${PROJECT_NAME} lscl.c device.c deviceCL.c error.c deviceJson.c platformJson.c platform.c platformCL.c version.c)
target_link_libraries(${PROJECT_NAME} PRIVATE json-c::json-c)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenCL::OpenCL)
