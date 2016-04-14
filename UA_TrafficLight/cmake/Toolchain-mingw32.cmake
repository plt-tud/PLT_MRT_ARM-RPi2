# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)

#remove the runtime dependency for libgcc_s_sjlj-1.dll
set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc")

set(CMAKE_STRIP /opt/mingw-w32/bin/i686-w64-mingw32-strip)
set(CMAKE_C_COMPILER /opt/mingw-w32/bin/i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /opt/mingw-w32/bin/i686-w64-mingw32-g++)
set(CMAKE_RC_COMPILER /opt/mingw-w32/bin/i686-w64-mingw32-windres)
set(CMAKE_FIND_ROOT_PATH /opt/mingw-w32/i686-w64-mingw32-mingw32)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(ENV{PKG_CONFIG_LIBDIR} ${CMAKE_FIND_ROOT_PATH}/lib/pkgconfig)
set(ENV{PKG_CONFIG_PATH} ${CMAKE_FIND_ROOT_PATH}/lib/pkgconfig)
set(ENV{MINGDIR} ${CMAKE_FIND_ROOT_PATH}) 
