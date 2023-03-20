# Set all default build flags (warning check)

macro (cpp_flags cpp_target)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_compile_options(${cpp_target} PRIVATE -Xclang -fcxx-exceptions) # Enable exceptions
		target_compile_options(${cpp_target} PRIVATE -Wall -Wextra) # reasonable and standard
		target_compile_options(${cpp_target} PRIVATE -Wshadow) # warn the user if a variable declaration shadows one from a parent context
		target_compile_options(${cpp_target} PRIVATE -Wnon-virtual-dtor) # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
		target_compile_options(${cpp_target} PRIVATE -Wold-style-cast) # warn for c-style casts
		target_compile_options(${cpp_target} PRIVATE -Wcast-align) # warn for potential performance problem casts
		target_compile_options(${cpp_target} PRIVATE -Wunused) # warn on anything being unused
		target_compile_options(${cpp_target} PRIVATE -Woverloaded-virtual) # warn if you overload (not override) a virtual function
		target_compile_options(${cpp_target} PRIVATE -Wpedantic) # (all versions of GCC, Clang >= 3.2) warn if non-standard C++ is used
		target_compile_options(${cpp_target} PRIVATE -Wconversion) # warn on type conversions that may lose data
		target_compile_options(${cpp_target} PRIVATE -Wsign-conversion) # (Clang all versions, GCC >= 4.3) warn on sign conversions
		target_compile_options(${cpp_target} PRIVATE -Wdouble-promotion) # (GCC >= 4.6, Clang >= 3.8) warn if float is implicitly promoted to double
		target_compile_options(${cpp_target} PRIVATE -Wformat=2) # warn on security issues around functions that format output (i.e., printf)
		target_compile_options(${cpp_target} PRIVATE -Wimplicit-fallthrough) # Warns when case statements fall-through. (Included with -Wextra in GCC, not in clang)
		target_compile_options(${cpp_target} PRIVATE -Wno-c++98-compat -Wno-c++98-compat-pedantic) # Disable c++98 compat warnings.
		target_compile_options(${cpp_target} PRIVATE -Wno-missing-noreturn) # Disable warning on not specify 'noreturn' attribute.
		target_compile_options(${cpp_target} PRIVATE -Wno-global-constructors) # Disable declaration requires a global constructor.
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_compile_options(${cpp_target} PRIVATE -pedantic) # Warn on language extensions
		target_compile_options(${cpp_target} PRIVATE -Wall -Wextra) # reasonable and standard
		target_compile_options(${cpp_target} PRIVATE -Wshadow) # warn the user if a variable declaration shadows one from a parent context
		target_compile_options(${cpp_target} PRIVATE -Wnon-virtual-dtor) # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
		target_compile_options(${cpp_target} PRIVATE -Wold-style-cast) # warn for c-style casts
		target_compile_options(${cpp_target} PRIVATE -Wcast-align) # warn for potential performance problem casts
		target_compile_options(${cpp_target} PRIVATE -Wunused) # warn on anything being unused
		target_compile_options(${cpp_target} PRIVATE -Woverloaded-virtual) # warn if you overload (not override) a virtual function
		target_compile_options(${cpp_target} PRIVATE -Wpedantic) # (all versions of GCC, Clang >= 3.2) warn if non-standard C++ is used
		target_compile_options(${cpp_target} PRIVATE -Wconversion) # warn on type conversions that may lose data
		target_compile_options(${cpp_target} PRIVATE -Wsign-conversion) # (Clang all versions, GCC >= 4.3) warn on sign conversions
		target_compile_options(${cpp_target} PRIVATE -Wmisleading-indentation) # (only in GCC >= 6.0) warn if indentation implies blocks where blocks do not exist
		target_compile_options(${cpp_target} PRIVATE -Wduplicated-cond) # (only in GCC >= 6.0) warn if if / else chain has duplicated conditions
		target_compile_options(${cpp_target} PRIVATE -Wduplicated-branches) # (only in GCC >= 7.0) warn if if / else branches have duplicated code
		target_compile_options(${cpp_target} PRIVATE -Wlogical-op) # (only in GCC) warn about logical operations being used where bitwise were probably wanted
		target_compile_options(${cpp_target} PRIVATE -Wnull-dereference) # (only in GCC >= 6.0) warn if a null dereference is detected
		target_compile_options(${cpp_target} PRIVATE -Wuseless-cast) # (only in GCC >= 4.8) warn if you perform a cast to the same type
		target_compile_options(${cpp_target} PRIVATE -Wdouble-promotion) # (GCC >= 4.6, Clang >= 3.8) warn if float is implicitly promoted to double
		target_compile_options(${cpp_target} PRIVATE -Wformat=2) # warn on security issues around functions that format output (i.e., printf)
		target_compile_options(${cpp_target} PRIVATE -Wimplicit-fallthrough) # Warns when case statements fall-through. (Included with -Wextra in GCC, not in clang)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		target_compile_options(${cpp_target} PRIVATE /permissive-) # Enforces standards conformance.
		target_compile_options(${cpp_target} PRIVATE /W4) # All reasonable warnings
		target_compile_options(${cpp_target} PRIVATE /w14242) # 'identfier': conversion from 'type1' to 'type1', possible loss of data
		target_compile_options(${cpp_target} PRIVATE /w14254) # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
		target_compile_options(${cpp_target} PRIVATE /w14263) # 'function': member function does not override any base class virtual member function
		target_compile_options(${cpp_target} PRIVATE /w14265) # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
		target_compile_options(${cpp_target} PRIVATE /w14287) # 'operator': unsigned/negative constant mismatch
		target_compile_options(${cpp_target} PRIVATE /we4289) # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside the for-loop scope
		target_compile_options(${cpp_target} PRIVATE /w14296) # 'operator': expression is always 'boolean_value'
		target_compile_options(${cpp_target} PRIVATE /w14311) # 'variable': pointer truncation from 'type1' to 'type2'
		target_compile_options(${cpp_target} PRIVATE /w14545) # expression before comma evaluates to a function which is missing an argument list
		target_compile_options(${cpp_target} PRIVATE /w14546) # function call before comma missing argument list
		target_compile_options(${cpp_target} PRIVATE /w14547) # 'operator': operator before comma has no effect; expected operator with side-effect
		target_compile_options(${cpp_target} PRIVATE /w14549) # 'operator': operator before comma has no effect; did you intend 'operator'?
		target_compile_options(${cpp_target} PRIVATE /w14555) # expression has no effect; expected expression with side-effect
		target_compile_options(${cpp_target} PRIVATE /w14619) # pragma warning: there is no warning number 'number'
		target_compile_options(${cpp_target} PRIVATE /w14640) # Enable warning on thread unsafe static member initialization
		target_compile_options(${cpp_target} PRIVATE /w14826) # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
		target_compile_options(${cpp_target} PRIVATE /w14905) # wide string literal cast to 'LPSTR'
		target_compile_options(${cpp_target} PRIVATE /w14906) # string literal cast to 'LPWSTR'
		target_compile_options(${cpp_target} PRIVATE /w14928) # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
	endif()
endmacro()