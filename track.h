#ifndef TRACK_H
#define TRACK_H

#include <QString>

class Track
{
public:
    Track();
    Track(QString name, QString url);

    QString getName() const;
    QString getUrl() const;

private:
    QString name;
    QString url;
};

#endif // TRACK_H
