#include "TRoomDB.h"

typedef QHash<int, TRoom *> IntTRoomQHash;
typedef QMap<int, TArea *> IntTAreaQMap;
typedef QMap<int, QString> IntQStringQMap;
typedef QMultiHash<int, int> IntIntQMultiHash;

class MockTRoomDB : public TRoomDB {
public:
  MOCK_METHOD1(getRoom, TRoom *(int id));
  MOCK_METHOD1(getArea, TArea *(int id));
  MOCK_METHOD2(putRoomIDByHash, void(QString hash, int id));
  MOCK_METHOD1(getRoomIDByHash, int(QString hash));
  MOCK_METHOD1(writeRoomIDByHashTable, void(QDataStream &ofs));
  MOCK_METHOD1(readRoomIDByHashTable, void(QDataStream &ifs));
  MOCK_METHOD1(addRoom, bool(int id));
  MOCK_METHOD0(size, int());
  MOCK_METHOD1(removeRoom, bool(int));
  MOCK_METHOD1(removeRoom, void(QList<int> &));
  MOCK_METHOD1(removeArea, bool(int id));
  MOCK_METHOD1(removeArea, bool(QString name));
  MOCK_METHOD1(removeArea, void(TArea *));
  MOCK_METHOD1(addArea, bool(int id));
  MOCK_METHOD1(addArea, int(QString name));
  MOCK_METHOD2(addArea, bool(int id, QString name));
  MOCK_METHOD2(setAreaName, bool(int areaID, QString name));
  MOCK_METHOD0(getRoomPtrList, const QList<TRoom *>());
  MOCK_METHOD0(getAreaPtrList, const QList<TArea *>());
  // The following line won't really compile, as the return
  // type has multiple template arguments.  To fix it, use a
  // typedef for the return type.
  MOCK_CONST_METHOD0(getRoomMap, const IntTRoomQHash &());
  // The following line won't really compile, as the return
  // type has multiple template arguments.  To fix it, use a
  // typedef for the return type.
  MOCK_CONST_METHOD0(getAreaMap, const IntTAreaQMap &());
  MOCK_METHOD0(getRoomIDList, QList<int>());
  MOCK_METHOD0(getAreaIDList, QList<int>());
  // The following line won't really compile, as the return
  // type has multiple template arguments.  To fix it, use a
  // typedef for the return type.
  MOCK_CONST_METHOD0(getAreaNamesMap, const IntQStringQMap &());
  MOCK_METHOD2(updateEntranceMap, void(TRoom *, bool));
  MOCK_METHOD1(updateEntranceMap, void(int));
  // The following line won't really compile, as the return
  // type has multiple template arguments.  To fix it, use a
  // typedef for the return type.
  MOCK_CONST_METHOD0(getEntranceHash, const IntIntQMultiHash &());
  MOCK_METHOD1(deleteValuesFromEntranceMap, void(int));
  MOCK_METHOD1(deleteValuesFromEntranceMap, void(QSet<int> &));
  MOCK_METHOD0(buildAreas, void());
  MOCK_METHOD0(clearMapDB, void());
  MOCK_METHOD0(initAreasForOldMaps, void());
  MOCK_METHOD0(auditRooms, void());
  MOCK_METHOD3(addRoom, bool(int, TRoom *, bool));
  MOCK_METHOD1(getAreaID, int(TArea *pA));
  MOCK_METHOD1(restoreAreaMap, void(QDataStream &));
  MOCK_METHOD3(restoreSingleArea, void(QDataStream &, int, TArea *));
  MOCK_METHOD3(restoreSingleRoom, void(QDataStream &, int, TRoom *));
  MOCK_METHOD1(__removeRoom, bool(int id));
};
