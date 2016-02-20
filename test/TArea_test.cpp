#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Imports for units under test are relative to src/ directory
#include "TArea.h"
#include "mocks/MockTRoomDB.h"

using namespace testing;

class aTArea : public testing::Test {
  public:
    MockTRoomDB mockTRoomDB;
    TArea *area = NULL;

    void SetUp() {
      area = new TArea( NULL, &mockTRoomDB );
    }

    void TearDown() {
      if (area != NULL) {
        delete area;
        area = NULL;
      }
    }
};

TEST_F(aTArea, destructorShouldRemoveItselfFromTRoomDB)
{
  EXPECT_CALL(mockTRoomDB, removeArea(area)).Times(1);

  delete area;
  area = NULL;
}

TEST_F(aTArea, getAreaIDFailsIfNoTRoomDB)
{
  auto areaWithNoTRoomDB = new TArea( NULL, NULL );

  ASSERT_THAT(areaWithNoTRoomDB->getAreaID(), Eq(-1));
}

TEST_F(aTArea, getAreaIDLooksUpIDInTRoomDB)
{
  ON_CALL(mockTRoomDB, getAreaID(area)).WillByDefault(Return(42));
  EXPECT_CALL(mockTRoomDB, getAreaID(area)).Times(1);

  ASSERT_THAT(area->getAreaID(), Eq(42));
}

