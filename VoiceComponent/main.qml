import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

ApplicationWindow {
    visible: true
    width: 300
    height: 200
    title: "Voice Recorder"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Label {
            id: statusLabel
            text: "Stopped"
            font.pixelSize: 18
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
            id: timerLabel
            text: "00:00"
            font.pixelSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: recordButton
                text: "Record"
                onClicked: {
                    if (statusLabel.text === "Stopped") {
                        audioRecorder.startRecording();
                    } else {
                        audioRecorder.stopRecording();
                    }
                }
            }

            Button {
                id: saveButton
                text: "Save"
                onClicked: {
                    audioRecorder.saveRecording();
                }
            }
        }
    }

    Connections {
        target: audioRecorder
        onRecordingStateChanged: {
            statusLabel.text = state;
            if (state === "Stopped") {
                timerLabel.text = "00:00";
            }
        }
        onRecordingTimeChanged: {
            timerLabel.text = time;
        }
    }
}
