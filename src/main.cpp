#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// LCD:
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD Object 0x3F or 0x27
// Encoder rotativo:
#define pin_CLK 13 // gpio ahora el 13
#define pin_DT 12  // gpio 12
#define pin_SW 14   // gpio 14
int encoder_contador = 0, state_CLK = 0, state_CLK_ans = 0, state_DT = 0, state_DT_ans = 0;
char encoder_dir = ' ';
bool state_boton = false;

void fnc_encoder()
{
  // Encoder rotativo:
  state_CLK = digitalRead(pin_CLK);
  state_DT = digitalRead(pin_DT);
  if (state_CLK != state_CLK_ans && state_DT == 0 && state_CLK == 1) // 1 paso derecha. CLK,DT=0,1 a 0,0.
  {
    encoder_contador = encoder_contador + 1;
    encoder_dir = '>'; // Rotacion horaria.
  }
  if (state_CLK != state_CLK_ans && state_DT == 1 && state_CLK == 0) // 1 paso derecha. CLK,DT=1,0 a 1,1.
  {
    encoder_contador = encoder_contador + 1;
    encoder_dir = '>'; // Rotacion horaria.
  }
  
  if (state_CLK != state_CLK_ans && state_CLK == 1 && state_DT == 1) // 1 paso izquierda. CLK,DT=1,0 a 0,0.
  {
    encoder_contador = encoder_contador - 1;
    encoder_dir = '<'; // Rotacion anti_horaria.
  }
  if (state_CLK != state_CLK_ans && state_CLK == 0 && state_DT == 0) // 1 paso izquierda. CLK,DT=0,1 a 1,1.
  {
    encoder_contador = encoder_contador - 1;
    encoder_dir = '<'; // Rotacion anti_horaria.
  }
  state_CLK_ans = state_CLK;
  state_DT_ans = state_DT;
  state_boton = digitalRead(pin_SW);
  if (state_boton == false)
  {
    lcd.setCursor(8, 0);
    lcd.print("OFF");
  }
  else
  {
    lcd.setCursor(8, 0);
    lcd.print("ON ");
  }
  lcd.setCursor(0,0);
  lcd.print("    "); //Borra texto en lugar seleccionado.
  lcd.setCursor(0,0);
  lcd.print(encoder_dir);
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.setCursor(0,1);
  lcd.print(encoder_contador);
}

void setup()
{
  // Inicia Encoder rotativo:
  pinMode(pin_CLK, INPUT);
  pinMode(pin_DT, INPUT);
  pinMode(pin_SW, INPUT_PULLUP);
  state_CLK_ans = digitalRead(pin_CLK);

  // Inicia LCD:
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  fnc_encoder();
  delay(1);
}