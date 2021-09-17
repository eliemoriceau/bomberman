//
// Created by marin on 14/06/2021.
//

#pragma once

#include <vector>
#include "list"
#include "VectorUtils.hpp"
#include "Vector3.hpp"
#include "Texture.hpp"
#include "Color.hpp"
#include "DefineResources.hpp"
#include "ECSHandler.hpp"
#include "Entity.hpp"
#include <list>
#include "EntityCreator.hpp"
#include "Vector2.hpp"
#include <random>
#include <istream>
#include <fstream>
#include <string>
#include <iostream>
#include "TransformComponent.hpp"
#include <algorithm>
#include "TransformComponent.hpp"


class MapManager {
public:
    ~MapManager() = default;

    static MapManager *getInstance();

    std::vector<std::vector<char>> getMap2D();
    std::shared_ptr<Raylib::Vector3> getAvailablePlace(ECS::TransformComponent ai);
    bool checkAvailablePlace(const std::shared_ptr<Raylib::Vector3>& pos);
    std::shared_ptr<Raylib::Vector3> getGridPosition(const std::shared_ptr<Raylib::Vector3> &pos) const;

    void generateMap(int width, int height, int nb_player, int load);

    void generate3dMapFrom2d();

    void
    generateUnbreakable3D(float x, float y, const std::shared_ptr<Raylib::ColorRGB> &color,
                          const std::string &texture_name,
                          const std::shared_ptr<Raylib::Vector3> &size, float y_offset);

    void
    generateBreakable3D(float x, float y, const std::shared_ptr<Raylib::ColorRGB> &color,
                        const std::string &texture_name,
                        const std::shared_ptr<Raylib::Vector3> &size, float y_offset);

    void addBonus(ECS::Entity entity);


    void generateBorder2D(int x, int y);

    void generateUnbreakable2D(int x, int y);

    void generateBreakable2D(int x, int y);

    void generatePlayer2D();

    void generate2DMap();

    void printGenerate2DMap();

    static int getFileWidth(const std::string &path);

    static int getFileHeight(const std::string &path);

    void loadMap2DfromFile(const std::string &path);

    void saveMap2DtoFile(const std::string &path);

    static bool detectFileExist(const std::string &path);

    bool checkCellType(int x, int y, char type);
    bool checkMapType(char type);

    bool checkCellIsPlayer(int x, int y);

    std::pair<int, int> getArrayCoords(const std::shared_ptr<Raylib::Vector3> &pos) const;

    char getCellType(int x, int y);
    char getCell3DType(const std::shared_ptr<Raylib::Vector3> &pos);
    std::vector<std::pair<int, int>> getTypeList(char type);

    void clearAll();

    std::list<ECS::Entity> getBreakableWalls();

    std::list<ECS::Entity> getUnbreakableWalls();

    std::list<ECS::Entity> getBonus();

    std::map<std::shared_ptr<Raylib::Vector3>, std::tuple<int, int, char>> getSpawnPoints();

    void addSpawnPoint(const std::shared_ptr<Raylib::Vector3> &pos, int x, int y, char id);

    void deleteBreakableWallAtPosition(const std::shared_ptr<Raylib::Vector3> &pos);

    void removeBreakableWall(ECS::Entity entity);

    void deleteBonusAtPosition(const std::shared_ptr<Raylib::Vector3> &pos);

    void removeBonus(ECS::Entity entity);

    void setMapCoordPlayer(int x, int y, char c, char id);

    void setMapCoord(int x, int y, char c);

    int getWidth() const;

    int getHeight() const;

    void addBomb(ECS::Entity entity);

    const std::list<ECS::Entity> &getBombe() const;

    void removeBomb(ECS::Entity entity);

private:
    MapManager() = default;

    int _width{};
    int _height{};
    int _nb_player{};
    std::list<ECS::Entity> _unbreakableWalls;
    std::list<ECS::Entity> _breakableWalls;
    std::list<ECS::Entity> _bonus;
    std::list<ECS::Entity> _bombe;
    std::vector<std::vector<char>> maps2D;
    std::map<std::shared_ptr<Raylib::Vector3>, std::tuple<int, int, char>> _points;
    static MapManager *_instance;

};