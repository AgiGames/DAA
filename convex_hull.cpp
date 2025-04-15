#include <stdio.h>
#include <set>
#include <math.h>
using namespace std;

struct Point {

    int x, y;

    bool operator < (const Point& referencePoint) const {
        return x < referencePoint.x || (x == referencePoint.x && y < referencePoint.y);
    }

};
typedef struct Point Point;

set<Point> hullPoints;

Point findMinXPoint(Point points[], int n) {

    Point minXPoint = points[0];
    for(int i = 1; i < n; i++) {
        if(points[i].x < minXPoint.x) {
            minXPoint = points[i];
        }
    }
    return minXPoint;

}

Point findMaxXPoint(Point points[], int n) {

    Point maxXPoint = points[0];
    for(int i = 1; i < n; i++) {
        if(points[i].x > maxXPoint.x) {
            maxXPoint = points[i];
        }
    }
    return maxXPoint;

}

int findDistanceFromLine(Point point1, Point point2, Point referencePoint)
{

    return abs ((referencePoint.y - point1.y) *
                (point2.x - point1.x) - (point2.y - point1.y) *
                (referencePoint.x - point1.x));

}
 
int findSide(Point point1, Point point2, Point referencePoint)
{

    int val = (referencePoint.y - point1.y) *
              (point2.x - point1.x) - (point2.y - point1.y) *
              (referencePoint.x - point1.x);
    return 1 * (val > 0) + -1 * (val < 0);

}

void quickHull(Point* points, int n, Point linePoint1, Point linePoint2, int side) {

    int trianglePointIdx = -1;
    int maxDistance = 0;
    for(int i = 0; i < n; i++) {
        int ithDistance = findDistanceFromLine(linePoint1, linePoint2, points[i]);
        if(ithDistance > maxDistance && findSide(linePoint1, linePoint2, points[i]) == side) {
            trianglePointIdx = i;
            maxDistance = ithDistance;
        }
    }

    if(trianglePointIdx == -1) {
        hullPoints.insert(linePoint1);
        hullPoints.insert(linePoint2);
        return;
    }

    quickHull(points, n, linePoint1, points[trianglePointIdx],
              -findSide(linePoint1, points[trianglePointIdx], linePoint2));
    quickHull(points, n, points[trianglePointIdx], linePoint2,
              -findSide(points[trianglePointIdx], linePoint2, linePoint1));

}

void printHull(Point* points, int n) {

    printf("Hull Points:\n");

    Point minXPoint = findMinXPoint(points, n);
    Point maxXPoint = findMaxXPoint(points, n);

    quickHull(points, n, minXPoint, maxXPoint, 1);

    quickHull(points, n, minXPoint, maxXPoint, -1);

    while(!hullPoints.empty()) {
        Point ithPoint = *hullPoints.begin();
        printf("(%d, %d)\n", ithPoint.x, ithPoint.y);
        hullPoints.erase(hullPoints.begin());
    }

}

int main() {

    Point points[] = {
        {12, -34},
        {0, 0},
        {-76, 89},
        {45, 22},
        {-13, -55},
        {67, -44},
        {-90, 12},
        {33, 33},
        {-5, 88},
        {19, -99}
    };
    
    int n = sizeof(points) / sizeof(points[0]);

    printf("Input Points:\n");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", points[i].x, points[i].y);
    }

    printHull(points, n);

    return 0;

}
