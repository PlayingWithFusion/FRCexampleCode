/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  /**
     * Set PID gains and Feed foreward term.  These values work well for an
     * unloaded Venom motor.   P and I gains will likely need to increase 
     * depending on the motor load
     */
    m_motor.SetPID(0.195, 0.010, 0.0, 0.184, 0.0);
    
    /**
     * Set max acceleration and jerk limits when responding to step changes
     * in the motor speed command.   This allows Venom to calculate a true
     * s-curve internally
     */
    m_motor.SetMaxAcceleration(15000);  // RPM per second
    m_motor.SetMaxJerk(15000);          // RPM per second squared

    /**
     * Set the commanded motor speed to 0 RPM each time we enable the driver
     * station
     */
    m_commandedSpeed = 0;
    m_motor.SetCommand(frc::CANVenom::ControlMode::kSpeedControl, m_commandedSpeed);
}

void Robot::TeleopPeriodic() {
  /** 
     * Place the robot into teleop mode and enable the driverstation.
     * Press the X, Y, A & B buttons to adjsut the motor speed.   Y and A
     * command 4000 RPM in forward and reverse.  X and  B command the 
     * motor to stop.
     */
    if (m_gamePad.GetRawButtonPressed(4)) { // Y button
      m_commandedSpeed = 4000;
    }
    else if (m_gamePad.GetRawButtonPressed(1)) { // A button
      m_commandedSpeed = -4000;
    }
    else if (m_gamePad.GetRawButtonPressed(2) || m_gamePad.GetRawButtonPressed(3)) {  // X or B button
      m_commandedSpeed = 0;
    }

    // Place Venom into speed control mode and command m_commandedSpeed (in RPM)
    m_motor.SetCommand(frc::CANVenom::ControlMode::kSpeedControl, m_commandedSpeed);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
