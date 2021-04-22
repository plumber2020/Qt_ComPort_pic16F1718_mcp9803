#include "indicatorDGP_form.h"
#include "ui_indicatorDGP_form.h"
#include <QDebug>

IndicatorDGP_Form::IndicatorDGP_Form(QWidget *parent) :
    Indicator(parent),
    ui(new Ui::IndicatorDGP_Form)
{
    ui->setupUi(this);
    m_plot.customPlot = ui->graphPlot;
}

IndicatorDGP_Form::~IndicatorDGP_Form()
{
    delete ui;
}

void IndicatorDGP_Form::make_command(const QString &/*value*/)
{
    emit sendCommand(QString("{DGP}"));
}

void IndicatorDGP_Form::setParams(QStringList const& params)
{
    int i = 0;
    m_measure = params[i++];
    m_unit = params[i++];
    m_min = params[i++].toDouble();
    m_max = params.back().toDouble();

    QCPGraph *graph = m_plot.customPlot->addGraph();
    graph->setPen(QPen(Qt::blue));                      // line color blue for first graph
    graph->setBrush(QBrush(QColor(0, 0, 255, 20)));     // first graph will be filled with translucent blue

    for (; i<params.size()-1; i++) {
        QCPGraph *graph = m_plot.customPlot->addGraph();
        graph->setPen(QPen(Qt::red));                   // line color red for second graph
        m_plot.limits.append(params.at(i).toDouble());
    }

    // give the axes some labels:
    m_plot.customPlot->xAxis->setLabel("count");
    m_plot.customPlot->yAxis->setLabel(QString("%1,%2").arg(m_measure,m_unit));

    // set axes ranges, so we see all data:
    m_plot.customPlot->xAxis->setRange(0, RANGE_X_MAXPOINTS);
    m_plot.customPlot->yAxis->setRange(m_min, m_max);

    m_plot.customPlot->replot();
}

void IndicatorDGP_Form::setValue(const QString &value)
{
    bool ok;
    double data = value.toDouble(&ok);
    if(!ok || data < m_min || data > m_max) data = NAN; //draw not any value

    int graph_count = m_plot.customPlot->graph(0)->dataCount();
    if(graph_count > RANGE_X_MAXPOINTS)
        m_plot.customPlot->xAxis->moveRange(1); //add to the lower and upper bounds of the range


    m_plot.customPlot->graph(0)->addData(graph_count,data);

    for(int i=0;i<m_plot.limits.size();i++) {
        m_plot.customPlot->graph(i+1)->addData(graph_count,m_plot.limits.at(i));
    }

    m_plot.customPlot->replot();
}
