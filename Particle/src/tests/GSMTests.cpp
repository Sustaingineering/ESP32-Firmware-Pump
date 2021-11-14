#include "GSMTests.h"
#if GSM_SWITCH == 1

String message1 = "313.311,314.31,315.31,316.31,317.31,1617476161";
String message2 = "312.311,314.31,315.31,316.31,317.31,1617476162";

// 60 characters defined as max message length
String maxLengthMessage = "9999.9999,9999.9999,9999.9999,9999.9999,9999.999,1617476162";
String greaterThanMaxMessage = "9999.9999,9999.9999,9999.9999,9999.9999,9999.9999,1617476162";

bool testPublishInterval()
{
    String testTag = "PUBLISH INTERVAL";
    printTestStart(testTag);

    bool isPublished = false;    
    int lastPublishTime;
    int publishCount = 0;
    
    while(!isPublished) {
        delay(1000);
        isPublished = !(gsm.Publish(String(0), message1).equals(String("")));
        publishCount++;
        Serial.printf("Published %d times so far (loop 1)\n", publishCount);
    }

    Serial.println("Exited loop 1, updating lastPublishTime variable");
    lastPublishTime = rtc.getTimeStamp().toInt();

    isPublished = false;
    int newPublishTime;
    publishCount = 0;

    while(!isPublished) {
        delay(1000);
        isPublished = !(gsm.Publish(String(0), message2).equals(String("")));
        publishCount++;
        Serial.printf("Published %d times so far (loop 2)\n", publishCount);
    }

    Serial.println("Exited loop 2, updating newPublishTime variable");
    newPublishTime = rtc.getTimeStamp().toInt();

    Serial.println("Checking for difference in recorded times");
    if ((double)(newPublishTime - lastPublishTime) < MIN_PUBLISH_INTERVAL) {
        Serial.printf("newPublishTime: %d\n", newPublishTime);
        Serial.printf("lastPublishTime:, %d\n", lastPublishTime);
        printTestFailed(testTag);
        return false;
    }
    
    printTestPassed(testTag);
    return true;
}

bool testPublishLength()
{
    String testTag = "PUBLISH LENGTH";
    printTestStart(testTag);

    bool isPublished = false;    
    int publishCount = 0;
    String result;

    while(!isPublished) {
        delay(1000);
        result = gsm.Publish(String(0), maxLengthMessage);
        isPublished = !(result.equals(""));
        publishCount++;
        Serial.printf("Published %d times so far (loop 1)\n", publishCount);
    }

    if (strlen(result.c_str()) > MAX_BYTES_PER_OPERATION){
        printTestFailed(testTag);
        return false;
    }

    printTestPassed(testTag);
    return true;
}

void testGsm(){
    testPublishInterval();
    testPublishLength();
}

#endif