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

class Students implements Observerable {

	// storage underlayer.
	private $storage;

	public function __construct( Storage $storage, array $students = [] ) {
		$this->storage = $storage;
		$this->bulk_add( $students );

	}

	public function bulk_add( array $students ) {
		// fill students gruop
		array_map( function( $student ) {
			$this->add( new Student( $student ) );
		}, $students );
	}



	// add : shortcur to subscribe
	public function add( Student $student ) {
		$this->subscribe( $student );
	}

	// remove : shortcur to unsubscribe
	public function remove( Student $student ) {
		$this->unsubscribe( $student );
	}


	// get student by number.
	private function get( int $index ) {
		$iterated = 0;
		foreach ( $this->sorted_by_names() as $key => $student ) {
			if ( ++$iterated == $index ) {
				return $student;
			}
		}
		throw new \OutOfBoundsException( 'Item not found' );
	}

	// get student by name.
	private function get_by_name( string $name ) {
		foreach ( $this->sorted_by_names() as $key => $student ) {
			if ( $student->name() == $name ) {
				return $student;
			}
		}
		throw new \OutOfBoundsException( 'Item not found' );
	}

	// повертаю (або не повертає) студента за номером або іменем
	public function student( $input ) {
		switch ( gettype( $input ) ) {
			case 'integer':
				$method = 'get';
				break;
			case 'string':
				$method = 'get_by_name';
				break;
			default:
				throw new \InvalidArgumentException( "$input can be only string or int" );
		}

		try {
			return $this->$method( $input );
		} catch ( OutOfBoundsException $e ) {
			return false;
		}

		return false;
	}

	public function exists( Student $student ) : bool {
		return $this->storage->exists( $student );
	}


	public function is_empty() : bool {
		return $this->storage->is_empty();
	}

	public function size() : int {
		return $this->storage->length();
	}

	// return array[Student]
	public function all() {
		return (array) clone $this->storage;
	}

	// return array[Student] sorted by name
	public function sorted_by_names() {
		$students = $this->all();
		natsort( $students );
		return $students;
	}


	// ----------------------------------------------------------------
	// Observerable (Observer) Notifications.
	public function subscribe( Observer $observer ) {
		$this->storage->push( $observer );
	}

	public function unsubscribe( Observer $observer ) {
		$this->storage->remove( $observer );
	}

	public function notify_observers( Message $message ) {
		if ( $this->is_empty() ) {
			throw new \UnderflowException( 'no students here' );
		}

		foreach ( $this->storage as $student ) {
			$student->receive_notification( $message );
		}
	}

	// Observer interface implementation
	public function receive_notification( Message $message ) {
		$this->notify_observers( $message );
	}
}
