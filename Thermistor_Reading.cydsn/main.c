/* ========================================
 *
 * PSoC Thermistor lab
 * Luke Falls 
 * 10/29/2023
 * ========================================
*/
// The following setting must be made to use the math.h and float.h libraries
// Project--> Build Settings--> Linker--> General--> Additional Libraries: m
#include "project.h"    // Automatically generated code defines the chip being used
#include "math.h"       // Math functions
#include "float.h"      // Floating point routines

// Global variable declarations
uint32 loop_counter, LCD_write_counter, thermistor_R;
uint16 R_1_result, thermistor_result;
int16 thermistor_mv, R_1_mv, temperature, temperature_F;
float R_1_result_f, R_1_mv_f, thermistor_mv_f, ratio_f, voltage_f;
float thermistor_RA_f, thermistor_RB_f;
float current_mA_f, temperature_K_f, temperature_C_f;

int main(void)
{
    // Automatically generated
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Enable the peripherals
    ADC_DelSig_1_Start();
    AMux_1_Start();
    
    // Start the LCD
    LCD_Start();
    
    // Test the LCD
    LCD_Position(0,0);
    LCD_PrintString("Thermistor Test");
    CyDelay(1000);  //Delay 1000 ms (1 second)
    
    // Reposition to overwrite the test string
    LCD_Position(0,0);

    //.......................... Start of Infinite Loop ..........................//
    
    while(1)
    {
        // Verify that the code is running by displaying this variable on the LCD
        loop_counter++;
        
        // This will skip excessive wrting to the LCD.
        LCD_write_counter++;
        
        // Use this digital output with a scope to determine the loop time
        P3_5_Write(1);
        
        //******************** Select the mux input for the 10k resistor******************************//
        AMux_1_Select(0);
        
        // Start doing ADC conversions
        ADC_DelSig_1_StartConvert();
        
        // Code execution stops here until the conversion is complete
        ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);
        
        // Conversion is complete so reset the I/O pin so I can see how long the conversion took with a scope
        P3_5_Write(0);
        
        // Get the 16 bit result from the ADC result register
        R_1_result = ADC_DelSig_1_GetResult16();
        
        // Cast the result into a floating point format
        R_1_result_f = (float)R_1_result;
        
        // Convert the result to millivolts*1000 (450 = .450 mV; 4500 = 4.5 mV) and cast to an int
        R_1_mv = (int16)ADC_DelSig_1_CountsTo_mVolts(R_1_result);
        
        // Cast the int value of mV to floating point
        R_1_mv_f = (float)R_1_mv;
        
        //Calculate the current in mA through the 10k resistor
        current_mA_f = R_1_mv_f / 10000;
        
        //******************** Select the mux input for the thermistor voltage ***********************//
        AMux_1_Select(1);
        
        // Start doing ADC conversions
        ADC_DelSig_1_StartConvert();
        
        // Code execution stops here until the conversion is complete
        ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);
        
        // Get the raw thermistor digital 16 bit result from the ADC result register
        thermistor_result = ADC_DelSig_1_GetResult16();
                
        // Convert the result to millivolts*1000 (450 = .450 mV; 4500 = 4.5 mV) and cast to an int
        thermistor_mv = (int16)ADC_DelSig_1_CountsTo_mVolts(thermistor_result);
        
        // Cast the int value of mV to floating point
        thermistor_mv_f = (float)thermistor_mv;
        
        // Calculate the resistance manually using R = V/I
        thermistor_RA_f = thermistor_mv_f / current_mA_f;
        
        // Calculate the resistance using the built in function that is part of the thermistor module
        thermistor_R = Ametherm_1DC103K_EC_GetResistance(R_1_mv, thermistor_mv);
        
        // Cast the previous value into a float. This should be the same as thermistor_RA_f
        thermistor_RB_f = (float)thermistor_R;
        
        // Get the computed temperature in degrees C *100 from the thermistor API
        temperature = Ametherm_1DC103K_EC_GetTemperature(thermistor_R);
        
        // Convert C to F
       temperature_F = temperature * 9/5 + 3200;
        
        //********************************* Write to the LCD ************************************//
        if(LCD_write_counter++ > 1000)
        {
            LCD_write_counter = 0;          // Reset the write counter
            P3_6_Write(1);                  // Toggle bit 0 for monitoring LCD write time
            LCD_IsReady();                  // Built in function from the LCD API
            
            LCD_Position(0,0);              // Move to the first line
            LCD_PrintString("      degrees C ");
            LCD_Position(0,0);              // Move back to the first character
            LCD_PrintNumber(temperature/100);   // Print the whole number portion
            LCD_Position(0,2);              // Move to the fourth position since the temperature takes up 3 digits
            LCD_PrintString(".");
            LCD_PrintNumber(temperature % 100); // Get the decimal portion of the temperature
            
            //LCD_Position(0,0);              // Move to the first line
            //LCD_PrintString("loop cnt:       ");    // Set up to display the loop count
            //LCD_Position(0,10);             // Move to one space after the colon
            //LCD_PrintU32Number(loop_counter);       // Print the loop count
            
            LCD_Position(1,0);              // Move to the next line
            LCD_PrintString("      degrees F ");
            LCD_Position(1,0);              // Move back to the first character
            LCD_PrintNumber(temperature_F/100);   // Print the whole number portion
            LCD_Position(1,2);              // Move to the fourth position since the temperature takes up 3 digits
            LCD_PrintString(".");
            LCD_PrintNumber(temperature_F % 100); // Get the decimal portion of the temperature
            
            P3_6_Write(0);                  // Toggle bit 0 for monitoring LCD write time
            
        }
    }
    
    
    /*for(;;)
    {
       
    }*/
}

/* [] END OF FILE */
