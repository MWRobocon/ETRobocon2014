SPHERO CONNECTIVITY PACKAGE

This package allows us to connect a computer to a Sphero device, and communicate with it from within MATLAB.

------------------------------------------------------------------------------------------------------------------

ABOUT THE SPHERO:

Sphero is a robotic platform developed by orbotix, which can be controlled using a smartphone, tablet or other devices via Bluetooth. It is shaped similar to a call, which allows it to roll in any direction. For more information on the sphero, and in order to buy it, please refer to the following page: http://www.gosphero.com/

GETTING STARTED:

The Sphero comes with a Quick Start Guide, which describes how we can connect to a Sphero through an iOS or Android device. For general FAQs, please refer to this page: https://sphero.zendesk.com/home

------------------------------------------------------------------------------------------------------------------

PACKAGE INSTALLATION

When installing the Sphero Connectivity package on your operating system it is important that users have the right to modify the pathdef.m file.


ON LINUX:
---------

To make sure that the pathdef.m file is writable, issue a command like this: 
sudo chmod 777 usr/local/matlab/R2014a/toolbox/local/pathdef.m
(modify the path above according to where MATLAB is installed). 

Then from MATLAB, launch the "install_sphero" command. This will add the relevant Sphero folders to the MATLAB path and save the path. 


ON WINDOWS:
-----------

Run MATLAB as administrator (just one time for the purpose of installing the package) by right-clicking on the MATLAB icon and selecting "Run as Administrator". This will allow the updated path to be saved.

Then from MATLAB, launch the "install_sphero" command. This will add the relevant Sphero folders to the MATLAB path and save the path. 

------------------------------------------------------------------------------------------------------------------

OPEN EXAMPLES

In order to open the examples for the Sphero Connectivity Package, please run the following command at the MATLAB Command Prompt:
open('sphero_examples.html')
