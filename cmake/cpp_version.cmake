# default cpp build settings to build with same level of language in projects

# set compile prerequisites
macro (cpp_version cpp_version_nb)
	set(CMAKE_CXX_STANDARD ${cpp_version_nb})
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF) # -std=c++20 instead of -std=gnu++20
endmacro()