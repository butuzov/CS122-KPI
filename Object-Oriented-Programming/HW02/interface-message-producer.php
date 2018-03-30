<?php

interface Message_Producer {
	public function get() : Message;
	public function next() : bool;
}