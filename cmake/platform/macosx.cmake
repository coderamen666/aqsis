SET(BINDIR "bin" 
	CACHE STRING "Install location for binary files. (relative to CMAKE_INSTALL_PREFIX)")
SET(LIBDIR "lib" 
	CACHE STRING "Install location for shared libraries (relative to CMAKE_INSTALL_PREFIX)")
SET(RENDERENGINEDIR "${LIBDIR}" 
	CACHE STRING "Install location for render dependent shared libraries (relative to CMAKE_INSTALL_PREFIX)")
SET(DISPLAYSDIR "${LIBDIR}/aqsis" 
	CACHE STRING "Install location for display libraries (relative to CMAKE_INSTALL_PREFIX)")
SET(PLUGINDIR "${LIBDIR}/aqsis/plugins" 
	CACHE STRING "Install location for plugin libraries (relative to CMAKE_INSTALL_PREFIX)")
SET(STATICLIBDIR "${LIBDIR}/aqsis" 
	CACHE STRING "Install location for static libraries (relative to CMAKE_INSTALL_PREFIX)")
SET(SHADERDIR "share/aqsis/shaders" 
	CACHE STRING "Install location for shaders (relative to CMAKE_INSTALL_PREFIX)")
SET(SYSCONFDIR "etc/aqsis" 
	CACHE STRING "Install location for system configuration files (relative to CMAKE_INSTALL_PREFIX)")
SET(INCLUDEDIR "include/aqsis" 
	CACHE STRING "Install location for aqsis header files (relative to CMAKE_INSTALL_PREFIX)")
SET(CONTENTDIR "content" 
	CACHE STRING "Install location for content (relative to CMAKE_INSTALL_PREFIX)")
SET(SCRIPTSDIR "scripts" 
	CACHE STRING "Install location for scripts (relative to CMAKE_INSTALL_PREFIX)")

IF(AQSIS_USE_PLUGINS)
	SET(AQSISEXE_SYSTEM_LINKLIBS ${AQSIS_SYSTEM_LINKLIBS} dl)
	SET(TEQSER_SYSTEM_LINKLIBS ${TEQSER_SYSTEM_LINKLIBS} dl)
	SET(AQSL_SYSTEM_LINKLIBS ${AQSL_SYSTEM_LINKLIBS} dl)
	SET(AQSLTELL_SYSTEM_LINKLIBS ${AQSLTELL_SYSTEM_LINKLIBS} dl)
ENDIF(AQSIS_USE_PLUGINS)

# Ensure that the Carbons libraries are found and used appropriately
INCLUDE_DIRECTORIES ( /Developer/Headers/FlatCarbon )
FIND_LIBRARY(CARBON_LIBRARY Carbon)
#FIND_LIBRARY(QUICKTIME_LIBRARY QuickTime )
FIND_LIBRARY(APP_SERVICES_LIBRARY ApplicationServices )
MARK_AS_ADVANCED (CARBON_LIBRARY)
#MARK_AS_ADVANCED (QUICKTIME_LIBRARY)
MARK_AS_ADVANCED (APP_SERVICES_LIBRARY)

SET(AQSISLIB_SYSTEM_LINKLIBS ${AQSISLIB_SYSTEM_LINKLIBS} ${CARBON_LIBRARY}) 
SET(AQSIS_DISPLAY_SYSTEM_LINKLIBS ${AQSIS_DISPLAY_SYSTEM_LINKLIBS} ${CARBON_LIBRARY}) 
SET(AQSIS_PIQSL_SYSTEM_LINKLIBS ${AQSIS_PIQSL_SYSTEM_LINKLIBS} ${CARBON_LIBRARY}) 
