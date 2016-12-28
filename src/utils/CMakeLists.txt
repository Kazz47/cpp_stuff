find_package (glog REQUIRED)

add_library (utils OBJECT
             stringIt.cpp
             timer.cpp
             timerLog.cpp)
target_compile_features (utils PRIVATE cxx_auto_type)
