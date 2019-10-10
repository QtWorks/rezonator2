#ifndef FUNCTION_GRAPH_H
#define FUNCTION_GRAPH_H

#include "../core/CommonTypes.h"
#include "../core/Units.h"

#include <QVector>
#include <QPen>
#include <QMap>

class QCPGraph;
class Plot;
class PlotFunction;

struct GraphUnits
{
    Z::Unit X;
    Z::Unit Y;
};

class FunctionGraph
{
public:
    FunctionGraph(Plot* plot, Z::WorkPlane workPlane, std::function<GraphUnits()> getUnits);

    void clear();
    void update(PlotFunction* function);
    void update(const QList<PlotFunction*>& functions);
    int segmentsCount() const { return _segments.size(); }
    void setFlipped(bool on) { _isFlipped = on; }
    void setVisible(bool on) { _isVisible = on; }
    void setPen(const QPen& pen) { _linePen = pen; }

private:
    Plot* _plot;
    Z::WorkPlane _workPlane;
    std::function<GraphUnits()> _getUnits;
    bool _isFlipped = false;
    bool _isVisible = true;
    QVector<QCPGraph*> _segments;
    QPen _linePen;

    QCPGraph* getOrMakeSegment(int index);
    void fillSegment(QCPGraph* segment, PlotFunction* function, int resultIndex, double offsetX = 0);
    void trimToCount(int count);
};

class FunctionGraphSet
{
public:
    FunctionGraphSet(Plot* plot, std::function<GraphUnits()> getUnits);
    ~FunctionGraphSet();

    void clear();
    void update(PlotFunction* function);
    void update(const QList<PlotFunction*>& functions);
    void update(const QString& id, PlotFunction* function);

    FunctionGraph* T() { return _graphT; }
    FunctionGraph* S() { return _graphS; }

private:
    Plot* _plot;
    std::function<GraphUnits()> _getUnits;
    FunctionGraph *_graphT, *_graphS;
    QMap<QString, FunctionGraph*> _graphs;
};

#endif // FUNCTION_GRAPH_H
