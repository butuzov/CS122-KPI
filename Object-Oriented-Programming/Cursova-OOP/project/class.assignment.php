<?php
/**
 * Students - як репрезентація групи студентів
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */

namespace Cursova;

class Assignment implements Message {
	private $message;
	private $date;
	private $type = 'assignment';

	public function __construct( string $message, string $date ) {
		$this->message = $message;
		$this->date    = $date;
	}

	public function type() : string {
		return $this->type;
	}

	public function __tostring() : string {
		return sprintf( '[%s] %s', $this->date, $this->message );
	}

	public function do( Student $student ) {

		// do nothing.
		$student->prepare( $this->date );

	}
}
