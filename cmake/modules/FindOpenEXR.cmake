SET(AQSIS_OPENEXR_FOUND 0)

SET(AQSIS_OPENEXR_INCLUDE_SEARCHPATH)

IF(WIN32)
	IF(AQSIS_WIN32LIBS)
		SET(AQSIS_OPENEXR_INCLUDE_SEARCHPATH ${AQSIS_OPENEXR_INCLUDE_SEARCHPATH} ${AQSIS_WIN32LIBS}/OpenEXR/include)
		IF(MSVC AND MSVC80)
			SET(AQSIS_OPENEXR_LIBRARIES_DIR ${AQSIS_WIN32LIBS}/OpenEXR/lib/vc8_sp1 CACHE PATH "Semi-colon separated list of paths to search for OpenEXR libraries")
		ELSEIF(MSVC AND MSVC90)
			SET(AQSIS_OPENEXR_LIBRARIES_DIR ${AQSIS_WIN32LIBS}/OpenEXR/lib/vc9_sp1 CACHE PATH "Semi-colon separated list of paths to search for OpenEXR libraries")
		ELSE(MSVC AND MSVC80)
			IF(MINGW)
				SET(AQSIS_OPENEXR_LIBRARIES_DIR ${AQSIS_WIN32LIBS}/OpenEXR/lib/mingw CACHE PATH "Semi-colon separated list of paths to search for OpenEXR libraries")
			ENDIF(MINGW)
		ENDIF(MSVC AND MSVC80)
	ENDIF(AQSIS_WIN32LIBS)
	if(MINGW)
		LIST(APPEND AQSIS_OPENEXR_INCLUDE_SEARCHPATH ${AQSIS_DEPENDENCIES}/include/OpenEXR)
		LIST(APPEND AQSIS_OPENEXR_LIBRARIES_DIR ${AQSIS_DEPENDENCIES}/lib)
	endif()
ELSE(WIN32)
	SET(AQSIS_OPENEXR_LIBRARIES_DIR "" CACHE PATH "Semi-colon separated list of paths to search for openexr libraries")
	IF(NOT APPLE)
		SET(AQSIS_OPENEXR_INCLUDE_SEARCHPATH /usr/include /usr/local/include)
	ELSE(NOT APPLE)
		SET(AQSIS_OPENEXR_INCLUDE_SEARCHPATH /opt/home/include)
	ENDIF(NOT APPLE)
ENDIF(WIN32)

FIND_PATH(AQSIS_OPENEXR_INCLUDE_DIR
			OpenEXR/Iex.h
			PATHS ${AQSIS_OPENEXR_INCLUDE_SEARCHPATH}
			PATH_SUFFIXES "" OpenEXR openexr
			DOC "Location of the OpenEXR headers"
			)

FIND_LIBRARY(AQSIS_OPENEXR_LIBRARY
      NAMES OpenEXR 
			PATHS ${AQSIS_OPENEXR_LIBRARIES_DIR}
			DOC "Location of the OpenEXR library"
			)
MARK_AS_ADVANCED(AQSIS_OPENEXR_LIBRARY)
FIND_LIBRARY(AQSIS_IEX_LIBRARY
			NAMES Iex
			PATHS ${AQSIS_OPENEXR_LIBRARIES_DIR}
			DOC "Location of the Iex OpenEXR library"
			)
MARK_AS_ADVANCED(AQSIS_IEX_LIBRARY)
FIND_LIBRARY(AQSIS_IMATH_LIBRARY
			NAMES Imath
			PATHS ${AQSIS_OPENEXR_LIBRARIES_DIR}
			DOC "Location of the Imath OpenEXR library"
			)
MARK_AS_ADVANCED(AQSIS_IMATH_LIBRARY)
FIND_LIBRARY(AQSIS_ILMTHREAD_LIBRARY
			NAMES IlmThread
			PATHS ${AQSIS_OPENEXR_LIBRARIES_DIR}
			DOC "Location of the IlmThread OpenEXR library"
			)
MARK_AS_ADVANCED(AQSIS_ILMTHREAD_LIBRARY)

STRING(COMPARE EQUAL "${AQSIS_OPENEXR_INCLUDE_DIR}" "AQSIS_OPENEXR_INCLUDE-NOTFOUND" AQSIS_OPENEXR_INCLUDE_NOTFOUND)
STRING(COMPARE EQUAL "${AQSIS_OPENEXR_LIBRARY}" "AQSIS_OPENEXR_LIBRARY-NOTFOUND" AQSIS_OPENEXR_LIBRARY_NOTFOUND)
STRING(COMPARE EQUAL "${AQSIS_IEX_LIBRARY}" "AQSIS_IEX_LIBRARY-NOTFOUND" AQSIS_IEX_LIBRARY_NOTFOUND)
STRING(COMPARE EQUAL "${AQSIS_IMATH_LIBRARY}" "AQSIS_IMATH_LIBRARY-NOTFOUND" AQSIS_IMATH_LIBRARY_NOTFOUND)
STRING(COMPARE EQUAL "${AQSIS_ILMTHREAD_LIBRARY}" "AQSIS_ILMTHREAD_LIBRARY-NOTFOUND" AQSIS_ILMTHREAD_LIBRARY_NOTFOUND)

IF(NOT AQSIS_OPENEXR_LIBRARY_NOTFOUND AND NOT 
		AQSIS_IEX_LIBRARY_NOTFOUND AND NOT
		AQSIS_IMATH_LIBRARY_NOTFOUND AND NOT
		AQSIS_OPENEXR_INCLUDE_NOTFOUND)
  SET(AQSIS_OPENEXR_LIBRARIES ${AQSIS_OPENEXR_LIBRARY} ${AQSIS_IEX_LIBRARY} ${AQSIS_IMATH_LIBRARY} CACHE STRING "OpenEXR libraries")
	MARK_AS_ADVANCED(AQSIS_OPENEXR_LIBRARIES)
	SET(AQSIS_OPENEXR_FOUND 1)
ENDIF(NOT AQSIS_OPENEXR_LIBRARY_NOTFOUND AND NOT 
		AQSIS_IEX_LIBRARY_NOTFOUND AND NOT
		AQSIS_IMATH_LIBRARY_NOTFOUND AND NOT
		AQSIS_OPENEXR_INCLUDE_NOTFOUND)
# It's ok not to be able to find IlmThread, as 1.2 and before didn't have that as a separate library.
IF(NOT AQSIS_ILMTHREAD_LIBRARY_NOTFOUND)
	SET(AQSIS_OPENEXR_LIBRARIES ${AQSIS_OPENEXR_LIBRARIES} ${AQSIS_ILMTHREAD_LIBRARY})
ENDIF(NOT AQSIS_ILMTHREAD_LIBRARY_NOTFOUND)

