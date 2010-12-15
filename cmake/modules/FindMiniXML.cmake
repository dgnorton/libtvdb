# - Find MiniXML
# Find the MiniXML headers and libraries.
#
#  MiniXML_INCLUDE_DIRS - where to find include files.
#  MiniXML_LIBRARIES    - List of libraries.
#  MiniXML_FOUND        - True if MiniXML found.

#=============================================================================
# Copyright 2006-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)

# Look for the header file.
FIND_PATH(MiniXML_INCLUDE_DIR NAMES mxml.h)
MARK_AS_ADVANCED(MiniXML_INCLUDE_DIR)

# Look for the library.
FIND_LIBRARY(MiniXML_LIBRARY NAMES 
  mxml1.lib
)
MARK_AS_ADVANCED(MiniXML_LIBRARY)

# handle the QUIETLY and REQUIRED arguments and set MiniXML_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MiniXML DEFAULT_MSG MiniXML_LIBRARY MiniXML_INCLUDE_DIR)

IF(MiniXML_FOUND)
  SET(MiniXML_LIBRARIES ${MiniXML_LIBRARY})
  SET(MiniXML_INCLUDE_DIRS ${MiniXML_INCLUDE_DIR})
ENDIF(MiniXML_FOUND)
