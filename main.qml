import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: window;
    visible: true;

    // Component.onCompleted: flags = flags | Qt.WindowFullscreenButtonHint;

    width: 600;
    height: 300;

    minimumWidth: 600;
    minimumHeight: 300;

    onWidthChanged: {
        leftAnimation.to = window.width - rectangle1.width;
        animation.restart();
    }

    MouseArea {
        anchors.fill: parent;
        onClicked: {
            toggleFullscreen();
        }
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

    // Simple rectangle that moves from side to side
    Rectangle {
        id: rectangle1;
        x: 0;
        y: 200;
        width: 50;
        height: 50;
        color: "#ff0000";

        SequentialAnimation on x {
            id: animation;
            loops: Animation.Infinite;

            // Reset the position if the animation was restarted partway through
            ScriptAction { script: if( rectangle1.x != 0 ) rectangle1.x = 0; }

            PropertyAnimation { id: leftAnimation; to: window.width - rectangle1.width; duration: 2000; }
            PropertyAnimation { id: rightAnimation; to: 0; duration: 2000; }
        }
    }

    function toggleFullscreen() {
        if( window.visibility === Window.FullScreen )
            window.visibility = Window.Windowed;
        else if( window.visibility & ( Window.Windowed | Window.Maximized ) )
            window.visibility = Window.FullScreen;
    }
}
