<?php

	$data = glob( __DIR__ . "/doctors-short/*.txt" );

	// $data = array_map( 'file_to_doctors', array_slice( $data , 45 ) );
	$data = array_map( 'file_to_doctors', $data );

	$doctors = array();
	foreach( $data as $_ ){
		foreach( $_ as $doctor ) {
			$doctors[] = $doctor;
		}
	}

	$doctors = array_filter( $doctors, function( $item ) {
		return ! empty( $item );
	});

	$doctors = array_map( function( $item ){

		$shorts = array(
			"т.д." => 'тд',
		);


		$item['description'] = str_replace(
				array_keys( $shorts),
				array_values( $shorts ),
				$item['description']
		);
		$d = explode(". ", $item['description'] );
		$d = array_filter( array_map( 'trim', $d ), 'trim');

		foreach ( $d as $entry ) {
			if ( strpos( $entry, 'наук' ) !== false  ) {
				$item['titles'][] = array(
					'type'  => 'Academic',
					'title' => $entry,
				);
			}

			if ( stripos( $entry, 'член' ) !== false  ) {
				$item['titles'][] = array(
					'type'  => 'Membership',
					'title' => $entry,
				);
			}

			if ( stripos( $entry, 'Член' ) !== false  ) {
				$item['titles'][] = array(
					'type'  => 'Membership',
					'title' => $entry,
				);
			}

			if ( stripos( $entry, 'категории' ) !== false  ) {
				$item['titles'][] = array(
					'type'  => 'Profesional',
					'title' => $entry,
				);
			}
		}


		return $item;
	}, $doctors );


	$doctors = array_map( function( $item ) {

		$item['name'] = explode(" ", $item['name']);

		$item['name'] = translit( implode(" ", array_slice( $item['name'], 0, 2 )) );

		return $item;
	}, $doctors );
 

	function file_to_doctors( $file ) {
		return array_map( 'parse_doctor_info',
					explode( '<div class="doctors-list__item"',
						file_get_contents( $file )
					)
				);
	}

	function parse_doctor_info( $item ){
		if ( empty( $item) ) {
			return false;
		}


		$data = [
			'name' => get('name', $item),
			'jobtitle' => get('jobTitle', $item),
			'description' => get('description', $item),
		];


		if ( preg_match('/<div class="doctors-list__exp">(.*?)<\/div>/si', $item, $m)){
			$data['doctor_since'] = date("Y-m-d",
				time() - intval($m[1]) * 12 * 30 * 24 * 60 * 60 +
					array( rand(1000000, 6000000), -rand(1000000, 6000000))[rand(0,1)]
			) ;
		}

		preg_match_all( '/<a class="doctors-list__address" (.*?)>(.*?)<\/a>/si', $item, $adresses);
		foreach( $adresses[2] as $_adr){

			$data['clinics'][] = [
				'Title'  => get( 'name',    $_adr ),
				'Adress' => get( 'address', $_adr ),
			];
		}
		return $data;
	}

	function translit( $item ){
		$cyr = array(
			'ж',  'ч',  'щ',   'ш',  'ю',  'а', 'б', 'в', 'г', 'д', 'е', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ъ', 'ь', 'я', 'ы',
			'Ж',  'Ч',  'Щ',   'Ш',  'Ю',  'А', 'Б', 'В', 'Г', 'Д', 'Е', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ъ', 'Ь', 'Я');
		$lat = array(
			'zh', 'ch', 'sht', 'sh', 'yu', 'a', 'b', 'v', 'g', 'd', 'e', 'z', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'f', 'h', 'c', 'y', "'", 'ia', 'ii',
			'Zh', 'Ch', 'Sht', 'Sh', 'Yu', 'A', 'B', 'V', 'G', 'D', 'E', 'Z', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'T', 'U', 'F', 'H', 'c', 'Y', 'X', 'Ia');

		return rtrim(str_replace( $cyr, $lat, $item ), "'");
	}

	function get( $type, $data ) {
		preg_match('/<(.*?) itemprop="'.$type.'"(.*?)>(.*?)<\/\1>/si', $data, $m);
		return trim( $m[3] );
	}

