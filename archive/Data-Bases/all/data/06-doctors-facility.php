<?php 

include_once "../conf.php"; 
include "doctors-short-parser.php";


$db->exec("TRUNCATE TABLE `workers_facilities`");

foreach( $doctors as $raw_doctor ) {


    $data = array(
        'Name'         => $raw_doctor['name'],
        '_Position'    => $raw_doctor['jobtitle'],
        '_Description' => $raw_doctor['description'],
        '_Since'       => $raw_doctor['doctor_since'],
    );    

    $doctor = doctor( array_slice( $data, 0, 3, true) );


    if ( empty( $raw_doctor['clinics'] ) ) {
        continue;
    }

    foreach( $raw_doctor['clinics'] as $item ){

        $facility = facility( [
            'Title'       => $item['Title'], 
            'Affiliation' => 'Dobrobut',
            'Address'     => $item['Adress'],
        ] );

        // Add to Facilty
        $workpalce = [
            'FacilityID' => $facility->ID,
            'WorkerID'   => $doctor->ID,
            'Role'       => $doctor->_Position,
            'Type'       => 'Medical',
            'Start'      => $doctor->_Since,
            'Status'     => 'Active',
        ];

        if ( rand(0, 100) % 5 == 0 ) {
            $workpalce['End'] = next_random_date( (int) str_replace("-", "", $person['_Since']) );
            $workpalce['Status'] = 'None';
            
        }

        $wf = create_if_not_exists( 'workers_facilities', $workpalce);

       
    } 
 

}