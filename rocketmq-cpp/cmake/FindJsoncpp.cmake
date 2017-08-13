include(LibFindMacros)

libfind_pkg_check_modules(JsonCpp_PKGCONF jsoncpp)

find_path(Jsoncpp_INCLUDE_DIR
        NAMES json/features.h
        PATH_SUFFIXES jsoncpp
        PATHS ${JsonCpp_PKGCONF_INCLUDE_DIRS} /usr/local/Cellar/jsoncpp
        )
find_library(Jsoncpp_LIBRARY
        NAMES jsoncpp
        PATHS ${Jsoncpp_PKGCONF_LIBRARY_DIRS})

set(Jsoncpp_PROCESS_INCLUDES Jsoncpp_INCLUDE_DIR)
set(Jsoncpp_PROCESS_LIBS Jsoncpp_LIBRARY)
libfind_process(Jsoncpp)