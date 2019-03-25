<?php 

    include_once "../conf.php"; 
    include "doctors-short-parser.php";
    
    $db->exec("TRUNCATE TABLE `workers`");

    foreach( $doctors as $raw_doctor ) {

        // hacks 
        if ( $raw_doctor['name'] == "Litvinovskaia Ekaterina" ) {
            $tmp = $raw_doctor['jobtitle'];
            $raw_doctor['jobtitle'] = $raw_doctor['description'];
            $raw_doctor['description'] = $tmp;   
        }


        $data = array(
            'Name'        => $raw_doctor['name'],
            '_Position'    => $raw_doctor['jobtitle'],
            '_Description' => $raw_doctor['description'],
            '_Since'       => $raw_doctor['doctor_since'],
        );    
    
        if ( false === ( $doctor = doctor( array_slice( $data, 0, 3, true) ) ) ) {
            $doctor = doctor_create( $data );
        } 

    }