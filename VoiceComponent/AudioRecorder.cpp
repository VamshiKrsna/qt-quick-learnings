#include "AudioRecorder.h"
#include <QAudioEncoderSettings>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

AudioRecorder::AudioRecorder(QObject *parent) : QObject(parent), recordingDuration(0) {
    audioRecorder = new QAudioRecorder(this);
    timer = new QTimer(this);

    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/x-wav");
    audioSettings.setQuality(QMultimedia::HighQuality);
    audioRecorder->setEncodingSettings(audioSettings);

    connect(timer, &QTimer::timeout, this, &AudioRecorder::updateRecordingTime);
}

void AudioRecorder::startRecording() {
    if (audioRecorder->state() == QAudioRecorder::StoppedState) {
        QString outputDir = "C:\\Users\\vamsh\\Desktop\\Vamshi PC\\Work\\VyoriusDrones\\Recordings";

        QDir dir(outputDir);
        if (!dir.exists()) {
            if (!dir.mkpath(".")) {
                qWarning() << "Failed to create directory:" << outputDir;
                return;
            }
        }

        outputFilePath = outputDir + "/recording_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".wav";
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(outputFilePath));

        audioRecorder->record();
        recordingDuration = 0;
        timer->start(1000);
        emit recordingStateChanged("Recording");
    }
}

void AudioRecorder::stopRecording() {
    if (audioRecorder->state() == QAudioRecorder::RecordingState) {
        audioRecorder->stop();
        timer->stop();
        emit recordingStateChanged("Stopped");
    }
}

void AudioRecorder::saveRecording() {
    if (audioRecorder->state() == QAudioRecorder::StoppedState && !outputFilePath.isEmpty()) {
        QString saveDir = "C://Desktop//Vamshi//Work//VyoriusDrones//Recordings";

        QDir dir(saveDir);
        if (!dir.exists()) {
            if (!dir.mkpath(".")) {
                qWarning() << "Failed to create directory:" << saveDir;
                return;
            }
        }

        QString saveFilePath = saveDir + "/saved_recording_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".wav";

        if (QFile::copy(outputFilePath, saveFilePath)) {
            qDebug() << "Recording saved to:" << saveFilePath;
        } else {
            qWarning() << "Failed to save recording to:" << saveFilePath;
        }
    }
}

void AudioRecorder::updateRecordingTime() {
    recordingDuration++;
    QString timeString = QString("%1:%2")
                             .arg(recordingDuration / 60, 2, 10, QLatin1Char('0'))
                             .arg(recordingDuration % 60, 2, 10, QLatin1Char('0'));
    emit recordingTimeChanged(timeString);
}
