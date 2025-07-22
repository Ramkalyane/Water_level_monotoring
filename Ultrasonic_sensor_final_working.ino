#define TRIG_PIN D3
#define ECHO_PIN D1
#define PIN D5
#define BUTTON_PIN D6

bool button_presses = true;
bool min_distance = true;
bool max_distance = true;
bool led_turn_on = false;
int upper_distance = 10;
int lower_distance = 100;
bool timer_on = false;
int button_press_start_time = 0;
int button_press_duration = 0;

void Check_Button_Pressed(void);

void setup() {
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void loop() {
    long duration, distance;
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration / 2) / 29.1; // Divide by 29.1 or 58 to convert microseconds to centimeters or inches respectively

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    Check_Button_Pressed();

  Serial.print("Lower Distance: ");
  Serial.print(lower_distance);  
  
  if(distance < upper_distance && min_distance){
    min_distance = false;
    max_distance = true;
    led_turn_on  = true;
    Serial.print("Minimum: ");
  }else if(distance > lower_distance && max_distance){
    max_distance = false;
    min_distance = true;
    led_turn_on = true;
    Serial.print("Maximum: ");
  }

  Serial.print("Led tuen on = ");
  Serial.println(led_turn_on);
  
  Serial.print("button_presses = ");
  Serial.println(button_presses);

  if(led_turn_on && button_presses){
    Serial.print("LEDTURNED ON\n");
    digitalWrite(D4, HIGH);
  }
  else
  {
    digitalWrite(D4, LOW);
  }

    delay(1000); // Delay for stability
}

void Check_Button_Pressed(void)
{

  if(digitalRead(BUTTON_PIN) == LOW){
    Serial.print("Button pressed\n");

    if(timer_on)
    {
      lower_distance = lower_distance + 50;
    }
    if (button_presses)
    {
      button_press_start_time = millis(); // Start timing
      button_presses = false;   // button_presses = false;
      Serial.print("led turn on false\n");
      led_turn_on = false;
    } 
    else 
    {
        button_press_duration = millis() - button_press_start_time; // Calculate duration
        if (button_press_duration >= 10000) 
        { // Check if pressed for 10 seconds
            digitalWrite(D4, HIGH);
            timer_on = true;
            lower_distance = 100;
            delay(2000);
            digitalWrite(D4, LOW);
            button_press_start_time = 0; // Reset the timer
            button_press_duration = 0;
        }
        else
        {
          //timer_on = false;
        }
    }
  }
  else
  {
    button_presses = true;
    digitalWrite(D4, LOW);
  }
}

