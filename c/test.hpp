#pragma once

#include <vector>

namespace SGen {
    class Point {
    public:
        int x, y;

    public:
        Point(int x, int y);
    };

    class Map {
    public:
        static const int FLOOR = 0;

        static const int WALL = 1;
        static const int CRATE = 2;

        static const int END = 4;
        static const int REACH = 8;

        static const int VOID = 16;

        int w, h;

        int lines;
        int pushes;

        std::vector<Point> crates;
        int* arr;

        int hash;

    public:
        Map(int w, int h);
        Map(Map* map);
        ~Map();

        void setCrateCount(int count);
        void addCrate(int x, int y);
        void flood(int x, int y);

        bool isInner(int x, int y) const;
        bool isFree(int x, int y) const;

        void set(int x, int y, int flag);
        void clear(int x, int y, int flag);
        bool is(int x, int y, int flag) const;

        void commit();
        int hashCode() const;

        int value() const;
        bool applyTemplate(int x0, int y0, const char* templ);

    private:
        int& get(int x, int y) const {
            return arr[y + x * h];
        }

        bool tryApplyTemplate(int x0, int y0, const char* templ, bool dryRun);
    };

    class SGenMainPrivate;
    class SGenMain {
        SGenMainPrivate* d;

    public:
        SGenMain();
        ~SGenMain();

        Map* generateMap(int w, int h);
        Map* tryGenerateMap(int w, int h);

        bool validate(Map* map);
    };
}
