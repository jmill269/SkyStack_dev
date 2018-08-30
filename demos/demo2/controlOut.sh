#!/bin/bash


python2 control_gimbal4.py & #File should be kept in same directory as this file.

echo "Started Gimbal Control Program"

STOP='False'

while [[ $STOP != 'True' ]]
do

	echo "Start Controlling Gimbal"
	echo "1 - Low Position"
	echo "2 - Medium Position"
	echo "3 - High Position"
	echo "0 - Stop Program"
	read -p 'Please Enter Your Command' COMMAND

	if [ $COMMAND -eq 0 ]
	then
		$STOP=True
	fi
	if [ $COMMAND -gt 4 ]
	then
		echo "Command Input is Invalid."
		echo "Please enter a value between 0 and 3"
	else

		echo $COMMAND | control_gimbal4.py
	fi
done

