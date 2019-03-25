<?php

	set_time_limit(0);

	$url = "https://www.dobrobut.com/doctors?search=&clinic=&direction=&letter=%s&page=%d";

 	$abc = "Ъ|А|Б|В|Г|Д|Е|Ж|З|И|Й|К|Л|М|Н|О|П|Р|С|Т|У|Ф|Х|Ц|Ч|Ш|Щ|Ъ|Ы|Ь|Э|Ю|Я";
	foreach ( explode( "|", $abc) as $char ) {
		$i = 1;
		while( $i ) {
			$_url = sprintf( $url, urlencode($char), $i++ );
			$data = file_get_contents( $_url );

			if ( strpos( $data, 'Ничего не найдено' ) !== false ) {
				$i = 0;
				break;
			}

			list( $_, $data ) = explode( '<div id="w1" class="doctors-list">', $data );
			list( $data, $_ ) = explode( '<script>', $data );

			$file = __DIR__ . '/doctors-short/' . $char .'-' . substr(md5($data), 16) . '.txt';

			file_put_contents( $file, $data );
		}
	}