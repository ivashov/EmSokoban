#include "test.hpp"

#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
#include <random>

using namespace SGen;

Point::Point(int _x, int _y)
    : x(_x), y(_y)
{
}

Map::Map(int _w, int _h)
    : w(_w), h(_h),
    lines(0),
    pushes(0),
    arr(new int[w * h]),
    hash(0)
{
}

Map::Map(Map* _map)
    : w(_map->w),
    h(_map->h),
    lines(_map->lines),
    pushes(_map->pushes),
    arr(new int[w * h]),
    hash(0)
{
    std::copy(_map->arr, _map->arr + w * h, arr);
    crates = _map->crates;
}

Map::~Map() {
    delete arr;
}

void Map::setCrateCount(int count) {
    crates.reserve(count);
}

void Map::addCrate(int x, int y) {
    crates.push_back(Point(x, y));
}

bool Map::isInner(int x, int y) const {
    return x >= 0 && y >= 0 && x < w && y < h;
}

bool Map::isFree(int x, int y) const {
    assert(isInner(x, y));

    return isInner(x, y) && !is(x, y, WALL) && !is(x, y, CRATE);
}

void Map::set(int x, int y, int flag) {
    assert(isInner(x, y));

    get(x, y) |= flag;
}

void Map::clear(int x, int y, int flag) {
    assert(isInner(x, y));

    get(x, y) &= ~flag;
}

bool Map::is(int x, int y, int flag) const {
    assert(isInner(x, y));

    return (get(x, y) & flag) != 0;
}

void Map::commit() {
    int hash = 1;
    for (int i = 0; i < w * h; i++) {
        hash = 31 * hash + arr[i];
    }
    this->hash = hash;
}

int Map::hashCode() const {
    return hash;
}

void Map::flood(int sx, int sy) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            clear(x, y, REACH);
        }
    }

    std::queue<Point> queue;
    queue.push(Point(sx, sy));

    while (!queue.empty()) {
        Point p = queue.back();
        queue.pop();

        if (isInner(p.x, p.y)) {
            int f = get(p.x, p.y);

            if ((f & WALL) == 0 && (f & REACH) == 0 && (f & CRATE) == 0) {
                // Expand point
                queue.push(Point(p.x + 1, p.y));
                queue.push(Point(p.x - 1, p.y));
                queue.push(Point(p.x, p.y + 1));
                queue.push(Point(p.x, p.y - 1));

                set(p.x, p.y, REACH);
            }
        }
    }
}

int Map::value() const {
    int value;

    for (int i = 0; i < w * h; i++) {
        if ((arr[i] & (CRATE | END)) != 0) {
            value -= 200;
        }
    }

    return value + 100 * (pushes + 4 * lines - 12 * crates.size());
}

bool Map::applyTemplate(int x0, int y0, const char* templ) {
    if (tryApplyTemplate(x0, y0, templ, false)) {
        tryApplyTemplate(x0, y0, templ, true);
    }
}

bool Map::tryApplyTemplate(int x0, int y0, const char* templ, bool dryRun) {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            char c = templ[x + y * 5];

            int xx = x + x0;
            int yy = y + y0;

            if (!isInner(xx, yy))
                continue;

            if (c == '#') {
                if (is(xx, yy, FLOOR)) {
                    return false;
                }
                if (!dryRun) {
                    set(xx, yy, WALL);
                }
            } else if (c == '.') {
                if (is(xx, yy, WALL)) {
                    return false;
                }
                if (!dryRun) {
                    set(xx, yy, FLOOR);
                }
            }
        }
    }

    return true;
}

namespace SGen {
    class SGenMainPrivate {
    public:
        std::mt19937 r;
    };
}

SGenMain::SGenMain() {
    d = new SGenMainPrivate;

    std::random_device rd;
    d->r.seed(rd());
}

SGenMain::~SGenMain() {
    delete d;
}

Map* SGenMain::generateMap(int w, int h) {
    Map* map = nullptr;
    do {
        delete map;
        map = tryGenerateMap(w, h);
    } while (!validate(map, w, h));

    return map;
}

Map* SGenMain::tryGenerateMap(int w, int h) {

}

bool SGenMain::validate(Map* map) {

}

const char* helloworld(void) {
    return "Hello from c code!";
}
