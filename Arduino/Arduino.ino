#include "pico/stdio.h"
#include "pico/multicore.h"

int core1 = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

/*! \brief Main task
 *
 *
*/
void main_task() {
  while (true) {
    delay(5000);
    Serial.println("Test core 2");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!core1) {
    multicore_launch_core1(main_task);
    core1 = true;
  }


  delay(1000);
  Serial.println("Test");
}
