# Lab-hot-plate
PID driven DIY Laboratory heat plate.

# Tests

Test snippets used (or not) to **calibrate** the Lab-Hot-Plate.

# Ziegler-Nichols Method

Ziegler-Nichols method is a common PID-tuning procedure, it involves some steps:

1. **Set I and D to 0**;
2. Find the ultimate gain **Ku** that causes continuous oscillations with constant amplitude.
3. Calculate values, where **Pu** is the period from a max value to the next,:

    ![tablegeneral](https://eng.libretexts.org/@api/deki/files/18138/image-308.jpeg?revision=1)
    ![tableConversion](https://eng.libretexts.org/@api/deki/files/18141/image-57.gif?revision=1)

    Kp = Kc <br>
    Ki = Kp / Ti <br>
    Kd = Kp × Td <br>


[libretexts](https://eng.libretexts.org/Bookshelves/Industrial_and_Systems_Engineering/Chemical_Process_Dynamics_and_Controls_(Woolf)/09%3A_Proportional-Integral-Derivative_(PID)_Control/9.03%3A_PID_Tuning_via_Classical_Methods)