<?php

/**
 * Classes and Interfaces Autoloader.
 */
spl_autoload_register( function ( $class_name ) {

	foreach ( [ 'class', 'interface' ] as $type ) {
		$name = sprintf( '%s-%s.php', $type, str_replace( '_', '-', strtolower( $class_name ) ) );

		// echo "\nLoading:", $name, "\n";

		if ( file_exists( __DIR__ . '/' . $name ) ) {
			include_once __DIR__ . '/' . $name;
			return;
		}
	}
} );