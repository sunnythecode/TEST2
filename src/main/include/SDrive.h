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
    frc::SmartDashboard::PutNumber("Joystick X", jstick->GetX());
    frc::SmartDashboard::PutNumber("Joystick Y", jstick->GetY());

}
void SDrive::Arcade_Drive() {
    int left_Final;
    int right_Final;
    // Turning
    if (jstick->GetRawButton(0)) {
        if (jstick->GetX() > 0) {
            leftMotor->Set(jstick->GetX());
            rightMotor->Set(-jstick->GetX());
        } else {
            leftMotor->Set(jstick->GetX());
            rightMotor->Set(-jstick->GetX());
        }
    }

    
    leftMotor->Set(jstick->GetY());
    rightMotor->Set(jstick->GetY());


}