<?php 

    include_once "../conf.php"; 
    include "doctors-short-parser.php";


    $db->exec("TRUNCATE TABLE `workers_specialities`");


    $results = $db->exec( "SELECT ID, Name, 
        Concat(LOWER(_Position), ' ', LOWER(_Description)) as Position 
        FROM workers WHERE `_Type` = 'Medical'" );

   
    // Array to words.

    $results = array_map( function( $item ) {
        $r = array (
            "-" => " ",
            "," => " ",
            "." => " ",
        );

        $position = normalize($item->Position);
        $position = preg_replace( '/(\w)(хирург)/usi', '$1', $position);

        $item->words = explode( " ", str_replace( array_keys($r), array_values($r), $position ) );
         
        $item->words = array_filter( $item->words, function( $item ){
            return mb_strlen($item) > 3;
        });

        $item->words = array_unique(array_filter( $item->words, 'trim'));

        return $item;
    }, $results );



    $results = array_map( function( $item ){
        global $db;

        if ( empty( $item->words ) ) {
            return $item;
        }
        foreach( $item->words as $word ){
            $res = $db->exec("SELECT * FROM speciality WHERE lower(Speciality) LIKE '%{$word}%'");
            if ( !empty( $res )) {
                foreach( $res as $r ) {
                    $item->matches[ $r->Speciality ][] = $word;
                }
            }
        }
        
        // $item->matches = array_filter( $item->matches, function( $item ){
        //     return ! empty( $item );
        // });

        return $item;
    }, $results);


    $results = array_map( function( $item ){
        unset( $item->words );
        return $item;
    }, $results );


     // $results = array_filter( $results , function( $item ){
    //     return ! isset($item->matches);
    // });


    foreach( $results as $doctor ) {
       
        if ( empty( $doctor->matches ) ) {
            continue; 
        }
            
        foreach( array_keys($doctor->matches) as $Speciality ){
            $d = [ 'Speciality' => $Speciality ];
            $spec  = $db->get( 'speciality', $d )[0];

            $pair = [
                'SpecialityID' => $db->get( 'speciality', $d )[0]->ID,
                'WorkerID' => $doctor->ID,
            ];

            if ( ! $db->exists( 'workers_specialities',  $pair ) ) {
                $db->insert( 'workers_specialities',  $pair );
            }
        } 

    }


    function normalize( $string ) {
        $words = array(
            'физиотерапевт' => 'физиотер',
            'отоларинголог' => ' оториноларинголог отоларинголог',
            'массажист' => 'массажист массаж ',
            'семейный' => 'семей семейный',
            'семейной' => 'семей семейной',
            'невропатолог' => 'невропатолог невролог',
            'реабилитации' => 'реабилитация реабилитации',
            'неонотолог' => 'неонотолог неонатолог',
            'терапевт' => 'терапевт терапия',
            'реабилитолог' => 'реабили',
            'ультразвук' => ' ультразвук',
            'узи' => ' ультразвук',
            'эндоскопист' => ' эндоскопия эндоскопист',
            'детский' => 'педиатрия',
            'сексуальных' => 'сексолог сексуальных',
            'диагностике' => 'диагностика', 
            'эдокринолог' => 'эндокринология'
        );
        return str_replace(  array_keys( $words ), array_values( $words ), $string );
    }