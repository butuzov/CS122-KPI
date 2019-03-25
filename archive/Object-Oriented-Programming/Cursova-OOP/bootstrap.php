<?php
/**
 * spl autolaod
 *
 * @category    The Principles of Object Oriented Programming
 * @package     Курсова з предмету "Об'єкно Орієнтованого Програмування"
 * @author      Oleg Butuzov <butuzov@made.ua>
 *
 * Requires PHP: 7.1
 */

/**
 * Classes and Interfaces Autoloader.
 */
spl_autoload_register( function ( $name ) {

	$name_lower = strtolower( $name );

	$prefix = 'cursova';
	$length = strlen( $prefix );


	if ( substr( $name_lower, 0, $length ) !== $prefix) {
		return;
	}

	$changes = [
		'_'  => '-',
		'\\' => '/',
	];

	$search  = array_keys( $changes );
	$replace = array_values( $changes );

	$maybe_name = str_replace( $search, $replace, $name_lower );
	$maybe_name = sprintf( '%s.php', substr( $maybe_name, $length + 1 ) );

	$offset = strpos( strrev($maybe_name), '/' );

	$prefix = '';
	$postfix = $maybe_name;

	if ( false !== ( $offset = strpos( strrev($maybe_name), '/' ) ) ) {
		$prefix = substr( $maybe_name, 0, strlen($maybe_name) - $offset ) ;
		$postfix = substr( $maybe_name, strlen($maybe_name) - $offset ) ;
	}

	$files = array();


	foreach ( [ 'interface', 'class' ] as $type ) {

		$try_file_name = sprintf( '%s%s%s.%s', __DIR__ . '/project/', $prefix, $type, $postfix );

		if ( file_exists( $try_file_name ) ) {
			include_once $try_file_name;
			return;
		}

		$files[] = str_replace( __DIR__ . '/project/', '', $try_file_name );
	}


	var_dump( [
		'message'  => 'CLASS_NOT_FOUND',
		'name'     => $name,
		'we_tried' => $files
	] );

} );
