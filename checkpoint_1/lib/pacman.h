#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const int MAP_SIZE = 15;
const int MAX_POINT_COUNT = 90;

class Player {
public:
    Player() = default;
    explicit Player(std::string nickname_): nickname(nickname_) {};
    int getPoints() {return points;};
    void addPoints() {++points;};
    int getHealthPoints() {return healthPoints;};
    void decreaseHealthPoints() {--healthPoints;};

private:
    std::string nickname = "player1";
    int healthPoints = 5;
    int points = 0;
};

enum MapObjectTag {
    POINT,
    FENCE,
    COMMON,
    TUNNEL
};

class MapObject {
    friend class Map;
public:
    explicit MapObject(int x_, int y_): x(x_), y(y_) {};
protected:
    int x;
    int y;
    MapObjectTag tag = COMMON;
};

class Point: public MapObject {
public:
    Point(int x_, int y_): MapObject(x_, y_)  {
        tag = POINT;
    };
};

class Fence: public MapObject {
public:
    Fence(int x_, int y_): MapObject(x_, y_)  {
        tag = FENCE;
    };
};

class Tunnel: public MapObject {
public:
    Tunnel(int x_, int y_): MapObject(x_, y_)  {
        tag = TUNNEL;
    };
};

class Map {
public:
    Map() = default;
    Map(std::string fileName);
    MapObjectTag getTag(int x, int y);
    void eatPoint(int x, int y);
private:
    std::vector<std::vector<MapObject>> map_;
};

class Ghost {
    friend class Game;
public:
    Ghost() = default;
    Ghost(int time = 0): appearanceTime(time) {};
private:
    int appearanceTime = 0;
    int x = 7;
    int y = 7;
};

class Ghosts {
    friend class Game;
public:
    Ghosts() = default;
    Ghosts(int count);
private:
    std::vector<Ghost> ghost_;
};

class Creator {
    friend class Game;
private:
    static Player createPlayer();
    static Map createMap();
    static Ghosts createGhosts();
};

class Game {
public:
    void startGame();
private:
    Map map;
    Player player;
    size_t time;
    Ghosts ghosts;

    void tryMove(int x, int y, bool &b, bool &ifTunnel);
    void ghostsMoveToTarget(int x, int y);
    void playGame();
    void createObjects();
};