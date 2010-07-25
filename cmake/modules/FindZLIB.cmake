# Custom Aqsis specific version of FindTIFF
SET(AQSIS_ZLIB_FOUND 0)

SET(AQSIS_ZLIB_INCLUDE_SEARCHPATH)
SET(AQSIS_ZLIB_LIBRARY_NAMES z zlib)

IF(WIN32)
	IF(AQSIS_WIN32LIBS)
		SET(AQSIS_ZLIB_INCLUDE_SEARCHPATH ${AQSIS_ZLIB_INCLUDE_SEARCHPATH} ${AQSIS_WIN32LIBS}/zlib/include)
		IF(MSVC AND MSVC80)
			SET(AQSIS_ZLIB_LIBRARIES_DIR ${AQSIS_WIN32LIBS}/zlib/lib/vc8_sp1 CACHE PATH "Semi-colon separated list of paths to search for zlib libraries")
			SET(AQSIS_ZLIB_LIBRARY_NAMES ${AQSIS_ZLIB_LIBRARY_NAMES} zlibstat)
		ELSEIF(MSVC AND MSVC90)
			SET(AQSIS_ZLIB_LIBRARIES_DIR ${AQSIS_WIN32LIBS}/zlib/lib/vc9_sp1 CACHE PATH "Semi-colon separated list of paths to search for zlib libraries")
			SET(AQSIS_ZLIB_LIBRARY_NAMES ${AQSIS_ZLIB_LIBRARY_NAMES} zlibstat)		
		ELSE(MSVC AND MSVC80)
			IF(MINGW)
				SET(AQSIS_ZLIB_LIBRARIES_DIR ${AQSIS_WIN32LIBS}/zlib/lib/mingw CACHE PATH "Semi-colon separated list of paths to search for zlib libraries")
				SET(AQSIS_ZLIB_LIBRARY_NAMES ${AQSIS_ZLIB_LIBRARY_NAMES} z)
			ENDIF(MINGW)
		ENDIF(MSVC AND MSVC80)
	ENDIF(AQSIS_WIN32LIBS)
	if(MINGW)
		LIST(APPEND AQSIS_ZLIB_INCLUDE_SEARCHPATH ${AQSIS_DEPENDENCIES}/include)
		LIST(APPEND AQSIS_ZLIB_LIBRARIES_DIR ${AQSIS_DEPENDENCIES}/lib)
	endif()
ELSE(WIN32)
	SET(AQSIS_ZLIB_LIBRARIES_DIR CACHE PATH "Semi-colon separated list of paths to search for zlib libraries")
ENDIF(WIN32)

FIND_PATH(AQSIS_ZLIB_INCLUDE_DIR
			zlib.h
			PATHS ${AQSIS_ZLIB_INCLUDE_SEARCHPATH}
			DOC "Location of the zlib headers"
			)

FIND_LIBRARY(AQSIS_ZLIB_LIBRARIES
			NAMES ${AQSIS_ZLIB_LIBRARY_NAMES}	
			PATHS ${AQSIS_ZLIB_LIBRARIES_DIR}
			DOC "Location of the zlib library"
			)
MARK_AS_ADVANCED(AQSIS_ZLIB_LIBRARIES)


STRING(COMPARE EQUAL "${AQSIS_ZLIB_INCLUDE_DIR}" "AQSIS_ZLIB_INCLUDE-NOTFOUND" AQSIS_ZLIB_INCLUDE_NOTFOUND)
STRING(COMPARE EQUAL "${AQSIS_ZLIB_LIBRARIES}" "AQSIS_ZLIB_LIBRARIES-NOTFOUND" AQSIS_ZLIB_LIBRARIES_NOTFOUND)

IF(NOT AQSIS_ZLIB_LIBRARIES_NOTFOUND AND NOT AQSIS_ZLIB_INCLUDE_NOTFOUND)
	SET(AQSIS_ZLIB_FOUND 1)
ENDIF(NOT AQSIS_ZLIB_LIBRARIES_NOTFOUND AND NOT AQSIS_ZLIB_INCLUDE_NOTFOUND)

