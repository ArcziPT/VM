#include <registers/Register.h>
#include <gtest/gtest.h>

TEST(RegisterContrustorTest, ConstructorThrowTest){
    EXPECT_ANY_THROW(Register("reg_name", 0xABCD, 12, Register::Type::IP));

    EXPECT_NO_THROW(Register("reg_name", 0xABCD, 32, Register::Type::IP));
}



class RegisterTest : public testing::Test{
public:
    Register* reg;

    RegisterTest(){
        reg = new Register("name", 0xABCD, 32, Register::Type::GENERAL);
    }

    ~RegisterTest(){
        delete reg;
    }
};

TEST_F(RegisterTest, RegisterDataTest){
    ASSERT_EQ(0xABCD, reg->get_code());
    ASSERT_EQ("name", reg->get_name());
    ASSERT_EQ(32, reg->get_sz());
    ASSERT_EQ(Register::Type::GENERAL, reg->get_type());
}


struct RegisterValueState{
    reg_val init;
    reg_val add;
    reg_val sub;
    reg_val fin;
};

class RegisterValueTest : public RegisterTest, public testing::WithParamInterface<RegisterValueState>{

public:
    RegisterValueTest(){
        reg->set_value(GetParam().init);
    }
};

TEST_P(RegisterValueTest, FinalValue){
    auto state = GetParam();

    EXPECT_EQ(state.init, reg->get_value());

    reg->set_value(reg->get_value() + state.add);
    reg->set_value(reg->get_value() - state.sub);

    EXPECT_EQ(state.fin, reg->get_value());
}

INSTANTIATE_TEST_CASE_P(Default, RegisterValueTest, 
testing::Values(
    RegisterValueState{0, 100, 20, 80},
    RegisterValueState{1000, 8000, 2000, 7000}
));