<?php
/**
 * Person - як репрезентація людини
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */

namespace Cursova;

use StdClass;

class Person extends stdClass {
	protected $name;

	public function __construct( string $name ) {
		$this->name = $name;
	}

	public function name() : string {
		return $this->name;
	}

}
