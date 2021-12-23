set(BINARY ${CMAKE_PROJECT_NAME})

set (SOURCE
    main.cpp
)

add_executable(${BINARY} ${SOURCE})
add_library(${BINARY}_lib STATIC ${SOURCE})

