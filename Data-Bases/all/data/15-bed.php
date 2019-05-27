<?php 

    set_time_limit(0);
    include_once "../conf.php"; 

    $res = $db->exec("SELECT * FROM `facilities_rooms` WHERE Type = 'Ambulatory' ");


    foreach ( $res as $item ) {
        $nums = pow( 2, rand(0, 3));
        for ( $i = 0; $i < $nums; $i++ ) {
            $data = [
                'RoomID'     => $item->ID,
                'FacilityID' => $item->FacilityID,
                'Type'       => $nums == 1 ? 'Luxury' : 'Standard',
            ];

            $db->insert( 'facilities_rooms_beds', $data );
///            create_if_not_exists( 'facilities_rooms_beds', $data );
        }
    } 