<?php 

    $data = file_Get_contents('https://www.synevo.ua/uk/analizy/vse-analizy/');

    preg_match_all('/<tr>(.*?)<\/tr>/si', $data, $m);
    
    $_tests = array_map( function($item){
        if ( preg_match( '/<h4>(.*?)<\/h4>/si', $item, $m)) {
            return array(
                'Title' => $m[1],
            );
        }

        if ( preg_match( '/<h5>(.*?)<\/h5>/si', $item, $m)) {
            return array(
                'Title' => $m[1],
            );
        }

        preg_match_all('/([a-z\-]{1,})="(.*?)"/si', $item, $m);
        

        $properties = array_combine( $m[1], $m[2] );

       

        return array(
            'Title' => $properties['test-name'],
            'Code' => $properties['code'],
        );;
    }, $m[0]);

    $tests = array();
    foreach( $_tests as $item ){
        $ids = array(); 

        if (strpos($item['Title'], 'Пакет') !== false ) {
            continue;
        }

        if ( preg_match( "/\d\./si", $item['Title'], $_ ) ) {

            preg_match("/(.*?) /si", $item['Title'], $id);
            
            $ids = array_filter(array_map('intval', explode(".", $id[0])), function( $i ){
                return $i > 0;
            });
        }


            
            
        $header = false;
        if ( ! empty( $ids ) ) {
            $parent = array_shift( $ids );
            $header = true;
            unset($sub);
        }

        if ( ! empty( $ids ) ) {
            $sub = array_shift( $ids );
            $header = true;
        }

        add( $header, $parent, $sub, $item );
      //  var_dump( array($header, $parent, $sub, $item ) );

        
        
    }
 


    function add( $header, $parent, $sub, $item  ){
        global $tests;

        if ( $header && $parent > 0 && is_null($sub) ) {
            $tests[$parent]['Title'] = clean($item['Title']);
            return;
        }

        if ( $header && $parent > 0 && $sub > 0 ) {
            $tests[$parent][$sub]['Title'] = clean($item['Title']);
            return;
        }

        $title = clean($item['Title']);
        if ( empty( $title ) ) {
            return;
        }

        $test = clean($item['Title']);  

        if ( is_null( $sub ) ) {
            $tests[$parent]['Tests'] = $tests[$parent]['Tests'] ?: []; 
            if ( ! in_array($test, $tests[$parent]['Tests'] ) ){
                $tests[$parent]['Tests'][$item['Code']] = $test;
            }
            return;            
        }

        $tests[$parent][$sub]['Tests'] = $tests[$parent][$sub]['Tests'] ?: []; 
        if ( ! in_array($test, $tests[$parent][$sub]['Tests'] ) ){
            $tests[$parent][$sub]['Tests'][$item['Code']] = $test;
        }

         
    }   

    function clean( $string ) {
        $p = explode(" ", $string);
        array_shift($p);
        return implode(" ", $p);
    }

    var_dump($tests);