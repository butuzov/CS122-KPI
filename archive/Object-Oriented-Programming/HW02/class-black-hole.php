<?php

class Black_Hole implements Message_Consumer {
	public function consume( Message $message ) {
		echo "Consumer BH: ", $message, "\n";
	}
}