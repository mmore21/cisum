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
    updater = new QTimer();

    connect(updater, SIGNAL(timeout()), this, SLOT(update()));

    updater->start();

    currentIndex = -1;

    loop = false;
    shuffle = false;

    ui->currentTrackLabel->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    if (!ui->trackSlider->isSliderDown())
    {
        ui->trackSlider->setValue(static_cast<int>(static_cast<double>(player->position()) / player->duration() * 1000));
    }

    updatePlayTimeLabel();

    if (ui->trackSlider->value() == ui->trackSlider->maximum())
    {
        if (loop)
        {
            changeTrack(currentIndex);
        }
        else
        {
            on_nextButton_clicked();
        }
    }
}

void MainWindow::updateMusicTimeLabel()
{
    updatePlayTimeLabel();
    long long musicTime = player->duration() / 1000;
    long long musicTimeMinutes = musicTime / 60;
    long long musicTimeSeconds = musicTime % 60;
    ui->musicTimeLabel->setText(QString::number(musicTimeMinutes) + ":" + QString::number(musicTimeSeconds));
}

void MainWindow::updatePlayTimeLabel()
{
    long long playTime = player->position() / 1000;
    long long musicTimeMinutes = playTime / 60;
    long long musicTimeSeconds = playTime % 60;
    ui->playTimeLabel->setText(QString::number(musicTimeMinutes) + ":" + QString::number(musicTimeSeconds));
}

void MainWindow::on_addButton_clicked()
{
    QString trackUrl = QFileDialog::getOpenFileName(this,
        tr("Open Music"), "/home", tr("Music Files (*.mp3 *.ogg *.wav)"));


    QFileInfo trackInfo(trackUrl);
    QString trackName(trackInfo.fileName());

    Track t = Track(trackName, trackUrl);
    playlist.addTrack(t);
    ui->playlistList->addItem(t.getName());
}

void MainWindow::updatePlaylistList()
{
    ui->playlistList->clear();
    for (QVector<Track>::iterator it = playlist.getTracks().begin(); it != playlist.getTracks().begin() + 1; ++it)
    {
        qDebug() << it->getName();
        ui->playlistList->addItem(it->getName());
        qDebug() << it->getUrl();
    }
}

void MainWindow::on_trackSlider_sliderMoved(int position)
{
    player->setPosition(player->duration() / 1000 * position);
}

void MainWindow::on_playButton_clicked()
{
    if (!playlist.getTracks().empty())
    {
        if (currentIndex < 0)
        {
            currentIndex = 0;

            ui->playlistList->setCurrentRow(currentIndex);
            ui->currentTrackLabel->setText(ui->playlistList->currentItem()->text());

            player->setMedia(playlist.getTrackUrl(currentIndex));
        }
        if (player->state() == QMediaPlayer::PlayingState)
        {
            player->pause();
            ui->playButton->setText("Play");
        }
        else
        {
            player->play();
            ui->playButton->setText("Pause");
        }
    }
}

void MainWindow::on_nextButton_clicked()
{
    if (!playlist.getTracks().empty())
    {
        qDebug() << currentIndex;
        if (shuffle)
        {
            QVector<int> shuffle_numbers;
            for (int i = 0; i < playlist.getTracks().size(); ++i)
            {
                shuffle_numbers.push_back(i);
            }
            std::random_shuffle(shuffle_numbers.begin(), shuffle_numbers.end());


        }
        else
        {
            currentIndex++;
            if (currentIndex == playlist.getTracks().size())
            {
                currentIndex = 0;
            }
            changeTrack(currentIndex);
        }
    }
}

void MainWindow::on_backButton_clicked()
{
    if (!playlist.getTracks().empty())
    {
        qDebug() << currentIndex;
        if (currentIndex == 0)
        {
            currentIndex = playlist.getTracks().size();
        }
        currentIndex--;
        changeTrack(currentIndex);
    }
}

void MainWindow::on_loopButton_toggled(bool checked)
{
    loop = checked;
    qDebug() << loop;
}

void MainWindow::on_shuffleButton_toggled(bool checked)
{
    shuffle = checked;
    qDebug() << checked;
}

void MainWindow::changeTrack(int index)
{
    ui->playlistList->setCurrentRow(index);
    ui->currentTrackLabel->setText(ui->playlistList->currentItem()->text());

    player->setMedia(playlist.getTrackUrl(index));
    on_playButton_clicked();

}

void MainWindow::on_playlistList_itemDoubleClicked(QListWidgetItem *item)
{
    currentIndex = ui->playlistList->row(item);
    changeTrack(currentIndex);
}

void MainWindow::on_removeButton_clicked()
{
    if (!ui->playlistList->selectedItems().empty())
    {

        int deleteIndex = ui->playlistList->currentRow();
        ui->playlistList->takeItem(deleteIndex);
        playlist.removeTrack(deleteIndex);

        if (playlist.isEmpty())
        {
            player->stop();
            ui->playButton->setText("Play");
            ui->currentTrackLabel->clear();
            currentIndex = -1;
        }
        else
        {
            if (currentIndex == playlist.getTracks().size())
            {
                currentIndex--;
            }
            changeTrack(currentIndex);
        }
    }
}
