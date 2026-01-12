#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;
Servo myservo1;

int pos = 0;

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

int tempo = 140;
int buzzer = 10;

int melody[] = {
    NOTE_C5, 4, NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4, NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4, NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8,
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

unsigned long startMillis = 0;
unsigned long lastMillis = 0;
unsigned long timeInSeconds = 0;
unsigned long updateInterval = 1000;
bool timeSet = false;
int LED = 2;

void setup() {
    lcd.begin(16, 2);
    lcd.print("Astept timp...");
    Serial.begin(9600);
    myservo.attach(9);
    myservo1.attach(3);
    pinMode(LED, OUTPUT);
}

void loop() {
    if (!timeSet && Serial.available() > 0) {
        String timeString = Serial.readStringUntil('\n');

        if (timeString.length() == 8 && timeString.charAt(2) == ':' && timeString.charAt(5) == ':') {
            int hours = timeString.substring(0, 2).toInt();
            int minutes = timeString.substring(3, 5).toInt();
            int seconds = timeString.substring(6, 8).toInt();

            timeInSeconds = (unsigned long)hours * 3600 + (unsigned long)minutes * 60 + (unsigned long)seconds;
            startMillis = millis();
            timeSet = true;

            lcd.clear();
            lcd.print("Timp sincronizat");
            delay(2000);
            lcd.clear();
        } else {
            Serial.println("Eroare: format invalid");
            lcd.setCursor(0, 0);
            lcd.print("Eroare format!");
            delay(2000);
            lcd.clear();
        }
    }

    if (timeSet) {
        if (millis() - lastMillis >= updateInterval) {
            lastMillis = millis();
            timeInSeconds += 1;

            int hours = (timeInSeconds / 3600) % 24;
            int minutes = (timeInSeconds / 60) % 60;
            int seconds = timeInSeconds % 60;

            lcd.setCursor(0, 0);
            lcd.print("Ora curenta:   ");

            lcd.setCursor(0, 1);
            if (hours < 10) lcd.print("0");
            lcd.print(hours);
            lcd.print(":");
            if (minutes < 10) lcd.print("0");
            lcd.print(minutes);

            if (hours == 20 && minutes == 58 && seconds == 1) {
                digitalWrite(LED, HIGH);
                for (int thisNote = 0; thisNote < notes / 2; thisNote += 2) {
                    divider = melody[thisNote + 1];
                    noteDuration = (divider > 0) ? (wholenote / divider) : (wholenote / abs(divider)) * 1.5;
                    tone(buzzer, melody[thisNote], noteDuration * 0.9);
                    delay(noteDuration);
                    noTone(buzzer);
                }
                digitalWrite(LED, LOW);
                for (pos = 0; pos <= 180; pos++) {
                    myservo.write(pos);
                    delay(15);
                }
                for (pos = 180; pos >= 0; pos--) {
                    myservo.write(pos);
                    delay(15);
                }
                timeInSeconds += 20;
            }
           if (hours == 6 && minutes == 58 && seconds == 1) {
                digitalWrite(LED, HIGH);
                for (int thisNote = 0; thisNote < notes / 2; thisNote += 2) {
                    divider = melody[thisNote + 1];
                    noteDuration = (divider > 0) ? (wholenote / divider) : (wholenote / abs(divider)) * 1.5;
                    tone(buzzer, melody[thisNote], noteDuration * 0.9);
                    delay(noteDuration);
                    noTone(buzzer);
                }
                digitalWrite(LED, LOW);
                for (pos = 0; pos <= 180; pos++) {
                    myservo.write(pos);
                    delay(15);
                }
                for (pos = 180; pos >= 0; pos--) {
                    myservo.write(pos);
                    delay(15);
                }
                timeInSeconds += 20;
           }
        }
    }
}
