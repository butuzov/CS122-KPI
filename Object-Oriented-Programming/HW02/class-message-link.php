<?php

class Message_Link implements Message {
	private $text;
	private $link;

	private $format_link = '[%2$s](%1$s)';
	private $format_text = '%1$s';

	public function __construct( string $text, string $link ) {
		$this->text = $text;
		$this->link = $link;
		// Should I add by default some fromatter calss here? dunno.
	}

	public function format() :string {
		if ( empty( $this->link ) ) {
			return sprintf( $this->format_text, $this->text );
		}
 		return sprintf( $this->format_link, $this->link, $this->text );
	}

	public function __toString() : string {
		return $this->format();
	}
}