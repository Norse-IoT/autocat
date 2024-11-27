# autocat
Automatically Feeds Cats

We have a circuit that cuts power to the 28BYJ48 motor and ULN2003AN driver board when it is not in use, to minimize overheating.

This uses a IRFZ44N N-Channel mosfet:
 - Gate: Pin 2 on esp32
 - Drain: Goes to the negative line on the ULN2003AN
 - Source: Goes to the negative line for the 9V power supply 

![PXL_20241127_030743353](https://github.com/user-attachments/assets/c9fa51be-bad1-4d0b-907f-0fe50c543f0a)
