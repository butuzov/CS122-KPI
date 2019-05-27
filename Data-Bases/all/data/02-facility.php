<?php 

    include_once "../conf.php"; 
    
    include "doctors-short-parser.php";

    $db->exec("TRUNCATE TABLE `facilities`");
    $db->exec("TRUNCATE TABLE `workers_facilities`");

    foreach( $doctors as $raw_doctor ) {

        if ( ! empty ( $raw_doctor['clinics'] ) ) {
            foreach ( $raw_doctor['clinics'] as $item ) {

                $data = [
                    'Title'       => $item['Title'], 
                    'Affiliation' => 'Dobrobut',
                    'Address'     => $item['Adress'],
                ];

                if ( false === ( $facility = facility( $data ) ) ) {
                    $facility = facility_create( $data );
                }
            }
        }
    }