set(BINARY ${CMAKE_PROJECT_NAME}_test)
set (SOURCE
    main.cpp
    vec3_tests.cpp
    )

add_executable(${BINARY} ${SOURCE})
add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

