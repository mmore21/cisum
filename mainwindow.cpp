#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(900, 600);
    this->setWindowTitle("Cisum");

    player = new QMediaPlayer;
    playlist = new QMediaPlaylist();

    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(updateMusicTimeLabel()));
    connect(player, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(updateCurrentTrackLabel()));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(updatePlayButtonStatus()));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(updatePlayTimeLabel()));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(updateSlider()));

    player->setPlaylist(playlist);

    ui->currentTrackLabel->clear();
    ui->volumeSlider->setValue(100);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    animation = new QPropertyAnimation(ui->title, "geometry");
    animation->setDuration(750);
    animation->setKeyValueAt(0, QRect(10, -100, 871, 101));
    animation->setKeyValueAt(1, QRect(10, 10, 871, 101));

    animation->start();

    QFile *styleSheet = new QFile(":/css/css/button.css");
    styleSheet->open(QFile::ReadOnly);
    styling = QLatin1String(styleSheet->readAll());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSlider()
{
    // if user is not dragging slider
    if (!ui->trackSlider->isSliderDown())
    {
        ui->trackSlider->setValue(static_cast<int>(static_cast<double>(player->position()) / player->duration() * 1000));
    }
}

void MainWindow::updateMusicTimeLabel()
{
    long long musicTime = player->duration() / 1000;
    long long musicTimeMinutes = musicTime / 60;
    long long musicTimeSeconds = musicTime % 60;

    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << musicTimeMinutes << ":";
    ss << std::setw(2) << std::setfill('0') << musicTimeSeconds;

    ui->musicTimeLabel->setText(QString::fromStdString(ss.str()));
}

void MainWindow::updatePlayTimeLabel()
{
    long long playTime = player->position() / 1000;
    long long musicTimeMinutes = playTime / 60;
    long long musicTimeSeconds = playTime % 60;

    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << musicTimeMinutes << ":";
    ss << std::setw(2) << std::setfill('0') << musicTimeSeconds;

    ui->playTimeLabel->setText(QString::fromStdString(ss.str()));
}

void MainWindow::updateCurrentTrackLabel()
{
    ui->currentTrackLabel->setText(player->currentMedia().canonicalUrl().fileName());
}

void MainWindow::updatePlayButtonStatus()
{
    if (player->state() == QMediaPlayer::PlayingState)
    {
        ui->playButton->setText("Pause");
    }
    else
    {
        ui->playButton->setText("Play");
    }
}

void MainWindow::on_addButton_clicked()
{
    QStringList trackUrls = QFileDialog::getOpenFileNames(this,
        tr("Open Music"), "/home", tr("Music Files (*.mp3 *.ogg *.wav)"));

    for (int i = 0; i < trackUrls.size(); i++)
    {
        QMediaContent mediaContent = QMediaContent("file://" + trackUrls.at(i));
        playlist->addMedia(mediaContent);
        ui->playlistList->addItem(mediaContent.canonicalUrl().fileName());
    }
}

void MainWindow::on_trackSlider_sliderMoved(int position)
{
    player->setPosition(player->duration() / 1000 * position);
}

void MainWindow::on_playButton_clicked()
{
    if (playlist->mediaCount())
    {
        if (player->state() == QMediaPlayer::PlayingState)
        {
            player->pause();
        }
        else
        {
            player->play();
        }
    }
}

void MainWindow::on_nextButton_clicked()
{
    if (playlist->playbackMode() == QMediaPlaylist::CurrentItemInLoop)
    {
        ui->loopButton->toggle();
    }
    playlist->next();
}

void MainWindow::on_backButton_clicked()
{
    if (playlist->playbackMode() == QMediaPlaylist::CurrentItemInLoop)
    {
        ui->loopButton->toggle();
    }
    playlist->previous();
}

void MainWindow::on_loopButton_toggled(bool checked)
{
    if (checked)
    {
        ui->loopButton->setStyleSheet("background-color: #0099ff; border-color: #0099ff");

        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else
    {
        ui->loopButton->setStyleSheet(styling);

        if (ui->shuffleButton->isChecked())
        {
            playlist->setPlaybackMode(QMediaPlaylist::Random);
        }
        else
        {
            playlist->setPlaybackMode(QMediaPlaylist::Loop);
        }
    }
}

void MainWindow::on_shuffleButton_toggled(bool checked)
{
    if (checked)
    {
        ui->shuffleButton->setStyleSheet("background-color: #0099ff; border-color: #0099ff");

        if (ui->loopButton->isChecked())
        {
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        }
        else
        {
            playlist->setPlaybackMode(QMediaPlaylist::Random);
        }
    }
    else
    {
        ui->shuffleButton->setStyleSheet(styling);

        if (ui->loopButton->isChecked())
        {
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        }
        else
        {
            playlist->setPlaybackMode(QMediaPlaylist::Loop);
        }
    }
}

void MainWindow::on_playlistList_itemDoubleClicked(QListWidgetItem *item)
{
    playlist->setCurrentIndex(ui->playlistList->row(item));
    player->play();
}

void MainWindow::on_removeButton_clicked()
{
    if (!ui->playlistList->selectedItems().empty())
    {
        int deleteIndex = ui->playlistList->currentRow();
        playlist->removeMedia(deleteIndex);
        ui->playlistList->takeItem(deleteIndex);
    }
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    player->setVolume(value);
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this, tr("Save Playlist"),
            "/home/untitled.m3u",
            tr("Playlist File (*.m3u)"));

    playlist->save(QUrl::fromLocalFile(fileName), "m3u");
}

void MainWindow::on_actionUpload_triggered()
{
    QString playlistUrl = QFileDialog::getOpenFileName(this,
        tr("Open Playlist"), "/home", tr("Playlist File (*.m3u)"));

    QFile file(playlistUrl);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening playlist file.";
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString trackUrl = in.readLine();
        QMediaContent mediaContent = QMediaContent(trackUrl);
        playlist->addMedia(mediaContent);
        ui->playlistList->addItem(mediaContent.canonicalUrl().fileName());
    }

    file.close();
}

void MainWindow::on_actionClear_triggered()
{
    playlist->clear();
    ui->playlistList->clear();
    player->stop();
}
