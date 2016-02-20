#ifndef MUDLET_TROOMDB_H
#define MUDLET_TROOMDB_H

/***************************************************************************
 *   Copyright (C) 2008-2013 by Heiko Koehn - KoehnHeiko@googlemail.com    *
 *   Copyright (C) 2014 by Ahmed Charles - acharles@outlook.com            *
 *   Copyright (C) 2015 by Stephen Lyons - slysven@virginmedia.com         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "pre_guard.h"
#include <QHash>
#include <QMultiHash>
#include <QMap>
#include <QString>
#include "post_guard.h"

class TArea;
class TMap;
class TRoom;


class TRoomDB
{
public:
    virtual TRoom * getRoom( int id ) = 0;
    virtual TArea * getArea( int id ) = 0;
//    int getArea( TArea * pA ); use duplicate int getAreaID( TArea * pA ) instead
    virtual bool addRoom( int id ) = 0;
    virtual int size() = 0;
    virtual bool removeRoom( int ) = 0;
    virtual void removeRoom( QList<int> & ) = 0;
    virtual bool removeArea( int id ) = 0;
    virtual bool removeArea( QString name ) = 0;
    virtual void removeArea( TArea * ) = 0;
    virtual bool addArea(int id) = 0;
    virtual int addArea( QString name ) = 0;
    virtual bool addArea( int id, QString name ) = 0;
    virtual bool setAreaName( int areaID, QString name ) = 0;
    virtual const QList<TRoom *> getRoomPtrList() = 0;
    virtual const QList<TArea *> getAreaPtrList() = 0;
    virtual const QHash<int, TRoom *> & getRoomMap() const = 0;
    virtual const QMap<int, TArea *> & getAreaMap() const = 0;
    virtual QList<int> getRoomIDList() = 0;
    virtual QList<int> getAreaIDList() = 0;
    virtual const QMap<int, QString> & getAreaNamesMap() const = 0;
    virtual void updateEntranceMap(TRoom *, bool isMapLoading = false ) = 0;
    virtual void updateEntranceMap(int) = 0;
    virtual const QMultiHash<int, int> & getEntranceHash() = 0;
    virtual void deleteValuesFromEntranceMap( int ) = 0;
    virtual void deleteValuesFromEntranceMap( QSet<int> & ) = 0;

    virtual void buildAreas() = 0;
    virtual void clearMapDB() = 0;
    virtual void initAreasForOldMaps() = 0;
    virtual void auditRooms() = 0;
    virtual bool addRoom(int id, TRoom *pR, bool isMapLoading = false) = 0;
    virtual int getAreaID(TArea * pA) = 0;
    virtual void restoreAreaMap( QDataStream & ) = 0;
    virtual void restoreSingleArea( QDataStream &, int, TArea * ) = 0;
    virtual void restoreSingleRoom( QDataStream &, int, TRoom * ) = 0;
    virtual QMap<QString,int> hashTable;
    virtual ~TRoomDB() {};



private:
    bool __removeRoom( int id );

    friend class TRoom;//friend TRoom::~TRoom();
    //friend class TMap;//bool TMap::restore(QString location);
    //friend bool TMap::serialize(QDataStream &);
    friend class XMLexport;
};

class ConcreteTRoomDB: TRoomDB
{
public:
    ConcreteTRoomDB( TMap * );

private:
    ConcreteTRoomDB(){};
    int createNewAreaID();
    bool __removeRoom( int id );

    QHash<int, TRoom *> rooms;
    QMultiHash<int, int> entranceMap;
    QMap<int, TArea *> areas;
    QMap<int, QString> areaNamesMap;
    TMap * mpMap;
    QString mUnnamedAreaName;
    QList<int> * mpTempRoomDeletionList; // Used during bulk room deletion

    friend class TRoom;//friend TRoom::~TRoom();
    //friend class TMap;//bool TMap::restore(QString location);
    //friend bool TMap::serialize(QDataStream &);
    friend class XMLexport;
};

#endif // MUDLET_TROOMDB_H
