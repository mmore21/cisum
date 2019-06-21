#include "track.h"

Track::Track()
{
    this->name.clear();
    this->url.clear();
}

Track::Track(QString name, QString url)
{
    this->name = name;
    this->url = url;
}

QString Track::getName() const
{
    return name;
}

QString Track::getUrl() const
{
    return url;
}
