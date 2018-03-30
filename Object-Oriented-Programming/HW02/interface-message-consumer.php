<?php

/**
 * Out "Observer" with update/process method called consume that accept Message.
 */
interface Message_Consumer {
	public function consume( Message $message );
}