#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QObject>
#include <QAudioRecorder>
#include <QUrl>
#include <QFileDialog>
#include <QStandardPaths>


class AudioRecorder : public QObject {
    Q_OBJECT

public:
    explicit AudioRecorder(QObject *parent = nullptr);

    Q_INVOKABLE void startRecording();
    Q_INVOKABLE void stopRecording();
    Q_INVOKABLE void saveRecording();

signals:
    void recordingStateChanged(const QString &state);
    void recordingTimeChanged(const QString &time);

private slots:
    void updateRecordingTime();

private:
    QAudioRecorder *audioRecorder;
    QTimer *timer;
    int recordingDuration; // in seconds
    QString outputFilePath;
};


#endif // AUDIORECORDER_H
