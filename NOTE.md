# Notes 
## Todo
  - Serial interface
  - PM2.5 sensor calibration API
  - PM2.5 sensor measurement routine (e.g. how often do we recalibrate, what do
  we actually record?
  - Learn how to use ctags

## Useful links
  - [https://github.com/sudar/Arduino-Makefile/tree/master/examples]
  - [https://github.com/sudar/Arduino-Makefile/blob/master/examples/MakefileExample/Makefile-example.mk]

## Conversion formula

    1.Store a reference voltage (Vs) in the environment with less dust (for example clean box etc).
    or store a reference voltage (Vs) in the state that after a few minutes to stop the fan
    (state that dust fell by gravity).
    Note. The output voltage is Vo terminal (pin 2)
    2.In case that ⊿ voltage[mV] （Vo[mV] – Vs[mV]） is difference between the reference voltage(Vs)
    and the output voltage (Vo) when the fan turn on.
    It is possible to approximate the PM2.5 level by use following conversion formula.
    Conversion formula (draft):
    PM2.5 level (μg/m3) = α × β ×（Vo[mV] – Vs[mV]）
    Note. Do not temperature correction, an estimates in actual environment.
    α ： Conversion factor in the true environment
    Recommendation ： 0.6
    （β ： Humidity factor〔h=humidity(%)〕）
    〔 β ＝ {1-0.01467(h-50)} (h>50) 〕
    〔 β ＝ 1 (h≦50) 〕
