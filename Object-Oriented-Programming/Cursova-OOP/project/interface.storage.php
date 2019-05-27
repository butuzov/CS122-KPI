<?php
/**
 * Storage - defined objects unique storage interface behaviour.
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */

namespace Cursova;

interface Storage {

	public function push( Storable $item );
	public function pull( int $id ) : Storable;

	// return id in local data storage
	public function id( Storable $item ) : int;

	// check existance of object in local storage
	public function exists( Storable $item ) : bool;

	// removal functions
	public function remove( Storable $item );

	// empty storage check
	public function is_empty() : bool;

	// size of storage
	public function length() : int;


}
