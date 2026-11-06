#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// =================================
// ESP32 PIN CONFIGURATION
// =================================

#define LCD_SDA 21
#define LCD_SCL 22

#define GREEN_LED 13
#define RED_LED 14
#define BUZZER 27

// =================================
// LCD CONFIGURATION
// =================================

// Common I2C address: 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Time each item is displayed
const unsigned long DISPLAY_TIME = 2500;

// =================================
// FRUITS LIST
// =================================

const char* fruits[] = {
  "Apple",
  "Banana",
  "Mango",
  "Orange",
  "Grapes",
  "Papaya",
  "Watermelon",
  "Pineapple"
};

// =================================
// VEGETABLES LIST
// =================================

const char* vegetables[] = {
  "Carrot",
  "Potato",
  "Tomato",
  "Onion",
  "Cabbage",
  "Brinjal",
  "Spinach",
  "Cauliflower"
};

const int fruitCount =
  sizeof(fruits) / sizeof(fruits[0]);

const int vegetableCount =
  sizeof(vegetables) / sizeof(vegetables[0]);

// =================================
// WELCOME MESSAGE
// =================================

void showWelcome() {

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Hi!");

  lcd.setCursor(0, 1);
  lcd.print("Welcome!");

  delay(2000);
}

// =================================
// DISPLAY FRUIT
// GREEN LED ON, BUZZER OFF
// =================================

void showFruit(const char* name) {

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Fruit:");

  lcd.setCursor(0, 1);
  lcd.print(name);

  Serial.print("FRUIT: ");
  Serial.println(name);

  delay(DISPLAY_TIME);

  digitalWrite(GREEN_LED, LOW);
}

// =================================
// DISPLAY VEGETABLE
// RED LED ON, BUZZER ON
// =================================

void showVegetable(const char* name) {

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Vegetable:");

  lcd.setCursor(0, 1);
  lcd.print(name);

  Serial.print("VEGETABLE: ");
  Serial.println(name);

  // Active buzzer controlled through transistor
  digitalWrite(BUZZER, HIGH);

  delay(DISPLAY_TIME);

  digitalWrite(BUZZER, LOW);
  digitalWrite(RED_LED, LOW);
}

// =================================
// SETUP
// =================================

void setup() {

  Serial.begin(115200);

  // Configure output pins
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Initially turn everything OFF
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  // Initialize I2C
  Wire.begin(LCD_SDA, LCD_SCL);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  Serial.println("ESP32 Starting...");

  // Show welcome message
  showWelcome();

  Serial.println("Fruit and Vegetable System Started!");
}

// =================================
// MAIN LOOP
// =================================

void loop() {

  // STEP 1: DISPLAY ALL FRUITS

  for (int i = 0; i < fruitCount; i++) {

    showFruit(fruits[i]);

  }

  // STEP 2: DISPLAY ALL VEGETABLES

  for (int i = 0; i < vegetableCount; i++) {

    showVegetable(vegetables[i]);

  }

  // STEP 3: REPEAT AUTOMATICALLY

}
