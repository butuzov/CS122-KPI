<?php 

    set_time_limit(0);
    include_once "../conf.php";    
    
    include "laboratory_tests.php";
    $db->exec("TRUNCATE TABLE `laboratory_examination_types`");

    foreach ( $tests as $test ){
        $item = processItems( $test , 0 );        
    }


    function processItems( $data , $parent  ) {
        if ( isset ( $data['Title'] ) ) {
            $p = create_if_not_exists( 'laboratory_examination_types', array( 
                'Title' => $data['Title'],
                'Type' => 'Category',
                'ParentID' => $parent,
                ) 
            );
        }
        
        if ( isset( $data['Tests'] ) ){
            foreach( $data['Tests']  as $code => $test ) {
                create_if_not_exists( 'laboratory_examination_types', array( 
                    'Title' => $test,
                    'Type' => 'Test',
                    'Code' => $code,
                    'ParentID' => $p[0]->ID,
                    ) 
                );
            }
        }

        unset($data['Title']);
        unset($data['Tests']);

        foreach( $data as $code => $item ) {
            processItems( $item , $p[0]->ID );
        }

    }   