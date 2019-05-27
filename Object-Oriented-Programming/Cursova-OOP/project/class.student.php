<?php
/**
 * Student - як репрезентація студенту
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */

namespace Cursova;

class Student extends Person implements Storable, Observer {

	public function __toString() : string {
		return $this->name();
	}

	public function hash() : string {
		return spl_object_hash( $this );
	}

	public function __debugInfo() {
		return [ 'name' => $this->name() ];
	}

	// ----------------------------------------------------------------
	// Observer Notifications.

	public function receive_notification( Message $message ) {
		$formatter = "\n[%s] got %s: %s\n";
		printf( $formatter, $this->name(), $message->type(), $message );

		$message->do( $this );
	}


	public function prepare( string $date ) {
		printf( "[%s] почав готуватись якусь роботу до %s\n", $this->name(), $date );
	}

}
