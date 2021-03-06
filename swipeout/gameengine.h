/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of Swipeout.                                         *
 *                                                                         *
 *  Swipeout is free software: you can redistribute it and/or modify       *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  Swipeout is distributed in the hope that it will be useful,            *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with Swipeout. If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QFuture>
#include <QDateTime>
#include <QTimer>

#include "levels.h"
#include "levelpack.h"
#include "levelpacks.h"
#include "levelcreator.h"
#include "board.h"
#include "boardsolver.h"
#include "settings.h"

class GameEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LevelPack *levelPack READ levelPack NOTIFY levelPackChanged)
    Q_PROPERTY(LevelPacks *levelPacks READ levelPacks CONSTANT)
    Q_PROPERTY(Levels *loadedLevels READ loadedLevels CONSTANT)
    Q_PROPERTY(LevelCreator *levelCreator READ levelCreator CONSTANT)
    Q_PROPERTY(Board *board READ board CONSTANT)
    Q_PROPERTY(Settings *settings READ settings CONSTANT)
    Q_PROPERTY(QString dataDir READ dataDir WRITE setDataDir NOTIFY dataDirChanged)
    Q_PROPERTY(QString solverTime READ solverTime NOTIFY solverTimeChanged)
    Q_PROPERTY(bool solverRunning READ solverRunning NOTIFY solverRunningChanged)
    Q_PROPERTY(bool hasNextLevel READ hasNextLevel NOTIFY hasNextLevelChanged)
    Q_PROPERTY(bool hasPreviousLevel READ hasPreviousLevel NOTIFY hasPreviousLevelChanged)

public:
    explicit GameEngine(QObject *parent = 0);

    QString dataDir() const;
    void setDataDir(const QString &dataDir);

    QString solverTime() const;

    bool hasNextLevel() const;
    bool hasPreviousLevel() const;

    LevelPack *levelPack();
    LevelPacks *levelPacks();
    LevelCreator *levelCreator();
    Board *board();
    Settings *settings();

    Q_INVOKABLE void loadLevelPack(const QString &name);

    Q_INVOKABLE void loadLevel(Level *level);
    Q_INVOKABLE void loadNextLevel();
    Q_INVOKABLE void loadPreviousLevel();

    Q_INVOKABLE void solveBoard();
    Q_INVOKABLE void stopSolvingBoard();

    Q_INVOKABLE void resetSettings();

    Levels *loadedLevels();
    Q_INVOKABLE void loadCreatedLevels();

    bool solverRunning() const;

private:
    QString m_dataDir;
    LevelPack *m_levelPack;
    LevelPacks *m_levelPacks;
    Levels *m_createdLevels;
    LevelCreator *m_levelCreator;
    Board *m_board;
    BoardSolver *m_solver;
    QFutureWatcher<QStack<Move> > *m_watcher;
    Settings *m_settings;

    QTimer *m_solverTimer;
    QDateTime m_solverStartTime;
    QString m_solverTime;
    bool m_solverRunning;
    Board *m_solverBoard;

    Level *m_nextLevel;
    Level *m_previousLevel;

    bool m_hasNextLevel;
    bool m_hasPreviousLevel;

    void loadLevelPacks();
    bool levelAlreadyLoaded(const int &id);

    void reloadLevelPackStatistic();

    void setSolverRunning(const bool &solverRunning);
    void setSolverTime(const QString &solverTime);

    void setHasNextLevel(const bool &hasNextLevel);
    void setHasPreviousLevel(const bool &hasPreviousLevel);

private slots:
    void onSolverFinished();
    void onLevelCompleted();
    void onShowSolutionSpeedChanged();
    void onSolverTimerTimout();

signals:
    void dataDirChanged();
    void hasNextLevelChanged();
    void hasPreviousLevelChanged();
    void solverTimeChanged();
    void solverRunningChanged();
    void solutionReady(const QString &runTime);
    void levelPackChanged();

};

#endif // GAMEENGINE_H
