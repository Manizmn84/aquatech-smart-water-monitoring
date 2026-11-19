# Hardware assumptions and calibration

## Pin assignment

| Function | GPIO |
|---|---|
| DS18B20 data | 4 |
| CQRSENTDS01 analog signal | 34 |
| IR receiver analog circuit output | 35 |
| IR transmitter via series 470 ohm resistor, active high | 25 |
| OLED SDA / SCL | 21 / 22 |

Use a common ground. DS18B20 uses a DATA pull-up (typically 4.7 kohm to 3.3 V). GPIO34 and 35 have no internal pull resistors: a receiver circuit and connected TDS module are required. Floating analog inputs cannot reliably be identified in software; plausible readings do not prove a sensor is connected.

The demo uses GPIO25 -> 470 ohm -> IR LED anode, with LED cathode to GND; no transistor is required for this low-current trial. At nominal 3.3 V the resistor limits current to less than about 7 mA even ignoring the LED voltage drop. Confirm emitter identity and polarity before connecting. Optical strength is not guaranteed at this current.

The 5 mm receiver type and pin polarity remain unidentified. If confirmed to be an NPN phototransistor, use five 470 ohm resistors in series (2.35 kohm total) from 3.3 V to GPIO35/collector, with emitter to GND. This is a trial load, not a validated receiver design. Do not apply this pin assignment to an unidentified photodiode. No 5 V connection is used in the IR circuit. For a bare, externally powered three-wire DS18B20, two 1 kohm resistors in series provide a trial 2 kohm data pull-up to 3.3 V; omit them if the module already has its pull-up. Demo resistor inventory: six 470 ohm and two 1 kohm.

Fix geometry and shield the optical path from ambient light. Initial alternating dark/light settling time is 10 ms; verify and adjust it to the actual circuit. Signed light-minus-dark millivolts support either receiver polarity. The ADC has a finite measurable range; saturated or weak signals require circuit adjustments. Do not immerse bare IR parts or exposed conductors in water.

## TDS

Manufacturer documentation: https://cqrobot.wiki/info?articleId=120&title=TDS_(Total_Dissolved_Solids)_Meter_Sensor_SKU:_CQRSENTDS01

CQRSENTDS01 supply is 3.3–5.5 V; specified analog output is 0–2.3 V, range 0–1000 ppm. Use 3.3 V supply for initial integration. The implementation adapts the manufacturer's polynomial and 2%/degree compensation at 25 C using ESP32 calibrated millivolts rather than the UNO example's 10-bit ADC formula. Median window: 31 samples, sampled every 40 ms. No result is published before the window fills. Values outside the output/range limits or without a valid water temperature (0–55 C) return NaN. Zero voltage is ambiguous: it does not establish a connected probe.

TDS is an estimate requiring reference-solution calibration. In Settings.h set TDS_GAIN to reference ppm divided by the initial reported ppm in the reference solution, after stabilization with measured temperature. Repeat validation using another reference. The gain must be positive and finite. No independently measured EC is exposed. Do not use the probe above 55 C; only the probe and its lead are waterproof, not the transmitter board/connector.

## IR relative turbidity

Median filtering uses 15 paired light-minus-dark samples. Record the signed IR signal with clear water in fixed geometry, then with a repeatable turbid reference. Set TURBIDITY_CLEAR_MV and TURBIDITY_REFERENCE_MV in Settings.h. Defaults are NaN: relative percentage remains unavailable until configured. The two signals must differ by at least 1 mV. Percentage is a clamped linear relative index between these references, not NTU and not a validated concentration measurement. Changing container, alignment or receiver circuit invalidates these references. Quantitative NTU requires appropriate standards and a validated calibration curve.

## OLED and output

Assumption: SSD1306 128x64 I2C at 0x3C, no reset pin. The user confirmed only 0.96 inch yellow/blue; confirm controller, four-pin interface and resolution before wiring. Settings.h exposes address/height. Two-color panels assign colors physically; firmware uses monochrome pixels. Missing OLED at startup leaves Serial running. NaN appears as `--` on OLED and `nan` in CSV. A responding I2C address does not prove the controller is compatible. The driver does not recover automatically from later display disconnection.

Temperature conversion is asynchronous at 12 bits with a 750 ms wait. Reports are approximately once per second; ADC sampling is cooperative, so I2C rendering can introduce jitter. No hard real-time guarantee is claimed.

## Deferred hardware checks

Upload, confirm temperature and disconnection handling, verify receiver voltages and optical response, calibrate TDS and relative turbidity, confirm OLED controller/address, then test the combined system. None of these checks have been performed by this implementation. TDS/turbidity values alone do not certify drinking-water safety.
