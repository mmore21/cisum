#include "playlist.h"

Playlist::Playlist()
{
    this->tracks.clear();
    this->currentIndex = 0;
}

void Playlist::addTrack(Track track)
{
    tracks.push_back(track);
}

void Playlist::removeTrack(int index)
{
    tracks.removeAt(index);
}

QVector<Track> Playlist::getTracks() const
{
    return tracks;
}

int Playlist::getCurrentIndex() const
{
    return currentIndex;
}


QUrl Playlist::getTrackUrl(int index)
{
    return QUrl::fromLocalFile(tracks.at(index).getUrl());
}

bool Playlist::isEmpty()
{
    return tracks.empty();
}
