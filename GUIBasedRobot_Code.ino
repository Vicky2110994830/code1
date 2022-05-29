#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>
#include <RemoteXY.h>

#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600

#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
{
  255, 3, 0, 0, 0, 29, 0, 16, 31, 1, 5, 16, 16, 40, 30, 30, 36, 8, 34, 2, 0, 4, 6, 22, 11, 12, 66, 31, 31, 79, 78, 0, 79, 70, 70
};

struct {

  int8_t joystick_1_x;
  int8_t joystick_1_y;
  uint8_t switch_1;

  uint8_t connect_flag;

} RemoteXY;
#pragma pack(pop)

#define PIN_SWITCH_1 10

#define right_motor_A 6
#define right_motor_B 7
#define right_motor_speed 12

#define left_motor_A 7
#define left_motor_B 8
#define left_motor_speed 13

uint8_t RightMotor[3] = {right_motor_A, right_motor_B, right_motor_speed};
uint8_t LeftMotor[3] = {left_motor_A, left_motor_B, left_motor_speed};

void Wheel (uint8_t * motor, int v)
{
  if (v > 100)
  {
    v = 100;
  }
  if (v < -100)
  {
    v = -100;
  }
  if (v > 0)
  {
    digitalWrite (motor [0], HIGH);
    digitalWrite (motor [1], LOW);
    analogWrite (motor [2], v * 2.55);
  }

  else if ( v < 0 ) {

    digitalWrite (motor [0], LOW);
    digitalWrite (motor [1], HIGH);
    analogWrite (motor [2], (-v) * 2.55);
  }

  else {
    digitalWrite (motor [0], LOW);
    digitalWrite (motor [1], LOW);
    analogWrite (motor [2], 0);
  }
}


void setup()
{
  RemoteXY_Init();

  pinMode (PIN_SWITCH_1, OUTPUT);
  pinMode (right_motor_A, OUTPUT);
  pinMode (right_motor_B, OUTPUT);
  pinMode (left_motor_A, OUTPUT);
  pinMode (left_motor_B, OUTPUT);
}

void loop()
{
  RemoteXY_Handler ();
  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1 == 0) ? LOW : HIGH);
  Wheel(LeftMotor, RemoteXY.joystick_1_y + RemoteXY.joystick_1_x);
  Wheel(RightMotor, RemoteXY.joystick_1_y - RemoteXY.joystick_1_x);


  
}
