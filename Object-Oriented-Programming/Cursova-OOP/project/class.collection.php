<?php
/**
 * Collection - default data structure based on ArrayObject
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */

namespace Cursova;

class Collection extends \ArrayObject implements Storage {

	// map[hash]id
	private $hashes;

	public function __construct() {
		$this->hashes = [];
	}

	public function push( Storable $object ) {
		if ( $this->exists( $object ) ) {
			return;
		}

		$this->append( $object );
		if ( -1 === ( $id = $this->id( $object ) ) ) {
			throw new \AssertionError( 'Item not added' );
		}
	}

	// return item from the storage by id.
	public function pull( int $index ) : Storable {
		if ( $this->offsetExists( $index ) ) {
			return $this->offsetGet( $index );
		}
		throw new \OutOfBoundsException( 'Item not found' );
	}

	// Existance Check
	public function exists( Storable $object ) : bool {
		return isset( $this->hashes[ $object->hash() ] );
	}

	// retrive / updates object id hash map.
	public function id( Storable $object ) : int {
		// case 1 - object in the hash map.
		if ( isset( $this->hashes[ $object->hash() ] ) ) {
			return $this->hashes[ $object->hash() ];
		}

		// case 2 - object not in the hash map, so we need
		// to find it and create key entry.
		foreach ( $this as $key => $item ) {
			if ( $item === $object ) {
				$this->hashes[ $object->hash() ] = $key;
				return $key;
				break;
			}
		}
		return -1;
	}

	public function remove( Storable $object ) {
		if ( -1 !== ( $id = $this->id( $object ) ) ) {
			$this->remove_hash( $object );
			$this->offsetUnset( $id );
		}
	}

	public function remove_hash( Storable $object ) {
		unset( $this->hashes[ $object->hash() ] );
	}

	public function is_empty() : bool {
		return $this->length() === 0;
	}

	public function length() : int {
		return $this->count();
	}
}
