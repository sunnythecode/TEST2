#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>


class SDrive
{
private:


public:
    frc::Joystick *jstick{0};
    rev::CANSparkMax *leftMotor;
    rev::CANSparkMax *rightMotor;
    SDrive(int controller_ID, int LL_ID, int RL_ID, int LF_ID, int RF_ID);
    void Joystick_Display();
    void Arcade_Drive();



};
SDrive::SDrive(int controller_ID, int LL_ID, int RL_ID, int LF_ID, int RF_ID)
{
    jstick = new frc::Joystick(controller_ID);
    leftMotor = new rev::CANSparkMax(LL_ID, rev::CANSparkMax::MotorType::kBrushless);
    rightMotor = new rev::CANSparkMax(RL_ID, rev::CANSparkMax::MotorType::kBrushless);


}
void SDrive::Joystick_Display() {
    frc::SmartDashboard::PutNumber("left y: ", -(jstick->GetRawAxis(1)));
    frc::SmartDashboard::PutNumber("right x: ", jstick->GetRawAxis(4));
    //frc::SmartDashboard::PutNumber("current", m_leftLeadMotor->GetOutputCurrent());

}
void SDrive::Arcade_Drive() {
    int left_Final = jstick->GetY();
    int right_Final = jstick->GetY();
    // Turning



    
    leftMotor->Set(jstick->GetRawAxis(1));
    rightMotor->Set(jstick->GetRawAxis(3));


}