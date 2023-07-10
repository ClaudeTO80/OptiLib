# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (LibOpt)
set(CMAKE_CXX_STANDARD 20)

option(LibOpt_BUILDSTATIC "Build static library" OFF)
option(LibOpt_BUILDSHARED "Build shared library" ON)
option(LibOpt_BUILDEXAMPLE1 "Build first example" OFF)
# option(POCO_PREFIX "" OFF)
set(POCO_PREFIX cachedValue CACHE PATH "")
set(OPENSSL_PREFIX cachedValue CACHE PATH "")
 # the directory containing "include" and "lib"
# set(POCO_PREFIX "/home/sotiris/Documents/Poco/poco/cmake-build/install")
# set(POCO_INCLUDE_DIR "${POCO_PREFIX}/include")
set(POCO_LIB_DIR "${POCO_PREFIX}/lib64")
set(POCO_BIN_DIR "${POCO_PREFIX}/bin64")

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
# add_subdirectory (Hello)
# add_subdirectory (Demo)
file(GLOB Opt_SRC CONFIGURE_DEPENDS  "src/*.cpp")
file(GLOB POCO_INCLUDE_DIRS CONFIGURE_DEPENDS  
		"${POCO_PREFIX}/Foundation/include"
		"${POCO_PREFIX}/Redis/include"
		"${POCO_PREFIX}/Util/include"
		"${POCO_PREFIX}/XML/include"
		"${POCO_PREFIX}/JSON/include"
		"${POCO_PREFIX}/JWT/include"
		"${POCO_PREFIX}/Crypto/include"
		"${POCO_PREFIX}/Net/include"
		"${POCO_PREFIX}/MongoDB/include"
		"${POCO_PREFIX}/Data/include"
		"${POCO_PREFIX}/Data/PostgreSQL/include"
		"${POCO_PREFIX}/Data/SQLite/include"
		"${POCO_PREFIX}/Data/MySQL/include"
		)
		
file(GLOB OPENSSL_INCLUDE_DIRS CONFIGURE_DEPENDS  
		"${OPENSSL_PREFIX}/include")
# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${POCO_INCLUDE_DIRS}")
include_directories("${OPENSSL_INCLUDE_DIRS}")
# set(CMAKE_LIBRARY_PATH_FLAG "${POCO_LIB_DIR}")

if (LibOpt_BUILDSTATIC)
	add_library (LibOpt_Static STATIC ${Opt_SRC})
	# target_include_directories (LibOpt_Static PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
	set_target_properties( LibOpt_Static 
    PROPERTIES
	OUTPUT_NAME LibOpt
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)	
	
	message("Static library exported in" "${CMAKE_BINARY_DIR}/lib")
endif(LibOpt_BUILDSTATIC)

if (LibOpt_BUILDSHARED)

	if (WIN32)
		set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	endif (WIN32)
	
	add_library (LibOpt_Shared SHARED ${Opt_SRC})
	# target_include_directories (LibOpt_Shared PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
	set_target_properties(LibOpt_Shared
		PROPERTIES
		OUTPUT_NAME LibOpt
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libDll"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libDll"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)

	target_link_directories(LibOpt_Shared PUBLIC "${POCO_LIB_DIR}")
	target_link_directories(LibOpt_Shared PUBLIC "${POCO_PREFIX}/VS2022/x64/lib/Debug")
	message(Shared library exported in "${CMAKE_BINARY_DIR}/bin")
	
endif(LibOpt_BUILDSHARED)

if (LibOpt_BUILDEXAMPLE1)
	file(GLOB Exmpl1_SRC CONFIGURE_DEPENDS  "examples/ex1.cpp")
		# message("Static library exported in" "${Exmpl1_SRC}/lib")
	add_executable(Ex1 ${Exmpl1_SRC})
	target_link_directories(Ex1 PUBLIC "${POCO_LIB_DIR}")

	target_link_libraries(Ex1
                      PUBLIC LibOpt_Static
						)
# set(MY_PATH "PATH=%PATH%" ${MY_CUSTOM_PATH})
set_target_properties(Ex1 PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=${POCO_BIN_DIR};%PATH%")
endif (LibOpt_BUILDEXAMPLE1)
# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
