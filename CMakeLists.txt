cmake_minimum_required(VERSION 3.3)
project(Autofac_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/home/bartoszborowik/projekty/googletest/googletest/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/home/bartoszborowik/projekty/Autofac-cpp/DI")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/home/bartoszborowik/projekty/Autofac-cpp/DIGTest/Support")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_USE_OWN_TR1_TUPLE=0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_DI_API")

set(SOURCE_FILES
    DI/Container.cpp
    DI/ContainerBuilder.cpp
    DIGTest/DIGTest.cpp
    DIGTest/ConstServiceTest.cpp
    DIGTest/ContainerBuilderUsageTest.cpp
    DIGTest/ResolveEfficiencyTest.cpp
    DIGTest/ServiceFactoryAsSingleInstanceTest.cpp
    DIGTest/ServiceFactoryAsTypeTest.cpp
    DIGTest/ServiceFactoryTest.cpp
    DIGTest/ServiceFactoryWithDependenciesTest.cpp
    DIGTest/ServiceInstanceAsTypeTest.cpp
    DIGTest/ServiceInstanceTest.cpp
    DIGTest/ServiceTypeAsSingleInstance.cpp
    DIGTest/ServiceTypeAsTypeTest.cpp
    DIGTest/ServiceTypeTest.cpp
    DIGTest/ServiceTypeWithDependencies.cpp
    DIGTest/StandardServiceInstanceTest.cpp
)

set(GTEST_FILES
    ../googletest/googletest/build-aux/gtest-all.o
)

add_executable(Autofac_cpp ${SOURCE_FILES} ${GTEST_FILES})