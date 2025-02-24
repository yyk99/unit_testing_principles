//
// https://stackoverflow.com/questions/72954488/gmock-visual-studio-test-crashes-when-using-expect-call
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return;

class MockCow
{
public:
    MOCK_METHOD0(Moo,int());
};

TEST(the_unit_test,the_test_method) {
    MockCow cow;

    EXPECT_CALL(cow,Moo())
        .WillOnce(Return(42));

    cow.Moo();
};

int main(int argc,char *argv[]) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
