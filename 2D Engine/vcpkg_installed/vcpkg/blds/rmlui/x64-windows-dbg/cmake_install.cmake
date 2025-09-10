# Install script for directory: D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/src/6.0-611c7f442e.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/pkgs/rmlui_x64-windows/debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/x64-windows-dbg/Source/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/x64-windows-dbg/Samples/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/RmlUi/RmlUiTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/RmlUi/RmlUiTargets.cmake"
         "D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/x64-windows-dbg/CMakeFiles/Export/d6af78c78fa6a3230f346d4b18450ea1/RmlUiTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/RmlUi/RmlUiTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/RmlUi/RmlUiTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/RmlUi" TYPE FILE FILES "D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/x64-windows-dbg/CMakeFiles/Export/d6af78c78fa6a3230f346d4b18450ea1/RmlUiTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/RmlUi" TYPE FILE FILES "D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/x64-windows-dbg/CMakeFiles/Export/d6af78c78fa6a3230f346d4b18450ea1/RmlUiTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/src/6.0-611c7f442e.clean/Include/RmlUi")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/RmlUi" TYPE FILE FILES
    "D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/x64-windows-dbg/install/RmlUiConfig.cmake"
    "D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/x64-windows-dbg/install/RmlUiConfigVersion.cmake"
    "D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/src/6.0-611c7f442e.clean/CMake/Dependencies.cmake"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/x64-windows-dbg/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/Programming/C++/Game Dev/Enginie/2D Engine/vcpkg_installed/vcpkg/blds/rmlui/x64-windows-dbg/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
