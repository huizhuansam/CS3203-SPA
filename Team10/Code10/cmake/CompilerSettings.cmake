if (APPLE) 
  set(CMAKE_CXX_FLAGS_DEBUG "-g") # debug

  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall") # turn on all warnings
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wextra") # turn on even more warnings
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wshadow") # warn the user if a variable declaration shadows one from a parent context
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wnon-virtual-dtor") # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wold-style-cast") # warn for c-style casts
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wcast-align") # warn for potential performance problem casts
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wunused") # warn on anything being unused
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Woverloaded-virtual") # warn if you overload (not override) a virtual function
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wpedantic") # warn if non-standard C++ is used
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wconversion") # warn on type conversions that may lose data
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wsign-conversion") # warn on sign conversions
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wnull-dereference") # warn if a null dereference is detected
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wdouble-promotion") # warn if float is implicit promoted to double
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wformat=2") # warn on security issues around functions that format output (ie printf)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wimplicit-fallthrough") # warn on switch statements fallthrough
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Werror") # turn all warnings into errors

  # custom build type for CI
  set(CMAKE_CXX_FLAGS_CI "${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS_CI "${CMAKE_CXX_FLAGS_CI} ${CMAKE_CXX_FLAGS_RELEASE}") # all the compiler warnings
  set(CMAKE_CXX_FLAGS_CI "${CMAKE_CXX_FLAGS_CI} -fprofile-instr-generate -fcoverage-mapping") # code coverage
  set(CMAKE_CXX_FLAGS_CI "${CMAKE_CXX_FLAGS_CI} -O0") # no optimization needed for CI, should be faster

  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3") # maximum optimization
endif()

if (MSVC) 
  set(CMAKE_CXX_FLAGS_DEBUG "/Zi") # debug

  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2") # maximum optimization
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W4") # Baseline reasonable warnings
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14242") # 'identifier': conversion from 'type1' to 'type2', possible loss of data
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14254") # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14263") # 'function': member function does not override any base class virtual member function
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14265") # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not
                # be destructed correctly
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14287") # 'operator': unsigned/negative constant mismatch
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /we4289") # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside
                # the for-loop scope
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14296") # 'operator': expression is always 'boolean_value'
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14311") # 'variable': pointer truncation from 'type1' to 'type2'
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14545") # expression before comma evaluates to a function which is missing an argument list
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14546") # function call before comma missing argument list
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14547") # 'operator': operator before comma has no effect; expected operator with side-effect
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14549") # 'operator': operator before comma has no effect; did you intend 'operator'?
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14555") # expression has no effect; expected expression with side- effect
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14619") # pragma warning: there is no warning number 'number'
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14640") # Enable warning on thread un-safe static member initialization
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14826") # Conversion from 'type1' to 'type2' is sign-extended. This may cause unexpected runtime behavior
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14905") # wide string literal cast to 'LPSTR'
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14906") # string literal cast to 'LPWSTR'
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w14928") # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /permissive") # standards conformance mode for MSVC compiler
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /WX") # turn all warnings into errors
endif()
