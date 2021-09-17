find_package(Doxygen)
if (DOXYGEN_FOUND)
    doxygen_add_docs(
            doxygen_raylibwrapper
            ${PROJECT_SOURCE_DIR}/RaylibWrapper
            ALL
    )
endif (DOXYGEN_FOUND)