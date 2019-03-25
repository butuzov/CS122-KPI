<?php 

    set_time_limit(0);
    include_once "../conf.php";  


    $facility = $db->exec("SELECT * FROM facilities WHERE `Type` IS NULL 
        OR  `Type` != 'Laboratory' ");

    $labs     = $db->exec("SELECT * FROM facilities WHERE `Type` = 'Laboratory' 
        ORDER BY RAND() LIMIT ".(count($facility) + 5) );

    foreach( $labs as $lab ) {
 
        $data = [
            'LaboratoryID'  => $lab->ID,
            'FacilityID'    =>  $facility[rand(0, count($facility)-1)]->ID,
            'Start'         => generate_date(),
            'Type'          => 'Active',
        ];
        
        create_if_not_exists( 'laboratory_contracts', $data );
    }