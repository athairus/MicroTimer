#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QTimer>

#include "microtimer.h"
#include "timelistener.h"

int main( int argc, char *argv[] ) {
    QGuiApplication app( argc, argv );

    QQmlApplicationEngine engine;
    engine.load( QUrl( QStringLiteral( "qrc:/main.qml" ) ) );

    // Testing showed signals started to drop in OS X 10.11 beyond 400Hz
    qreal freq = 60.0 * 1000.0 / 1001.0; // ~59.94 (NTSC)
    qreal msec = 1000.0 / freq;

    QThread listenerThread;
    QThread microTimerThread;

    // Cleanly quit threads once app is closed
    QObject::connect( &app, &QCoreApplication::aboutToQuit, [ & ]() {
        listenerThread.quit();
        listenerThread.wait();
        microTimerThread.quit();
        microTimerThread.wait();
    } );

    TimeListener timeListener( freq );

    // Our custom timer class
    MicroTimer microTimer;
    QObject::connect( &microTimer, &MicroTimer::timeout, &timeListener, &TimeListener::printStatistics );

    // Set maxAccuracy here, causes heavy CPU usage when on
    // microTimer.setProperty( "maxAccuracy", true );

    // Make sure the internal timers are properly killed before ending thread
    QObject::connect( &microTimerThread, &QThread::finished, &microTimer, &MicroTimer::killTimers );

    // A standard QTimer for comparison
    QTimer timer;
    timer.setTimerType( Qt::PreciseTimer );
    QObject::connect( &timer, &QTimer::timeout, &timeListener, &TimeListener::printStatistics );

    // Only run one at a time
    microTimer.start( msec );
    //timer.start( msec );

    timeListener.moveToThread( &listenerThread );
    microTimer.moveToThread( &microTimerThread );
    listenerThread.start();
    microTimerThread.start();

    return app.exec();
}
