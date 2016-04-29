import QtQuick 2.5
import QtQuick.Window 2.2
import test 1.0

Window {
    id: window;
    visible: true;

    // Component.onCompleted: flags = flags | Qt.WindowFullscreenButtonHint;

    width: 600;
    height: 300;

    minimumWidth: 600;
    minimumHeight: 300;

    MouseArea {
        anchors.fill: parent;
        onClicked: {
            toggleFullscreen();
        }
    }

    TestItem {
        id: testItem;
        anchors.fill: parent;
    }

    Text {
        text: qsTr( "Click this window over and over and watch the timer's accuracy drop..." );
        color: "white";
        anchors.centerIn: parent;
    }

    Shortcut {
        autoRepeat: false;
        sequence: StandardKey.FullScreen;
        onActivated: toggleFullscreen();
    }

    Shortcut {
        autoRepeat: false;
        sequence: "Alt+Return";
        onActivated: toggleFullscreen();
    }

    function toggleFullscreen() {
        if( window.visibility === Window.FullScreen )
            window.visibility = Window.Windowed;
        else if( window.visibility & ( Window.Windowed | Window.Maximized ) )
            window.visibility = Window.FullScreen;
    }
}
