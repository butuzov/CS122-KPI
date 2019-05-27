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

class Notification implements Message {
	private $notification;
	private $type = 'notification';

	public function __construct( string $notification ) {
		$this->notification = $notification;
	}

	public function type() : string {
		return $this->type;
	}

	public function __tostring() : string {
		return $this->notification;
	}

	public function do( Student $student ) {
		// do nothing.
	}
}
