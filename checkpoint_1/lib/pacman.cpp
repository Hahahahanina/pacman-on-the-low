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

Ghosts::Ghosts(int count) {
    for (int i = 0; i < count; ++i) {
        ghost_.push_back(Ghost(rand() % 30));
    }
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
    std::cout << "Enter ghosts count:" << '\n';
    int count;
    std::cin >> count;
    Ghosts ghosts(count);
    return ghosts;
}

void Game::startGame() {
    createObjects();
    playGame();
}

void Game::tryMove(int x, int y, bool &b, bool &ifTunnel) {
    if (map.map_[x][y].tag == POINT) {
        ++player.points;
        map.map_[x][y] = MapObject(x, y);
    } else if (map.map_[x][y].tag == FENCE) {
        b = 0;
    } else if (map.map_[x][y].tag == TUNNEL) {
        ifTunnel = 1;
    } else if (map.map_[x][y].tag == COMMON) {

    }
}

void Game::ghostsMoveToTarget(int x, int y) {
    for (int i = 0; i < ghosts.ghost_.size(); ++i) {
        if (ghosts.ghost_[i].appearanceTime <= time) {
            if (x > ghosts.ghost_[i].x) {
                ++ghosts.ghost_[i].x;
            } else if (x < ghosts.ghost_[i].x) {
                --ghosts.ghost_[i].x;
            }

            if (y > ghosts.ghost_[i].y) {
                ++ghosts.ghost_[i].y;
            } else if (y < ghosts.ghost_[i].y) {
                --ghosts.ghost_[i].y;
            }
        }
    }
}

void Game::playGame() {
    int x = 1;
    int y = 1;
    while (player.healthPoints > 0) {
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


        for (int i = 0; i < ghosts.ghost_.size(); ++i) {
            if (ghosts.ghost_[i].x == x && ghosts.ghost_[i].y == y) {
                --player.healthPoints;
                std::cout << "You lost 1HP" << '\n';
                x = 1;
                y = 1;
                time = 0;
            }
        }

        if (player.points == MAX_POINT_COUNT) {
            std::cout << "You win!" << '\n';
            break;
        }
    }
}

void Game::createObjects() {
    player = Creator::createPlayer();
    map = Creator::createMap();
    time = 0;
    ghosts = Creator::createGhosts();
}