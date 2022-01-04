set(BINARY ${CMAKE_PROJECT_NAME})

set (SOURCE
    main.cpp
    sphere.cpp
    hitable_list.cpp
    metal.cpp
    lambertian.cpp
    dielectric.cpp
    random_utils.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(${BINARY} ${SOURCE})
add_library(${BINARY}_lib STATIC ${SOURCE})

