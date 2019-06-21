#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QVector>
#include <QUrl>
#include "track.h"

class Playlist
{
public:
    Playlist();

    void addTrack(Track track);
    void removeTrack(int index);

    QVector<Track> getTracks() const;
    int getCurrentIndex() const;

    QUrl getTrackUrl(int index);

    bool isEmpty();

private:
    QVector<Track> tracks;
    int currentIndex;
};

#endif // PLAYLIST_H
