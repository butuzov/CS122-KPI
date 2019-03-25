<?php

interface Message {
	/**
	 * Explicit Message as string formatter.
	 * @return string
	 */
	public function format() : string;

	/**
	 * Implicit Message as string formatter.
	 * @return string
	 */
	public function __toString() : string ;
}