target_sources(${PROJECT_NAME}-Bomberman PRIVATE
        ECSHandler.cpp ECSHandler.hpp
        Entity.hpp
        EntityManager.cpp EntityManager.hpp
        ComponentManager.cpp ComponentManager.hpp
        IComponentStore.hpp
        System.hpp
        SystemManager.cpp SystemManager.hpp
        Exception.cpp Exception.hpp
        )

add_subdirectory(Components)
target_include_directories(${PROJECT_NAME}-Bomberman PRIVATE Components)

add_subdirectory(Systems)
target_include_directories(${PROJECT_NAME}-Bomberman PRIVATE Systems)