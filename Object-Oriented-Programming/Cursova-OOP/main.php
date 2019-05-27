<?php
/**
 * Все живе в цьому неймспейсі.
 */
namespace Cursova;

/**
 * Основний код демонстрації проекту
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */

// авто завантажувач класів
require __DIR__ . '/bootstrap.php';

// Ми можемо розглядати Students як List[Student] тобто список студентів
// що реалізує насутпні патерни проектування
// - Observer -> коли ми додаємо/видаляємо студента ми власне
// підписуємо/відписуємо його на якісь події.
//
// - Iterator -> дозволяє ітерувати студентів одного за одним.
$students = new Students( new Collection(), require 'data/students.php' );

// Group реалізує кілька патернів
// - Mediator: у випадку Group - це Students, а в Students це Collection
// - Proxy:    ми проксуємо виклики і передаємо нотифікації будучи Observer'ом
// - Observer: Пroup є обсервером по відношенню іншиї entities про які далі.
$group = new Group( 'ICзп-71', $students );

// метод notification зробить запит до receive_notification
// це не зовім привильно, яка в свою чергу вже дасть знати
// студентам через notify_observers. це мабуть найбільш заплутана
// штука яка насправді "помилка дизайну"
//
// ідея полягає в тому що Students через композицію вже є частиною Group
$group->notification( new Notification( 'Пора починати навчання' ) );


// Схожа за своєю будовою структура Subjects містить одинці Subject
// які складаються з назви предмету та інстантсу викладача.
// для створення Subject використовувалось simple factory.
$subjects = new Subjects( new Collection() );
$subjects->bulk_add( require 'data/subjects.php' );

$oop = new Subject( "Object Orientd Programming", new Teacher( "Rykhalskiy OU" ) );
$subjects->add( $oop );

// Премети та Група теж формують собою Obeserver - де обсервером є група
// а продюсером меседжів предмет.
$group->semester( $subjects );

printf( "Group Info \n%s ", $group);
printf( "Group Subjects \n%s \n\n", $group->subjects());


// Command через відправлене повідомлення.
printf("\n\nПредмет ОО надсилає повідомлення.");
$oop->notify_observers( new Assignment( 'Курсова робота', '14-05-2018' ) );
