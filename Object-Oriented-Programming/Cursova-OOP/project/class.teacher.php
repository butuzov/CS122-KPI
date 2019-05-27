<?php
/**
 * Teacher - як репрезентація студенту
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */

namespace Cursova;

class Teacher extends Person implements Storable {

	public function __toString() : string {
		return $this->name();
	}

	public function hash() : string {
		return spl_object_hash( $this );
	}

	public function __debugInfo() {
		return [ 'teacher name' => $this->name() ];
	}

}
