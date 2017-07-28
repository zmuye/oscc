/**
 * @file accumulator.cpp
 *
 */


#include <Arduino.h>
#include "vehicles.h"

#include "globals.h"
#include "accumulator.h"
#include "helper.h"
#include "debug.h"


void accumulator_init( void )
{
    pinMode( PIN_ACCUMULATOR_PUMP_MOTOR, OUTPUT );

    accumulator_turn_pump_off( );
}


void accumulator_turn_pump_off( void )
{
    digitalWrite( PIN_ACCUMULATOR_PUMP_MOTOR, LOW );
}


void accumulator_turn_pump_on( void )
{
    digitalWrite( PIN_ACCUMULATOR_PUMP_MOTOR, HIGH );
}


float accumulator_read_pressure( void )
{
    int raw_adc = analogRead( PIN_ACCUMULATOR_PRESSURE_SENSOR );

    float pressure = raw_adc_to_pressure( raw_adc );

    return pressure;
}


void accumulator_maintain_pressure( void )
{
    float pressure = accumulator_read_pressure( );

    if ( pressure <= BRAKE_ACCUMULATOR_PRESSURE_MIN_IN_DECIBARS )
    {
        accumulator_turn_pump_on( );
    }
    else if ( pressure >= BRAKE_ACCUMULATOR_PRESSURE_MAX_IN_DECIBARS )
    {
        accumulator_turn_pump_off( );
    }
}
