# determine if the OS is 32 or 64 bit
if (UNIX AND NOT WIN32)
   if (CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET(OS_64_BIT true)
      MESSAGE("********** 64 BIT OS **********")
   else(OS_64_BIT)
      MESSAGE("********** 32 BIT OS **********")
   endif(CMAKE_SIZEOF_VOID_P MATCHES "8")
endif (UNIX AND NOT WIN32)

# add current directory to the included directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(CURL REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(Iconv REQUIRED)

include_directories(
   ${CURL_INCLUDE_DIRS}
   ${LIBXML2_INCLUDE_DIR}
   ${ICONV_INCLUDE_DIR}
   )

# figure out whether to use 32 or 64 bit luxand libs
if(OS_64_BIT)
  # do something 64 bit specific 
else(OS_64_BIT)
  # do something 32 bit specific 
endif(OS_64_BIT)

# Allow the developer to select if Dynamic or Static libraries are built
option (SHARED_LIB "Build Shared Libraries" OFF)
# Set the LIB_TYPE variable to STATIC
set (LIB_TYPE STATIC)
if (SHARED_LIB)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  set (LIB_TYPE SHARED)
else (SHARED_LIB)
  add_definitions(-DLIBTVDB_STATIC)
endif (SHARED_LIB)

# create executable(s) from the source files
add_library(tvdb ${LIB_TYPE} tvdb_types.c tvdb_xml.c tvdb.c tvdb_list.c)
add_executable(tvdb_test tvdb_test.c)
add_dependencies(tvdb_test tvdb)

if (MSVC)
   set_target_properties(tvdb PROPERTIES LINK_FLAGS "/MAP")
endif(MSVC)

# set libraries to link against
target_link_libraries(tvdb
   ${CURL_LIBRARIES}
   ${LIBXML2_LIBRARIES}
   ${ICONV_LIBRARIES}
   )
   
target_link_libraries(tvdb_test tvdb)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/tvdb_key_template.h ${CMAKE_CURRENT_SOURCE_DIR}/tvdb_key.h COPYONLY)

#copy default config file
#file(COPY "pcproxd.cfg" DESTINATION .)
