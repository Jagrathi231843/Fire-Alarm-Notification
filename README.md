# Fire-Alarm-Notification
Build a Fire Alarm System using Arduino, LM35 Temperature Sensor and GSM Module
We are going to build a Fire Alarm System using **Arduino, LM35 Temperature Sensor and GSM Module**. The objectives of this fire detector using arduino is to sense the surroundings for occurrence of fire with help of LM35 temperature sensor, and send 3 SMS alerts to two mobile numbers stored inside the arduino program if fire is detected (using GSM Module).
1. SMS based Fire Alarm system are very useful in remote locations where human interaction is limited. Such systems are useful in mines, industrial areas, factories etc.

2. Night Owl – We all know owls don’t sleep during night. SMS based Fire Alarm system helps to monitor locations and alert during fire that occurs in night time.

3. Quick Actions to shut down Fire – 90% of fire damages occur due to lack of early fire detection. A fire attack is usually silent and people will know about fire only when it has spread across a large area. SMS based Fire Alert system gives warning immediately to multiple mobile numbers and hence remedy actions can be taken quickly. This helps to prevent major damages and losses created by a fire accident.

The circuit connections of this arduino fire alarm are very simple to understand and implement. If you are a beginner, read the following tutorials to grasp connections perfectly.

1. **LM35 Temperature Sensor and Arduino** – Interfacing Arduino with fire sensor LM35- read this tutorial to learn how to connect LM35 and Arduino

2. **GSM Module and Arduino** – read this tutorial to learn how to send SMS using Arduino and GSM Module

3. **LCD and Arduino** – read this tutorial to learn how to connect 16×2 LCD module to Arduino

**Important Aspects of the Program**

When we develop Fire Alarm Systems or such critical systems, the one important aspect we have to keep in mind is the real world scenario. A “fire” can occur any time (24×7). This means our system must constantly monitor fire 24×7 all the month and year. If you look into the program, you will see it has only 2 function calls inside **void loop() – that is CheckFire() and CheckShutDown()**

**CheckFire()** – is the function which monitors occurrence of a fire 24×7.  This function fetches the temperature measured by LM35 and stores it to the variable **Temp_alert_val** for comparison. This temperature value is compared against a set value of 45 degree Celsius. Usually room temperature is between 25 degree Celsius and 30 degree Celsius in tropical areas. This will vary with continents and locations. You have to change this comparison value by measuring the average room temperature of the installation site!

If fire occurs, room temperature will cross 45 degrees (within seconds) and an inner subroutine **SetAlert()** will be invoked. **SetAlert()** is the function that controls number of SMS alerts sent to each mobile number loaded in the program. The number of SMS alerts sent can be altered by changing the stopping condition of while loop. The stopping condition **sms_count<3** – means 3 SMS alerts will be sent to each mobile number. If you want to send 5 alerts, just change the stopping condition to sms_count<5 – you got it ?  The function to send SMS (using AT Commands) – **SendTextMessage()** will be called 3 times if SMS alert count is 3. This function SendTextMessage() will be invoked as many times as the number SMS alerts set in the program.

Note:- We have limited the number of SMS alerts using the stopping condition. Once a fire accident occurs and the set number of SMS alerts has been sent, the system will not send any more SMS! The system assumes that its job is over by sending SMS. Humans has to come and shut down the fire. After sending alerts, the system will start monitoring Shut Down process. Once the Fire has been shut down, system will reactivate its SMS alert settings by resetting the sms_count variable back to zero.

**CheckShutDown()** – is the function which monitors if fire was shut down. We need to entertain this function only if a fire accident has occurred. To limit the entry to the statements inside this routine, we have introduced a variable **Fire_Set**. This variable status will be set to value 1 when a fire accident occurs (check the statement inside SetAlert()). The statements inside **CheckShutDown()** will  be executed only if the value of **Fire_Set==1**. (If not there was no fire accident and we don’t need to waste time executing ShutDown checking statements). We consider the fire has been shut down once room temperature is back to normal. So if our variable **Temp_shut_val** falls less than 28 degrees, we consider fire has been shut and things are safe. We start our FireAlarm monitoring again with SMS Alerts active! (We reset the Fire_Set variable and sms_count variable back to zero – which are conditions of normal room status)
