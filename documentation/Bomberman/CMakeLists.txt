find_package(Doxygen)
if (DOXYGEN_FOUND)
    doxygen_add_docs(
            doxygen_bomberman
            ${PROJECT_SOURCE_DIR}/Bomberman
            ALL
    )
endif (DOXYGEN_FOUND)