<?php
/**
 * Observerable interface
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */

namespace Cursova;

interface Observerable {

	public function subscribe( Observer $observer );
	public function unsubscribe( Observer $observer );
	public function notify_observers( Message $message );

}
