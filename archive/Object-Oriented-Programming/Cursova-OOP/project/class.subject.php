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

class Subject implements Storable, Observerable {

	protected $name;
	protected $teacher;
	protected $subscribers = [];

	public function __construct( string $name, Teacher $teacher ) {
		$this->name    = $name;
		$this->teacher = $teacher;
	}

	public function hash() : string {
		return spl_object_hash( $this );
	}

	public function name() : string {
		return $this->name;
	}

	public function __toString() : string {
		return $this->name();
	}

	public function notify_observers( Message $message ) {
		foreach ( $this->subscribers as $subscriber ) {
			$subscriber->receive_notification( $message );
		}
	}

	public function subscribe( Observer $observer ) {
		foreach ( $this->subscribers as $subscriber ) {
			if ( $subscriber === $observer ) {
				return;
			}
		}
		$this->subscribers[] = $observer;
	}

	public function unsubscribe( Observer $observer ) {
		foreach ( $this->subscribers as $k => $subscriber ) {
			if ( $subscriber === $observer ) {
				unset( $this->subscribers[ $k ] );
				return;
			}
		}
	}

}
