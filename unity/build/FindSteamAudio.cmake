# Copyright 2017-2023 Valve Corporation. Subject to the following license:
# https://valvesoftware.github.io/steam-audio/license.html

include(FindPackageHandleStandardArgs)
include(SteamAudioHelpers)

get_local_lib_path(IPL_LIB_PATH)

find_path(SteamAudio_INCLUDE_DIR
	NAMES 			phonon.h
	PATHS 			${CMAKE_HOME_DIRECTORY}/include
	PATH_SUFFIXES 	phonon
)

if (BUILD_SHARED_LIBS)
	find_library(SteamAudio_LIBRARY
		NAMES phonon
		PATHS ${IPL_LIB_PATH}
	)

	find_package_handle_standard_args(SteamAudio
		FOUND_VAR 		SteamAudio_FOUND
		REQUIRED_VARS 	SteamAudio_INCLUDE_DIR
	)
else()
	find_package_handle_standard_args(SteamAudio
		FOUND_VAR 		SteamAudio_FOUND
		REQUIRED_VARS 	SteamAudio_INCLUDE_DIR SteamAudio_LIBRARY
	)
endif()

if (SteamAudio_FOUND)
	if (NOT TARGET SteamAudio::SteamAudio)
		if (BUILD_SHARED_LIBS)
			add_library(SteamAudio INTERFACE)
			target_include_directories(SteamAudio INTERFACE ${SteamAudio_INCLUDE_DIR})

			add_library(SteamAudio::SteamAudio ALIAS SteamAudio)
		else()
			add_library(SteamAudio::SteamAudio UNKNOWN IMPORTED)
			set_target_properties(SteamAudio::SteamAudio PROPERTIES IMPORTED_LOCATION ${SteamAudio_LIBRARY})
			target_include_directories(SteamAudio::SteamAudio INTERFACE ${SteamAudio_INCLUDE_DIR})
		endif()
	endif()
endif()

mark_as_advanced(SteamAudio_INCLUDE_DIR SteamAudio_LIBRARY)
