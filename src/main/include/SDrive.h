#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc/XboxController.h>

class SDrive
{
private:


public:
    frc::Joystick *jstick{0};
    frc::XboxController *controller{0};
    //rev::CANSparkMax *leftMotor;
    //rev::CANSparkMax *rightMotor;
    rev::CANSparkMax* m_leftLeadMotor;
    rev::CANSparkMax *m_rightLeadMotor;
    rev::CANSparkMax* m_leftFollowMotor;
    rev::CANSparkMax* m_rightFollowMotor;
    int driveMotorCurrentLimit = 30;
    SDrive(int controller_ID, int LL_ID, int RL_ID, int LF_ID, int RF_ID);
    void Joystick_Display();
    void Arcade_Drive();



};
SDrive::SDrive(int controller_ID, int LL_ID, int RL_ID, int LF_ID, int RF_ID)
{
    rev::CANSparkMax* m_leftLeadMotor = new rev::CANSparkMax(LL_ID, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANSparkMax* m_rightLeadMotor = new rev::CANSparkMax(RL_ID, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANSparkMax* m_leftFollowMotor = new rev::CANSparkMax(LF_ID, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANSparkMax* m_rightFollowMotor = new rev::CANSparkMax(RF_ID, rev::CANSparkMax::MotorType::kBrushless);
    jstick = new frc::Joystick(controller_ID);
    //controller = new frc::XboxController(controller_ID);


    //leftMotor = new rev::CANSparkMax(LL_ID, rev::CANSparkMax::MotorType::kBrushless);
    //rightMotor = new rev::CANSparkMax(RL_ID, rev::CANSparkMax::MotorType::kBrushless);
    m_leftLeadMotor->RestoreFactoryDefaults();
    m_rightLeadMotor->RestoreFactoryDefaults();
    m_leftFollowMotor->RestoreFactoryDefaults();
    m_rightFollowMotor->RestoreFactoryDefaults();

    // Set current limit for drive motors
    m_leftLeadMotor->SetSmartCurrentLimit(driveMotorCurrentLimit);
    m_rightLeadMotor->SetSmartCurrentLimit(driveMotorCurrentLimit);
    m_leftFollowMotor->SetSmartCurrentLimit(driveMotorCurrentLimit);
    m_rightLeadMotor->SetSmartCurrentLimit(driveMotorCurrentLimit);

    // Set drive motors to brake mode
    m_leftLeadMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_rightLeadMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_leftFollowMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_rightFollowMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    // Set followers and inverts for drive motors
    m_leftLeadMotor->SetInverted(true);
    m_leftFollowMotor->Follow(*m_leftLeadMotor, false);
    m_rightLeadMotor->SetInverted(false);
    m_rightFollowMotor->Follow(*m_rightLeadMotor, false);


}
void SDrive::Joystick_Display() {
    frc::SmartDashboard::PutNumber("left y: ", -(jstick->GetRawAxis(1)));
    frc::SmartDashboard::PutNumber("right y: ", jstick->GetRawAxis(3));
    frc::SmartDashboard::PutBoolean("A_Button", controller->GetAButton());
    //frc::SmartDashboard::PutNumber("current", m_leftLeadMotor->GetOutputCurrent());

}
void SDrive::Arcade_Drive() {
    int left_x = controller->GetLeftX();
    int left_y = controller->GetLeftY();
    int right_y = controller->GetRightY();
    int right_x = controller->GetRightX();
    double left_Final;
    double right_Final;
    // Turning
    if (right_x > 0.25 || right_x < -0.25) {
        left_Final = right_x;
        right_Final = -right_x;
    } else {
        left_Final = left_y;
        right_Final = left_y;

    }


    /*
    if (controller->GetAButton()) {
        if (left_x > 0) {
            left_Final = left_y;
            right_Final = left_y - left_x;
        } else {
            left_Final = left_y + left_x;
            right_Final = left_y;
        }
        //No Turn
    } else {
        left_Final = left_y;
        right_Final = left_y;
    }
    */


    m_leftLeadMotor->Set(left_Final);
    m_rightLeadMotor->Set(right_Final);
    //leftMotor->Set(jstick->GetRawAxis(1));
    //rightMotor->Set(jstick->GetRawAxis(3));


}