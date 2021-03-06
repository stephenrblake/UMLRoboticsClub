#ifndef OCCUPANCYGRID_H
#define	OCCUPANCYGRID_H

#include "globals.h"
#include "constants.h"
#include "navval.h"
#include "point.h"
#include <vector>

using std::vector;

class OccupancyGrid {
    public:
        OccupancyGrid();
        OccupancyGrid(const OccupancyGrid& orig);
        
        void init();
        void initFakeWorld();
        int update(float realX, float realY, int val);
        int getValue(int x, int y) const;
        int getValue(const Point &point) const; // return array

        const int size;
    private:
        vector<vector<NavVal>> gridVals;
};

#endif
