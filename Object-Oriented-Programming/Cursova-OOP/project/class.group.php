<?php
/**
 * Group - як репрезентація групи студентів
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */

namespace Cursova;

class Group  implements Observer {

	private $students;
	private $name;
	private $subjects;

	public function __construct( string $name, Students $students ) {
		$this->name     = $name;
		$this->students = $students;
		$this->kurs     = 1;
	}

	public function __toString() : string {
		return implode( "\n", [ $this->name(), $this->get_students_list() ] );
	}


	// повертає кількість студентів
	public function get_students_count() : int {
		return $this->students->size();
	}

	public function students() : array {
		return $this->students->sorted_by_names();
	}

	public function add_student( string $name ) {
		$this->students->add( $name );
	}

	public function remove_student() {
		$this->students->remove( $name );
	}

	// додання нових предметів скасовує підписку на предмети
	// попереднього семестру і інціює нові підписки.
	public function semester( Subjects $subjects ) {
		if ( $this->has_subjects() ) {
			 $this->del_subjects();
		}
		$this->set_subjects( $subjects );
		$subjects->subscribe( $this );

	}

	function subjects() {
		if ( $this->has_subjects() ) {
			return $this->subjects;
		}

		return '';
	}

	public function has_subjects() {
		return $this->subjects instanceof Subjects;
	}

	public function del_subjects() {
		$this->subjects->unsubscribe( $this );
		$this->subjects = null;
	}

	public function set_subjects( Subjects $subjects ) {
		$subjects->subscribe( $this );
		$this->subjects = $subjects;
	}


	public function notification( Message $message ) {
		$this->students->receive_notification( $message );
	}

	// власний метод групи
	public function receive_notification( Message $message ) {
		$this->notification( $message );
	}

	public function name() : string {
		return $this->name;
	}

	/**
	 * повертає студента за індексом або за іменем
	 *
	 * @param int|string $search
	 * @return array
	 */
	public function student( $search ) : Student {
		return $this->students->student( $search );
	}

	// повертає форматований список студентівs
	public function get_students_list() : string {

		if ( $this->get_students_count() == 0 ) {
			return 'Не виявлено жодного студента';
		}

		$output = '';

		// preformatted formatter
		$numpadding = sprintf( "%%' %dd %%s\n", strlen( $this->get_students_count() ) );

		$number = 0;

		foreach ( $this->students() as $key => $student ) {
			$output .= sprintf( $numpadding, ++$number, $student );
		}

		return $output;

	}


}
