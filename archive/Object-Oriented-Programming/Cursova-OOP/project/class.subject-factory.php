<?php
/**
 * Subjects - представлення предметів на поточному крусі
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */


namespace Cursova;

class Subject_Factory {

	public function __construct( array $arguments ) {
		$this->name    = $arguments['name'];
		$this->teacher = new Teacher( $arguments['teacher']['name'] );
	}

	public function create() : Subject {
		return new Subject( $this->name, $this->teacher );
	}
}
