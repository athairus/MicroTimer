/*
 * Copyright © 2016 athairus
 *
 * This file is part of MicroTimer.
 *
 * MicroTimer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <Qt>
#include <QtGlobal>
#include <QObject>
#include <QElapsedTimer>

class TimeListener : public QObject {
        Q_OBJECT

    public:
        explicit TimeListener( qreal frequency, QObject *parent = 0 );

    signals:

    public slots:
        void printStatistics();

    private:
        qreal frequency{ 1.0 };
        QElapsedTimer timer;
        QElapsedTimer looperTimer;
};
