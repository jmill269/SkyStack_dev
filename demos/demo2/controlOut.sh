#!/bin/bash

 #File should be kept in same directory as this file.

programStart() {

	echo "Started Gimbal Control Program" >&2

	STOP='False'

	while [[ $STOP != 'True' ]]
		do

		echo "Start Controlling Gimbal" >&2
		echo "1 - Low Position" >&2
		echo "2 - Medium Position" >&2
		echo "3 - High Position">&2
		echo "0 - Stop Program" >&2
		read COMMAND

		if [[ $COMMAND -eq 0 ]]
		then
			$STOP=True
		fi
		if [[ $COMMAND -gt 4 ]]
		then
			echo "Command Input is Invalid." >&2
			echo "Please enter a value between 0 and 3" >&2
		else
			echo $COMMAND >&1 # This should be the only stdout.
		fi

	done
}

programStart | ./control_gimbal4.py
