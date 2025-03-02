#include "lab_1_2_main.h"
#include <Arduino.h>
#include "srv_lcd_stdio/srv_lcd_stdio.h"
#include "srv_keypad_stdio/srv_keypad_stdio.h"
#include "dd_led/dd_led.h"

Led ledValid(13);
Led ledInvalid(12);
char correctCode[5] = "";
char inputCode[5];
int inputCodeIndex = 0;
bool codeSet = false;

void lab_1_2_setup() {
    Serial.begin(9600);

    srvLCDSetup();
    srvLCDInit();
    srvKeypadSetup();
}

void lab_1_2_loop() {
    if (!codeSet) {
        while (inputCodeIndex < 4) {
            char key;
            scanf("%c", &key);
            if (key) {
                if (isdigit(key)) {
                    inputCode[inputCodeIndex++] = key;
                    printf("*");
                }
            }
        }
        Serial.println(inputCode);
        inputCode[inputCodeIndex] = '\0';
        strcpy(correctCode, inputCode);
        codeSet = true;
        inputCodeIndex = 0;
        srvLCDClear();
      	Serial.write("SET CODE: ");
      	Serial.write(inputCode);
      	Serial.write("\n");
        printf("Code Set!");
        delay(1000);
        srvLCDClear();
    } else {
        if (inputCodeIndex < 4) {
            printf("Enter Code: ");
            srvLCDCursor(0, 1);
        }
        while (inputCodeIndex < 4) {
            char key;
            scanf("%c", &key);
            if (key) {
                if (isdigit(key)) {
                    inputCode[inputCodeIndex++] = key;
                    printf("%c", key);
                }
            }
        }
      	inputCodeIndex = 5;
      	Serial.write("INPUT CODE: ");
      	Serial.write(inputCode);
      	Serial.write("\n");
        char key;
        scanf("%c", &key);
        while (!key) {
            scanf("%c", &key);
            if (key == 'B') {
                inputCode[inputCodeIndex] = '\0';
                if (strcmp(inputCode, correctCode) == 0) {
                    Serial.write("RESULT VALID: ");
                    Serial.write(inputCode);
                    Serial.write(" = ");
                    Serial.write(correctCode);
                    Serial.write("\n");
                    ledValid.on();
                    ledInvalid.off();
                    srvLCDClear();
                    printf("Code Valid!");
                    srvLCDCursor(0, 1);
                    printf("Acces Granted!");
                } else {
                    Serial.write("RESULT INVALID: ");
                    Serial.write(inputCode);
                    Serial.write(" != ");
                    Serial.write(correctCode);
                    Serial.write("\n");
                    ledInvalid.on();
                    ledValid.off();
                    srvLCDClear();
                    printf("Invalid!");
                    srvLCDCursor(0, 1);
                    printf("Acces Denied!");
                }
                delay(3000);
                srvLCDClear();
                inputCodeIndex = 0;
                for (int i = 0; i < 5; i++) {
                    inputCode[i] = 0;
                }
                ledInvalid.off();
                ledValid.off();
            }
        }
    }
}