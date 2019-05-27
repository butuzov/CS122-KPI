<?php
    set_time_limit(0);
    include_once "../conf.php"; 
    
    $sets = array(
        // Gender | Position |                   
        [ 'f',     'Касир',                     2,        'Финанси'],
        [ 'f',     'Бухгалтер',                 1,        'Финанси'],
        [ 'f',     'Администратор',             4,        'Администратор'],
        [ 'f',     'Координатор',               2,        'Администратор'],
        [ 'f',     'Прибиральниця',             'rand',   'Санитарна справа'],
        [ 'm',     'Охрана',                    'rand',   'Охрана'],
        [ 'm',     'Системний администратор',   1,        'IT Sector'],
    );


    $genders = ["m", "f"];

    $facily_list = $db->exec( "SELECT * FROM facilities" ); 
    
    foreach( $facily_list as $facility ) {

        foreach( $sets as $set ) {

            $limit = $set[2];
            if ( $set[2] == 'rand' ) {
                $limit = rand(5, 10);
            }
    
            $gender = ( in_array( $set[0], $genders ) ? $set[0] : $genders[ rand(0, 1) ] );
            
            $spec = $db->exec(
                "SELECT * FROM speciality WHERE lower(Speciality) LIKE lower('%{$set[3]}%')" 
            );
            

            for( $i = 1; $i <= $limit; $i++ ){
                $gender = ( in_array( $set[0], $genders ) ? $set[0] : $genders[ rand(0, 1) ] );
                
                $person = array(
                    'Name'     => name( $gender ),
                    '_Position' => $set[1],
                    '_Type'     => $spec[0]->Type,
                    '_Since'    => generate_date()
                );
    
                // Create Person
                $p = create_if_not_exists( 'workers', $person );

                
    
                // Add to Specialization
                $ws = create_if_not_exists( 'workers_specialities', [
                    'WorkerID'   => $p->ID,
                    'SpecialityID' => $spec[0]->ID, 
                ] );

                // Add to Facilty
                $workpalce = [
                    'FacilityID' => $facility->ID,
                    'WorkerID'   => $p[0]->ID,
                    'Role'       => $person['_Position'],
                    'Type'       => $spec[0]->Type,
                    'Start'      => $person['_Since'],
                    'Status'     => 'Active',
                ];

                if ( rand(0, 100) % 5 == 0 ) {
                    $workpalce['Start'] = sprintf("%'04s-%'02s-%'02s", rand(2007, 2008), rand(1,2), rand(1,29));
                    $workpalce['End'] = next_random_date( 
                            (int) str_replace("-", "", $workpalce['Start']) );
                    $workpalce['Status'] = 'None';
                    
                }

                $wf = create_if_not_exists( 'workers_facilities', $workpalce);

 
            }
        }
    }
