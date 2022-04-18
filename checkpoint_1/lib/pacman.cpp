#include "pacman.h"

Map::Map(std::string fileName) {
    std::ifstream file;
    file.open(fileName);
    for (int i = 0; i < MAP_SIZE; ++i) {
        std::vector<MapObject> current;
        for (int j = 0; j < MAP_SIZE; ++j) {
            char c;
            file >> c;
            if (c == 'p') {
                current.push_back(Point(i, j));
            } else if (c == 'f') {
                current.push_back(Fence(i, j));
            } else if (c == 't') {
                current.push_back(Tunnel(i, j));
            } else {
                current.push_back(MapObject(i, j));
            }
        }
        map_.push_back(current);
    }
    file.close();
}

Player Creator::createPlayer() {
    std::cout << "Enter your nickname:" << '\n';
    std::string nickname;
    std::cin >> nickname;
    Player player(nickname);
    return player;
}

Map Creator::createMap() {
    std::string fileName = "map.txt";
    Map map(fileName);
    return map;
}

Ghosts Creator::createGhosts() {
    Ghosts ghosts(GHOSTS_COUNT);
    return ghosts;
}

void Game::startGame() {
    createObjects();
    playGame();
}

void Game::tryMove(int x, int y, bool &b, bool &ifTunnel) {
    if (map.getTag(x, y) == POINT) {
        player.addPoints();
        map.eatPoint(x, y);
    } else if (map.getTag(x, y) == FENCE) {
        b = 0;
    } else if (map.getTag(x, y) == TUNNEL) {
        ifTunnel = 1;
    } else if (map.getTag(x, y) == COMMON) {

    }
}

void Game::ghostsMoveToTarget(int x, int y) {
    for (int i = 0; i < GHOSTS_COUNT; ++i) {
        if (ghosts[i].getAppearanceTime() <= time) {
            if (x > ghosts[i].getXCoordinate()) {
                ghosts[i].moveRight();
            } else if (x < ghosts[i].getXCoordinate()) {
                ghosts[i].moveLeft();
            }

            if (y > ghosts[i].getYCoordinate()) {
                ghosts[i].moveTop();
            } else if (y < ghosts[i].getYCoordinate()) {
                ghosts[i].moveBottom();
            }
        }
    }
}

void Game::playGame() {
    int x = 1;
    int y = 1;
    while (player.getHealthPoints() > 0) {
        ++time;
        char c;
        std::cin >> c;
        bool b = 1;
        bool ifTunnel = 0;
        if (c == 'd') {
            tryMove(x, y + 1, b, ifTunnel);
            if (b) {
                ++y;
            }
            if (ifTunnel) {
                y = 0;
            }
        } else if (c == 'a') {
            tryMove(x, y - 1, b, ifTunnel);
            if (b) {
                --y;
            }
            if (ifTunnel) {
                y = MAP_SIZE - 1;
            }
        } else if (c == 's') {
            tryMove(x - 1, y, b, ifTunnel);
            if (b) {
                --x;
            }
        } else if (c == 'w') {
            tryMove(x + 1, y, b, ifTunnel);
            if (b) {
                ++x;
            }
        }

        if (time % 2 == 0) {
            ghostsMoveToTarget(x, y);
        }


        for (int i = 0; i < GHOSTS_COUNT; ++i) {
            if (ghosts[i].getXCoordinate() == x && ghosts[i].getYCoordinate() == y) {
                player.decreaseHealthPoints();
                std::cout << "You lost 1HP" << '\n';
                x = 1;
                y = 1;
                time = 0;
            }
        }

        if (player.getPoints() == MAX_POINT_COUNT) {
            std::cout << "You win!" << '\n';
            break;
        }

        if (player.getHealthPoints() == 0) {
            std::cout << "You lost(" << '\n';
        }
    }
}

void Game::createObjects() {
    player = Creator::createPlayer();
    map = Creator::createMap();
    time = 0;
    ghosts = Creator::createGhosts();
}