# Recruits Task - Week #2
- ## [git para noobs](https://hackmd.io/@PedroRomao/HJ0GJSae1x)
- ## Add this file to your local git repository create a new branch and work on it, when you are done or as you complete the questions merge the branch into the main branch (remote main branch will have your final work, this means main branch on GitHub, please make the repository public for the next weeks).
- ## Perform the following tasks to the best of your hability, sometimes, in the questions, there are multiple answers just tell us what you think, feel free to use the group to ask questions.


### 1
**1.** Check out the [el-sw repository](https://github.com/fs-feup/el-sw/tree/main) code and documentation  and try to generally understand what the software does in each device (there is no need to understand all the little details).



### 2
When we read values from the brake sensor (C1) and the apps (C3) we do not use the most recent reading and use instead a different approach. Explain the approach and why you think it is used.

**Answer:** The approach used for both brake sensor (C1) and apps (C3) consists in reading the value in the sensor using the analogRead() function, afterwards allocating the most recent value in the last position of the buffer, due to the bufferInsert() function. After that, it is applied an average() function to calculate the average between all the values of the buffer. The reason why I think that approach is implemented is in order to minimize the erros when CAN receives the information, in case of wrong sensor readings due to unwanted interferences.


### 3
Check out the R2D(Ready To Drive) code on the C3 state machine. In the condition below we use a timer (R2DTimer) to check the brake was engaged instead of just checking the brake pressure received from can, why?
```c++
        if ((r2dButton.fell() and TSOn and R2DTimer < R2D_TIMEOUT) or R2DOverride)
        {
            playR2DSound();
            initBamocarD3();
            request_dataLOG_messages();
            R2DStatus = DRIVING;
            break;
        }
```

**Answer:** In order to set the car in R2D mode, we need to ensure that the brake was engaged for a certain amount of time, increasing the safety and reliability of the car. If we checked the brake pressure received, it would work based on the pressure value and not depending on duration, making it less safe.



### 4
What is the ID of the can message sent to the bamocar to request torque?
**Answer:** To find the ID of the can message sent to the bamocar to request torque I searched for a can message that requests the torque and I found the global variable `torqueRequest`, once this was found I checked where it was used and I found the ID was set in `torqueRequest.id = BAMO_COMMAND_I` and the value was 0x201. 




### 5 
The code below is not amazing, tell us some things you would change to improve it, you can write them down in text or correct the code:
```c++
// this is a class for my car
class mycar {
private:
    
    int sensor_reading9; // old sensor, not used anymore
    int[8] sensor_readings;  // Array with all eight sensor readings

public:
        mycar() : sensor_readings({0}) {}

    // Method will update readings by analog reading and print them 
    void updateprint() {
       

	for(int i=0; i < 8; i++)
  	{ 
 		sensor_readings[i] = analogRead(i);
	}
        func();// print the readings
    }

    // function to print the readings of the sensors
    void func() {
	for(int i=0; i < 8; i++)
  	{ 
 		Serial.print("Sensor Reading "); Serial.print(i+1); Serial.print(": "); Serial.println(sensor_readings[i]);
		
	}

                //all readings were serial printed
    }
};
```

