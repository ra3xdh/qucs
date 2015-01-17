/***************************************************************************
                           abstractspicekernel.h
                             ----------------
    begin                : Sat Jan 10 2014
    copyright            : (C) 2014 by Vadim Kuznetsov
    email                : ra3xdh@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/



#ifndef ABSTRACTSPICEKERNEL_H
#define ABSTRACTSPICEKERNEL_H

#include <QtCore>
#include "schematic.h"

class AbstractSpiceKernel : public QObject
{
    Q_OBJECT
private:
    void normalizeVarsNames(QStringList &var_list);

protected:
    QString netlist,workdir, simulator_cmd,
            simulator_parameters, output;
    QProcess *SimProcess;

    QStringList sims,vars,output_files;


    Schematic *Sch;

    virtual void createNetlist(QTextStream& stream, int NumPorts,QStringList& simulations,
                               QStringList& vars, QStringList &outputs);

public:

    explicit AbstractSpiceKernel(Schematic *sch_, QObject *parent = 0);
    ~AbstractSpiceKernel();

    void parseNgSpiceSimOutput(QString ngspice_file,
                          QList< QList<double> > &sim_points,
                          QStringList &var_list, bool &isComplex);
    void convertToQucsData(const QString &qucs_dataset);
    QString getOutput();

    
signals:
    void started();
    void finished();
    void errors(QProcess::ProcessError);

protected slots:
    virtual void slotFinished();

public slots:
    virtual void slotSimulate();
    void killThemAll();
    void slotErrors(QProcess::ProcessError err);
    
};

#endif // ABSTRACTSPICEKERNEL_H
