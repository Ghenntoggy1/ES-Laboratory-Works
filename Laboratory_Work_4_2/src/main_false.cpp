// #include <Arduino.h>

// #define enA 8
// #define in1 2
// #define in2 3

// int motorPower = 0;       // Current motor power (-100 to 100)
// int rotDirection = 1;     // 1 = forward, -1 = backward

// void setMotorPower(int power) {
//   motorPower = constrain(power, -100, 100);
  
//   int pwmOutput = map(abs(motorPower), 0, 100, 0, 255);

//   if (motorPower > 0) {
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);
//     rotDirection = 1;
//   } else if (motorPower < 0) {
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);
//     rotDirection = -1;
//   } else {
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, LOW); // Stop motor
//   }

//   analogWrite(enA, pwmOutput);
// }

// void setup() {
//   pinMode(enA, OUTPUT);
//   pinMode(in1, OUTPUT);
//   pinMode(in2, OUTPUT);
//   Serial.begin(9600);
//   Serial.println("Motor Control Ready. Type 'motor set <value>' to set power.");
//   Serial.println("Commands: motor stop, motor max, motor inc, motor dec");
//   Serial.println("Value range: -100 to 100 (negative for reverse).");
//   Serial.println("Current power: 0 (stopped).");
//   Serial.println("Use 'motor set <value>' to set power.");
//   Serial.println("Use 'motor stop' to stop the motor.");
//   Serial.println("Use 'motor max' to set max power in current direction.");
//   Serial.println("Use 'motor inc' to increase power by 10.");
//   Serial.println("Use 'motor dec' to decrease power by 10.");

//   // Initialize motor in stopped state
//   setMotorPower(0);
// }

// void loop() {
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');
//     input.trim();

//     if (input.startsWith("motor set ")) {
//       int value = input.substring(10).toInt();
//       setMotorPower(value);
//       Serial.print("Set power to: ");
//       Serial.println(motorPower);
//     } else if (input == "motor stop") {
//       setMotorPower(0);
//       Serial.println("Motor stopped.");
//     } else if (input == "motor max") {
//       setMotorPower(100 * rotDirection);
//       Serial.print("Motor set to max in current direction: ");
//       Serial.println(motorPower);
//     } else if (input == "motor inc") {
//       setMotorPower(motorPower + 10 * rotDirection);
//       Serial.print("Motor power increased: ");
//       Serial.println(motorPower);
//     } else if (input == "motor dec") {
//       if (motorPower == 0) {
//         Serial.println("Motor already stopped.");
//       } else {
//         int step = 10 * (motorPower > 0 ? 1 : -1);
//         int newPower = motorPower - step;
//         if ((motorPower > 0 && newPower < 0) || (motorPower < 0 && newPower > 0)) {
//           newPower = 0;
//         }
//         setMotorPower(newPower);
//         Serial.print("Motor power decreased: ");
//         Serial.println(motorPower);
//       }
//     } else {
//       Serial.println("Invalid command.");
//     }
//   }
// }
