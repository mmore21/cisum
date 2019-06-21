#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QTimer>
#include <QListWidgetItem>

#include "track.h"
#include "playlist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void update();

    void on_addButton_clicked();

    void updateMusicTimeLabel();

    void updatePlayTimeLabel();

    void updatePlaylistList();

    void on_trackSlider_sliderMoved(int position);

    void on_playButton_clicked();

    void on_nextButton_clicked();

    void on_backButton_clicked();

    void on_loopButton_toggled(bool checked);

    void on_shuffleButton_toggled(bool checked);

    void changeTrack(int index);

    void on_playlistList_itemDoubleClicked(QListWidgetItem *item);

    void on_removeButton_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QTimer *updater;
    Playlist playlist;
    bool loop;
    bool shuffle;
    int currentIndex;
};

#endif // MAINWINDOW_H
