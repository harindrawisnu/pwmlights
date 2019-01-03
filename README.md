# pwmlights
Simple lights for RC model
2 PWM input channel ranging from 1000-2000ms
4 output channel for primary light, secondary light, right turn light and left turn light

# first channel for main light control
on low signal (below 1250ms) all light will turned off
on center signal (between 1250ms to 1750ms) only secondary lights will be turned on
on high signal (above 1750ms) all lights will be turned on

# second channel for turn light control
on low signal (below 1250ms) left light will blinking, right light will be turned off
on center signal (between 1250ms to 1750ms) all turn lights will be turned off
on high signal (above 1750ms) right light will blinking, left light will be turned off
