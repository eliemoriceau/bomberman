//
// Created by marin on 14/06/2021.
//

#include <algorithm>
#include "MapManager.hpp"

MapManager *MapManager::_instance = nullptr;

int MapManager::getWidth() const {
    return _width;
}

int MapManager::getHeight() const {
    return _height;
}

MapManager *MapManager::getInstance() {
    if (_instance == nullptr)
        _instance = new MapManager();
    return _instance;
}

std::vector<std::vector<char>> MapManager::getMap2D() {
    return maps2D;
}

std::vector<std::pair<int, int>> MapManager::getTypeList(char type)
{
    std::vector<std::pair<int, int>> list;

    for (int row = 0; row <= this->_height; row++) {
        for (int col = 1; col <= this->_width; col++) {
            if (maps2D[row][col - 1] == type)
                list.push_back({row, col - 1});
        }
    }
    return list;
}

std::shared_ptr<Raylib::Vector3> MapManager::getAvailablePlace(ECS::TransformComponent ai)
{
    std::vector<std::pair<int, int>> list = getTypeList('E');

    for (int row = 0; row <= this->_height; row++) {
        for (int col = 1; col <= this->_width; col++) {
            auto _pos = newVector(-_width/2 + (col - 1),ai.position->getY(),-_height/2 + row);

            for (auto bomb: list)
            {
                auto distance = (float) sqrt(pow(row - bomb.first, 2) + pow((col - 1) - bomb.second, 2));
                if (distance > 3 && maps2D[row][col - 1] == 'O') {
                    return _pos;
                }
            }
        }
    }
    return nullptr;
}


bool MapManager::checkAvailablePlace(const std::shared_ptr<Raylib::Vector3>& pos)
{
    auto checkPos = getArrayCoords(pos);
    std::vector<std::pair<int, int>> list = getTypeList('E');

    for (auto bomb: list)
    {
        auto distance = (float) sqrt(pow(checkPos.first - bomb.first, 2) + pow(checkPos.second - bomb.second, 2));
        if (distance < 3) {
            return false;
        }
    }

    return true;
}

std::shared_ptr<Raylib::Vector3> MapManager::getGridPosition(const std::shared_ptr<Raylib::Vector3> &pos) const {
    auto _min_pos = newVector(0, 0, 0);
    float min_distance = -1;

    for (int row = 0; row <= this->_height; row++) {
        for (int col = 1; col <= this->_width; col++) {
            auto _pos = newVector(-_width / 2 + (col - 1), 1.1f, -_height / 2 + row);
            auto distance = (float) sqrt(
                    pow(pos->x - _pos->x, 2) + pow(pos->y - _pos->y, 2) + pow(pos->z - _pos->z, 2));
            if (min_distance == -1)
                min_distance = distance;
            if (distance < min_distance) {
                _min_pos->setX(_pos->getX());
                _min_pos->setY(_pos->getY());
                _min_pos->setZ(_pos->getZ());
                min_distance = distance;
            }
        }
    }
    return _min_pos;
}

void MapManager::addBonus(ECS::Entity entity) {
    _bonus.push_back(entity);
}

std::list<ECS::Entity> MapManager::getBonus() {
    return _bonus;
}

void MapManager::clearAll() {
    _unbreakableWalls.clear();
    _breakableWalls.clear();
    _bonus.clear();
}

char MapManager::getCellType(int x, int y) {
    return maps2D[x][y];
}

char MapManager::getCell3DType(const std::shared_ptr<Raylib::Vector3> &pos) {
    std::pair<int, int> coords = getArrayCoords(pos);
    return maps2D[coords.first][coords.second];
}

void MapManager::deleteBreakableWallAtPosition(const std::shared_ptr<Raylib::Vector3> &pos) {
    std::vector<ECS::Entity> to_deletes;
    for (auto &entity : _breakableWalls) {
        ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
        auto &transform = ecsHandler->getComponent<ECS::TransformComponent>(entity);
        if (transform.position->x == pos->x && transform.position->z == pos->z) {
            to_deletes.push_back(entity);
        }
    }
    for (auto &entity : to_deletes) {
        removeBreakableWall(entity);
    }
}

void MapManager::removeBreakableWall(ECS::Entity entity) {
    ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    if (std::find(_breakableWalls.begin(), _breakableWalls.end(), entity) != _breakableWalls.end()) {
        ecsHandler->removeEntity(entity);
        _breakableWalls.remove(entity);
    }
}

std::map<std::shared_ptr<Raylib::Vector3>, std::tuple<int, int, char>> MapManager::getSpawnPoints() {
    return _points;
}

void
MapManager::generateUnbreakable3D(float x, float y, const std::shared_ptr<Raylib::ColorRGB> &color,
                                  const std::string &texture_name,
                                  const std::shared_ptr<Raylib::Vector3> &size, float y_offset) {
    auto pos = newVector(-_width / 2 + y, y_offset, -_height / 2 + x);
    _unbreakableWalls.push_back(EntityCreator::createCube(pos, size, color, texture_name, x, y));
}

void
MapManager::generateBreakable3D(float x, float y, const std::shared_ptr<Raylib::ColorRGB> &color,
                                const std::string &texture_name,
                                const std::shared_ptr<Raylib::Vector3> &size, float y_offset) {
    auto pos = newVector(-_width / 2 + y, y_offset, -_height / 2 + x);
    _breakableWalls.push_back(EntityCreator::createCube(pos, size, color, texture_name, x, y));
}

void MapManager::saveMap2DtoFile(const std::string &path) {
    std::ofstream myfile;
    myfile.open(path);

    for (int row = 0; row <= this->_height; row++) {
        for (int col = 1; col <= this->_width; col++) {
            myfile << maps2D[row][col - 1];
        }
        myfile << std::endl;
    }
}

int MapManager::getFileHeight(const std::string &path) {
    std::ifstream file(path);
    std::string str;
    int count = 0;

    if (!file.is_open())
        return (21);

    while (getline(file, str)) {
        count++;
    }
    file.close();
    return count - 1;
}

int MapManager::getFileWidth(const std::string &path) {
    std::ifstream file(path);
    std::string str;
    int count = 0;
    while (getline(file, str)) {
        return strlen(str.c_str());
    }
    file.close();
    return count;
}

void MapManager::loadMap2DfromFile(const std::string &path) {
    std::ifstream file(path);
    std::string str;
    int index = 0;

    this->_width = getFileWidth(path);
    this->_height = getFileHeight(path);

    maps2D.resize(this->_width + 1);
    for (int row = 0; row <= this->_height; row++) {
        maps2D[row].resize(this->_width);
        for (int col = 1; col <= this->_width; col++) {
            maps2D[row][col - 1] = 'O';
        }
    }
    while (std::getline(file, str)) {
        for (int x = 0; str[x]; x++)
            maps2D[index][x] = str[x];
        index++;
    }
}

void MapManager::setMapCoord(int x, int y, char c) {
    maps2D[x][y] = c;
}

void MapManager::setMapCoordPlayer(int x, int y, char c, char id) {
    if (maps2D[x][y] == id && c == 'O') {
        maps2D[x][y] = c;
        return;
    }
    maps2D[x][y] = c;
}

void MapManager::addSpawnPoint(const std::shared_ptr<Raylib::Vector3> &pos, int x, int y, char id) {
    _points.insert(std::pair<std::shared_ptr<Raylib::Vector3>, std::tuple<int, int, char>>(pos, {x, y, id}));
}

std::pair<int, int> MapManager::getArrayCoords(const std::shared_ptr<Raylib::Vector3> &pos) const {
    int y = Clamp(abs((getWidth() - (getWidth() / 2 - pos->x))) - 1, 0, _height);
    int x = Clamp(abs(getHeight() - (getHeight() / 2 - pos->z)) - 1, 0, _width);

    return std::make_pair(x, y);
}

bool MapManager::checkCellType(int x, int y, char type) {
    if (maps2D[x][y] == type)
        return true;

    return false;
}

bool MapManager::checkMapType(char type)
{
    for (int row = 0; row <= this->_height; row++) {
        for (int col = 1; col <= this->_width; col++) {
            if (maps2D[row][col - 1] == 'E')
                return true;
        }
    }

    return false;
}

bool MapManager::checkCellIsPlayer(int x, int y)
{
    if (maps2D[x][y] == '1' || maps2D[x][y] == '2' || maps2D[x][y] == '3' || maps2D[x][y] == '4')
        return true;

    return false;
}

void MapManager::generate3dMapFrom2d() {
    auto color_wall = std::make_shared<Raylib::ColorRGB>(255, 255, 255, 255);
    auto texture_border = WALL_ROCK;
    auto texture_floor = WALL_GRID;
    auto texture_block = WALL_UNBREAKABLE;
    auto texture_break = WALL_WOOD;

    //Generate Floor
    generateUnbreakable3D(_width / 2, _height / 2, color_wall, texture_floor, newVector(_width * 2.5, 1, _height * 2.5),
                          0);

    //Generate all block and spawn points
    for (int row = 0; row <= this->_height; row++) {
        for (int col = 1; col <= this->_width; col++) {
            if (maps2D[row][col - 1] == 'E')
                maps2D[row][col - 1] = 'O';
            if (maps2D[row][col - 1] == 'X')
                generateUnbreakable3D(row, col - 1, color_wall, texture_border, newVector(1, 1, 1), 1);
            if (maps2D[row][col - 1] == 'U')
                generateUnbreakable3D(row, col - 1, color_wall, texture_block, newVector(1, 1, 1), 1);
            if (maps2D[row][col - 1] == 'B')
                generateBreakable3D(row, col - 1, color_wall, texture_break, newVector(1, 1, 1), 1);
            if (maps2D[row][col - 1] == '1' || maps2D[row][col - 1] == '2' || maps2D[row][col - 1] == '3' ||
                maps2D[row][col - 1] == '4')
                addSpawnPoint(newVector(-_width / 2 + (col - 1), 1.1f, -_height / 2 + row), row, col - 1,
                              maps2D[row][col - 1]);
        }
    }
}

bool MapManager::detectFileExist(const std::string &path) {
    std::ifstream i_file;
    i_file.open(path);
    if (i_file)
        return true;
    return false;
}

void MapManager::generateMap(int width, int height, int nb_player, int load) {
    _width = width;
    _height = height;
    _nb_player = nb_player;
    _points.clear();

    if (detectFileExist(SAVE_FILE) && load == 1)
        loadMap2DfromFile(SAVE_FILE);
    else
        generate2DMap();
    generate3dMapFrom2d();
}

std::list<ECS::Entity> MapManager::getBreakableWalls() {
    return _breakableWalls;
}

std::list<ECS::Entity> MapManager::getUnbreakableWalls() {
    return _unbreakableWalls;
}

void MapManager::printGenerate2DMap() {
    for (int row = 0; row <= this->_height; row++) {
        for (int col = 1; col <= this->_width; col++) {
            std::cout << maps2D[row][col - 1];
        }
        std::cout << std::endl;
    }
}

void MapManager::generateBorder2D(int x, int y) {
    if (x == 0)
        maps2D[x][y] = 'X';

    if (x == _height)
        maps2D[x][y] = 'X';

    if (y == _width - 1)
        maps2D[x][y] = 'X';

    if (y == 0)
        maps2D[x][y] = 'X';
}

void MapManager::generateUnbreakable2D(int x, int y) {
    if (maps2D[x][y] == 'O' && y % 2 == 0 && x % 2 == 0)
        maps2D[x][y] = 'U';
}

void MapManager::generateBreakable2D(int x, int y) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if (maps2D[x][y] == 'O' && (gen()) % 3)
        maps2D[x][y] = 'B';
}

void MapManager::generatePlayer2D() {
    for (int row = 0; row <= this->_height; row++) {
        for (int col = 1; col <= this->_width; col++) {
            if (row == 1 && col - 1 == 1) {
                maps2D[row][col - 1] = '1';
                maps2D[row][(col - 1) + 1] = 'O';
                maps2D[row + 1][col - 1] = 'O';
            }
            if (row == 1 && col - 1 == (_width - 2)) {
                maps2D[row][col - 1] = '2';
                maps2D[row][(col - 1) - 1] = 'O';
                maps2D[row + 1][col - 1] = 'O';
            }
            if (row == (_height - 1) && col - 1 == (_width - 2)) {
                maps2D[row][col - 1] = '3';
                maps2D[row][(col - 1) - 1] = 'O';
                maps2D[row - 1][col - 1] = 'O';
            }
            if (row == (_height - 1) && col - 1 == 1) {
                maps2D[row][col - 1] = '4';
                maps2D[row][(col - 1) + 1] = 'O';
                maps2D[row - 1][(col - 1)] = 'O';
            }
        }
    }
}

void MapManager::generate2DMap() {
    maps2D.resize(this->_height + 1);

    for (int row = 0; row <= this->_height; row++) {
        maps2D[row].resize(this->_width);
        for (int col = 1; col <= this->_width; col++) {
            maps2D[row][col - 1] = 'O';
            generateBorder2D(row, col - 1);
            generateUnbreakable2D(row, col - 1);
            generateBreakable2D(row, col - 1);
        }
    }
    generatePlayer2D();
}

void MapManager::deleteBonusAtPosition(const std::shared_ptr<Raylib::Vector3> &pos) {
    std::vector<ECS::Entity> to_deletes;

    for (auto &entity : _bonus) {
        ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
        auto &transform = ecsHandler->getComponent<ECS::TransformComponent>(entity);
        if (transform.position->x == pos->x && transform.position->z == pos->z) {
            to_deletes.push_back(entity);
        }
    }
    for (auto &entity : to_deletes) {
        removeBonus(entity);
    }
}

void MapManager::removeBonus(ECS::Entity entity) {
    ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    if (std::find(_bonus.begin(), _bonus.end(), entity) != _bonus.end()) {
        ecsHandler->removeEntity(entity);
        _bonus.remove(entity);
    }
}

void MapManager::addBomb(ECS::Entity entity) {
    _bombe.push_back(entity);
}

const std::list<ECS::Entity> &MapManager::getBombe() const {
    return _bombe;
}

void MapManager::removeBomb(ECS::Entity entity) {
    ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    if (std::find(_bombe.begin(), _bombe.end(), entity) != _bombe.end()) {
        ecsHandler->removeEntity(entity);
        _bombe.remove(entity);
    }
}