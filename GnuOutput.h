#ifndef GNU_OUTPUT
#define GNU_OUTPUT

#include "gnuplot-iostream.h"
#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <sys/time.h>
#include <unordered_map>
#include <ProjGaia/Tools/Coord.h>
#include <ProjGaia/Tools/LineSeg.h>

namespace pg {

struct Color{

};

struct Point : public Coord{

};
struct Line: public LineSeg{

};


class Plotter {
public:
    Plotter();
    void addPoint(std::string index, Point);
    void plot2d();

protected:
    double minX = 0, minY = 0, maxY = 1, maxX = 1;
     double var = 1.1;
    bool upRange = false;
    long long lastT = 0;

    using DataSet = std::vector<std::vector<double>>;
    std::unordered_map<std::string ,std::vector<Point> > points;
    std::unordered_map<std::string ,std::vector<Line> > lines;

    void  checkPoints(double& x, double& y);
    void updateRange();
    void drawLine();
    DataSet squish(DataSet& p) ;
    void drawPoint();
    Gnuplot gp;



};

}
#endif // GNU_OUTPUT
