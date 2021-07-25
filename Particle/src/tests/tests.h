#include "PinConfig.h"
#include <Arduino.h>


#define RUN_TEST(test_func) run_test(test_func, #test_func)
#define TEST_FAIL_MESSAGE(msg) return (Serial.printf("TEST FAILED: %s\n", msg), false)

#define TEST_ASSERT_NULL(ptr) if (ptr != NULL) TEST_FAIL_MESSAGE("Pointer not NULL")
#define TEST_ASSERT_EQUAL_STRING(str1, str2) if (strcmp(str1, str2)) TEST_FAIL_MESSAGE("Strings not equal: " str1 "!=" str2)
#define TEST_ASSERT_TRUE(cond) if (!cond) TEST_FAIL_MESSAGE(#cond " IS FALSE")

#if EN_GSM
#include "Gsm.h"
extern Gsm gsm;
#endif

#if CURRENT
#include "Current.h"
extern Current hall_effect;
#endif

#if VOLTAGE
#include "Voltage.h"
extern Voltage volt_divider;
#endif

#if TEMPERATURE
#include "Temperature.h"
extern Temperature thermocouple; //pretty slow response and depends greatly on the surface temperature of the thermocouple tip
#endif

#if FLOW
#include "Flow.h"
extern Flow waterflow;
#endif

#include "RealTimeClock.h"
extern RealTimeClock rtc;

#if SDCARD
#include "SdCard.h"
extern SdCard memory;
#endif

void tests(); 
void run_test(bool (*test)(), char *test_name);
void printTestStart(String tag);
void printTestEnd(String tag);
void printTestFailed(String tag);
void printTestPassed(String tag);
