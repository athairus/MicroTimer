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

#include "timelistener.h"

#include <QDateTime>
#include <QDebug>
#include <QQueue>

TimeListener::TimeListener( qreal frequency, QObject *parent ) : QObject( parent ) {
    this->frequency = frequency;
}

void TimeListener::printStatistics() {
    // Print this many times per second
    // The more often you print, the less reliable the results due to overhead
    // 1 or less recommended
    static qreal perSecond = 2;

    // Use the average of the last __ print statements' data to determine the rolling average
    static qreal rollingAverageSeconds = 10;

    // Don't modify the stuff below (or do... I'm a comment not a cop)
    static qreal rollingAverageTurnover = perSecond * rollingAverageSeconds;
    static int mod = frequency / perSecond;
    static int modCounter = 1;
    static qreal runningTotalHz = 0;
    static QQueue<qreal> numbersQueue;
    static qreal numbersQueueSum = 0;

    if( !timer.isValid() ) {
        timer.start();
    }

    // Print statistics every (mod) calls to this function
    if( modCounter % mod == 0 ) {
        qreal time = ( qreal )timer.nsecsElapsed();
        timer.restart();
        qreal currentFreq = 1.0 / ( time / ( ( qreal )mod * 1000000000.0 ) );
        numbersQueueSum += currentFreq;
        numbersQueue.enqueue( currentFreq );

        // Start removing old entries once past the first __ print statements
        if( numbersQueue.size() > rollingAverageTurnover ) {
            numbersQueueSum -= numbersQueue.dequeue();
        }

        runningTotalHz += currentFreq;
        qreal averageHz = ( qreal )runningTotalHz / modCounter * mod;
        qreal averageMs = 1000.0 / averageHz;

        qreal deltaHz = qAbs( currentFreq - frequency );
        qreal deltaUs = qAbs( ( 1000000.0 / currentFreq ) - ( 1000000.0 / frequency ) );

        qreal rollingAverageHz = numbersQueueSum / numbersQueue.size();
        qreal rollingAverageMs = 1000.0 / rollingAverageHz;
        QString rollingAverageString( "---" );

        qreal rollingDeltaHz = qAbs( rollingAverageHz - frequency );
        qreal rollingDeltaUs = qAbs( ( 1000000.0 / rollingAverageHz ) - ( 1000000.0 / frequency ) );
        QString rollingDeltaString( "---" );

        if( numbersQueue.size() >= rollingAverageTurnover ) {
            rollingAverageString = QString( "%1Hz/%2ms" ).arg( rollingAverageHz ).arg( rollingAverageMs );
            rollingDeltaString = QString( "%1Hz/%2us" ).arg( rollingDeltaHz ).arg( rollingDeltaUs );
        }

        qDebug().nospace().noquote()
                << "last " << ( perSecond != 1 ? QString( "%1 seconds: " ).arg( 1.0 / perSecond ) : QString( "second: " ) )
                << currentFreq << "Hz/" << 1000 / currentFreq << "ms, "
                << "session average: " << averageHz << "Hz/" << averageMs << "ms, "
                << "rolling average (" << rollingAverageTurnover / perSecond << "s): " << rollingAverageString << ", "
                << "delta: " << deltaHz << "Hz/" << deltaUs << "us, "
                << "rolling delta (" << rollingAverageTurnover / perSecond << "s): " << rollingDeltaString << " ";
    }

    modCounter++;
}
