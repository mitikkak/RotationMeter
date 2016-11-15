
#include <gtest/gtest.h>
#include "Rotation.h"

class TestRotation : public ::testing::Test {
public:


    void SetUp()
    {

    }

    void TearDown() {

    }
};

TEST_F(TestRotation, once)
{
    Rotation r;
    EXPECT_EQ(0, r.times());
    r.inputSensorValue(HIGH_THRESHOLD);
    r.inputSensorValue(LOW_THRESHOLD);
    EXPECT_EQ(1, r.times());
}
TEST_F(TestRotation, perMinute)
{
    Rotation r;
    EXPECT_EQ(0, r.perMinute(0));
    r.set(10);
    EXPECT_EQ(600, r.perMinute(1000));
    EXPECT_EQ(1200, r.perMinute(500));
    EXPECT_EQ(2400, r.perMinute(250));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
