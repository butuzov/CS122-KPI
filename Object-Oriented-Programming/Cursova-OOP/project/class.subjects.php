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

class Subjects {

	// storage underlayer.
	private $storage;

	public function __construct( Storage $storage, array $subjects = [] ) {
		$this->storage = $storage;
		$this->bulk_add( $subjects );

	}

	public function subjects() {
		return $this->storage;
	}

	public function add( Subject $subject ) {
		$this->storage->push( $subject );
	}

	public function count() :int {
		return $this->storage->length();
	}

	public function bulk_add( array $subjects ) {

		array_map( function( $subject ) {
			$this->add(
				( new Subject_Factory( $subject ) )->create()
			);
		}, $subjects );
	}


	private function as_string() {
		$output = '';
		foreach ( $this->subjects()  as $item ) {
			$output .= sprintf( "\n - %s", $item );
		}
		return $output;
	}

	public function __toString() : string {
		return $this->as_string();
	}


	public function unsubscribe( Observer $observer ) {
		foreach ( $this->subjects() as $subject ) {
			$subject->unsubscribe( $observer );
		}
	}

	public function subscribe( Observer $observer ) {
		foreach ( $this->subjects() as $subject ) {
			$subject->subscribe( $observer );
		}
	}


}
