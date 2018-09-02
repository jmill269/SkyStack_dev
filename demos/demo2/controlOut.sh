#!/bin/bash

 #File should be kept in same directory as this file.

<<<<<<< HEAD
python2 control_gimbal4.py & #File should be kept in same directory as this file.
=======
programStart() {
>>>>>>> 50ad2116d48d7c801be0ee44d5bea5393c038b30

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

<<<<<<< HEAD
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
=======
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
>>>>>>> 50ad2116d48d7c801be0ee44d5bea5393c038b30

programStart | ./control_gimbal4.py
