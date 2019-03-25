<?php 

    set_time_limit(0);
    include_once "../conf.php"; 

    $facilities = $db->exec("SELECT * FROM facilities WHERE `Type` IS NULL 
                                OR  `Type` != 'Laboratory' ");

    $departments = [
        'Онкологія',
        'Педіатрія',
        'Травматологія',
        'Неврологии',
        'Нейрохірургії',
    ];

  

    foreach( $facilities as $facility ) {
        $doctors = $db->exec("SELECT * FROM workers_facilities 
            WHERE FacilityID = {$facility->ID} AND Type = 'Medical' AND Status = 'Active'");
    


        $deps = $departments;
        shuffle($deps);
        $deps = array_slice($deps, 0, 3);
        foreach(  $deps as $k=>$department) {
            $data = [
                'FacilityID' => $facility->ID, 
                'Name'       => $department,
            ];
            $deps[$k] = array_shift(create_if_not_exists( 'facilities_departments', $data ));
        }

        $rooms      = (((int) (count($doctors) / 10) ) + 1 ) * 10; 
        $bads       = $facility->Type == 'Hospital' ? $rooms + $rooms : 0;
        $procedures = (($rooms + $bads) / 10) * 2;
         
        $rooms = array(
            'Cabinet'      =>  $rooms,
            'Ambulatory'    =>  $bads,
            'Procedural'   =>  $procedures,
        );

        $t = 0;
        foreach( $rooms as $type => $number ) {
            for ( $i=0; $i < $number; $i++) {
                $t++;
                $data = array(
                    'FacilityID'   => $facility->ID,
                    'DepartmentID' => $deps[rand(0, 2)]->ID,
                    'Type'         => $type,
                    'Number'       => sprintf( "%s-%'03s", (int) ($t/24) + 1, ($t % 24 ) + 1 ),
                );

                create_if_not_exists( 'facilities_rooms', $data  );
            }   
        }

        echo "<hr>";
    }