#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QTimer>
#include <QListWidgetItem>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <iomanip>
#include <sstream>

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
    //! Member function that updates slider every if music is playing.
    /*!
     * \return void
     */
    void updateSlider();

    //! Member function that updates duration of current track.
    /*!
     * \return void
     */
    void updateMusicTimeLabel();

    //! Member function that updates position of current track.
    /*!
     * \return void
     */
    void updatePlayTimeLabel();

    //! Member function that updates the label of the current track.
    /*!
     * \return void
     */
    void updateCurrentTrackLabel();

    //! Member function that updates the display of the play button.
    /*!
     * \return void
     */
    void updatePlayButtonStatus();

    //! Member function that prompts user to locally add music files.
    /*!
     * \return void
     */
    void on_addButton_clicked();

    //! Member function that removes a selected file from playlist.
    /*!
     * \return void
     */
    void on_removeButton_clicked();

    //! Member function that plays or pauses the media.
    /*!
     * \return void
     */
    void on_playButton_clicked();

    //! Member function that plays the next track in playlist.
    /*!
     * \return void
     */
    void on_nextButton_clicked();

    //! Member function that plays the previous track in playlist.
    /*!
     * \return void
     */
    void on_backButton_clicked();

    //! Member function that changes song to selected track.
    /*!
     * \param item item selected from playlist.
     * \return void
     */
    void on_playlistList_itemDoubleClicked(QListWidgetItem *item);

    //! Member function that sets loop status of current track in playlist.
    /*!
     * \param checked loop toggle status.
     * \return void
     */
    void on_loopButton_toggled(bool checked);

    //! Member function that sets shuffle status of playlist.
    /*!
     * \param checked shuffle toggle status.
     * \return void
     */
    void on_shuffleButton_toggled(bool checked);

    //! Member function that updates player position of current track.
    /*!
     * \param position position of the slider.
     * \return void
     */
    void on_trackSlider_sliderMoved(int position);

    //! Member function that updates player volume when slider is changed.
    /*!
     * \param value value of the slider.
     * \return void
     */
    void on_volumeSlider_valueChanged(int value);

    //! Member function that saves current playlist to file.
    /*!
     * \return void
     */
    void on_saveButton_clicked();

    //! Member function that uploads and loads playlist from file.
    /*!
     * \return void
     */
    void on_actionUpload_triggered();

    //! Member function that clears playlist.
    /*!
     * \return void
     */
    void on_actionClear_triggered();

    void on_actionInfo_triggered();

private:
    Ui::MainWindow *ui;                         /*!< MainWindow UI */
    QMediaPlayer *player;                       /*!< music player */
    QMediaPlaylist *playlist;                   /*!< music playlist */
    QPropertyAnimation *animation;              /*!< animation controller */
    QString styling;                            /*!< stylesheet contents */

    const QString APPLICATION_NAME = "cisum";
    const QString ACTIVE_BUTTON_CSS = "background-color: #0099ff; border-color: #0099ff";
};

#endif // MAINWINDOW_H
