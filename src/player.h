#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QSettings>

#include "engine_fwd.h"

class Playlist;
class Settings;
class LastFMService;

class Player : public QObject {
  Q_OBJECT

 public:
  Player(Playlist* playlist, LastFMService* lastfm, QObject* parent = 0);

  EngineBase* GetEngine() { return engine_; }
  Engine::State GetState() const;
  int GetVolume() const;

 public slots:
  void PlayAt(int index);
  void PlayPause();
  void Next();
  void Previous();
  void Stop();
  void SetVolume(int value);

  void TrackEnded();
  void StreamReady(const QUrl& original_url, const QUrl& media_url);

 signals:
  void Playing();
  void Paused();
  void Stopped();
  void VolumeChanged(int volume);
  void Error(const QString& message);

 private slots:
  void EngineStateChanged(Engine::State);

 private:
  Playlist* playlist_;
  LastFMService* lastfm_;
  QSettings settings_;

  EngineBase* engine_;
};

#endif // PLAYER_H
