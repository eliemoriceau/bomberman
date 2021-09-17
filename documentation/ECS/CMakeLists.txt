find_package(Doxygen)
if (DOXYGEN_FOUND)
    doxygen_add_docs(
            doxygen_ecs
            ${PROJECT_SOURCE_DIR}/ECS
            ALL
    )
endif (DOXYGEN_FOUND)