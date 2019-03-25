<?php 

    include_once "../conf.php"; 

    $db->exec("TRUNCATE TABLE `speciality`");

    $data = file_get_contents("https://www.dobrobut.com/services");
    preg_match_all('/<span itemprop="supersededBy">(.*?)<\/span>/si', $data, $m);

    $speciality = $m[1];

    $speciality = array_map( function( $item ) {
        return [ 'Speciality' => str_replace('УЗ', 'УльтраЗвуковая', $item), 'Type' => 'Medical' ];
    }, $speciality);


    $speciality[] = [ 'Speciality' => 'Охрана',                      'Type' => 'Other' ];
    $speciality[] = [ 'Speciality' => 'Администратор',               'Type' => 'Administrative' ]; 
    $speciality[] = [ 'Speciality' => 'Управление Мед учереждением', 'Type' => 'Administrative' ]; 
    $speciality[] = [ 'Speciality' => 'Слесарное Дело',              'Type' => 'Technical' ]; 
    $speciality[] = [ 'Speciality' => 'Санитарна справа',            'Type' => 'Other' ]; 
    $speciality[] = [ 'Speciality' => 'Сестринское Дело',            'Type' => 'Medical' ]; 
    $speciality[] = [ 'Speciality' => 'Финанси',                     'Type' => 'Administrative' ]; 
    $speciality[] = [ 'Speciality' => 'IT Sector',                   'Type' => 'Technical' ]; 
    
   
    foreach( $speciality as $spec ){
         
        if ( false === $db->exists( 'speciality', $spec ) )  {
            $db->insert( 'speciality',  $spec );
        } else {
            var_dump("created");
        }
    }
    

     