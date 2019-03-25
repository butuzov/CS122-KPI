<?php 

include_once "../conf.php"; 
include "doctors-short-parser.php";


$db->exec("TRUNCATE TABLE `workers_titles`");

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

    $doctor = doctor( array_slice( $data, 0, 3, true) );
    
    
    if ( ! empty ( $raw_doctor['titles'] ) ) {
        foreach ( $raw_doctor['titles'] as $item ) {

            $data = [];
            $data['WorkerID'] = $doctor->ID;
            $data['Type'] = $item['type'];
            $data['Title'] = $item['title'];
            
            if ( false === ( $title = title( $data ) ) ) {
                $title = title_create( $data );
            }
        }
    } 

}