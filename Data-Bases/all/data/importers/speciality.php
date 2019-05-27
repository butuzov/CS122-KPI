<?php 

    include_once "db.php";
    $db = new db( "mysql", "root", "123", "cursova");

    include "functions.php";

    // creation of specilities
    // $data = file_get_contents("https://www.dobrobut.com/services");
    // preg_match_all('/<span itemprop="supersededBy">(.*?)<\/span>/si', $data, $m);
  

    $results = $db->exec( "SELECT ID, Name, Concat(LOWER(Position), ' ', LOWER(Description)) as Position FROM workers WHERE `Type` = 'Medical'" );
    

   
    




    $results = array_map( function( $item ){
        unset( $item->words );
        return $item;
    }, $results );


   

   
