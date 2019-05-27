<?php 

    function doctor( $args ) {
        global $db;

        if ( ! $db->exists( 'workers', $args ) ) {
            return false;
        }

        return doctor_get($db->get('workers', $args ));
    }

    function doctor_create( $args ){
        global $db;
        return doctor_get($db->insert( 'workers', $args ));
    }   


    function doctor_get( $results ){
        return $results[0];
    }

    function doctor_update( $id, $args ) {
        global $db;
        return doctor_get($db->update( 'workers', $id, $args )); 
    }

    /******************************
     * Facility
     ******************************/


    function facility( $args ) {
        global $db;

        if ( ! $db->exists( 'facilities', $args ) ) {
            return false;
        }

        return facility_get($db->get('facilities', $args ));
    }

    function facility_create( $args ){
        global $db;
        return facility_get($db->insert( 'facilities', $args ));
    }   


    function facility_get( $results ){
        return $results[0];
    }

    function facility_update( $id, $args ) {
        global $db;
        return facility_get($db->update( 'facilities', $id, $args )); 
    }
    

    /*********************************************************************
     * workplace
     ********************************************************************/

    function workplace_create( $facility, $worker, $role = null ){
        global $db;
        $args = [ 'FacilityID' => $facility, 'WorkerID' => $worker ];

        if ( ! is_null( $role ) ) {
            $args['Role'] = trim($role);
        }

        if ( $db->exists( 'workers_facilities', $args ) ) {
            return true;
        }

        $db->insert( 'workers_facilities', $args );
    }

    function workplace_drop( $facility, $worker, $role = null  ){
        global $db;

        $args = [ 'FacilityID' => $facility, 'WorkerID' => $worker ];
        if ( ! is_null( $role ) ) {
            $args['Role'] = trim($role);
        }

        if ( ! $db->exists( 'workers_facilities', $args ) ) {
            return true;
        }

        $db->drop( 'workers_facilities', $args );

    }

    /*********************************************************************
    * titles
    ********************************************************************/

    function title( $args ){
        global $db;
        if ( ! $db->exists( 'workers_titles', $args ) ) {
            return false;
        }

        return title_get( $db->get('workers_titles', $args ));
    }

    function title_create( $args ){
        global $db;
        return title_get($db->insert( 'workers_titles', $args ));
    }
    
    function title_update( $id, $args ){
        global $db;
        return title_get($db->update( 'workers_titles', $id, $args )); 
    }
    
    function title_drop( $args ){
        return  $db->drop( 'workers_facilities', $args );
    }

    function title_get( $results ){
        return $results[0];
    }
    

    function get_sql( $file ){
        return trim( file_get_contents( $file ) );
    }
    
    /*****
     * 
     ********/

    function name( $gender = 'r' ) {
        $gender = in_array($gender, ['m', 'f']) ? $gender : ['m', 'f'][ rand( 0, 1 ) ];
        $data = json_decode( file_get_contents( __DIR__ .'/data/'. 'names.json' ), true);
       
        return $data[ $gender ][rand(0, count($data[ $gender ]) - 1)] . ' ' .
            $data['surname'][rand(0, count($data['surname'])-1)];
    }

     
    function create_if_not_exists( $table, $data ){
        global $db;
        if ( ! $db->exists( $table, $data ) ) {
            $db->insert( $table, $data );
        }

        return $db->get( $table, $data ); 
    }

    function generate_date(){
        return sprintf("%'04s-%'02s-%'02s", rand(2007, 2017), rand(1,2), rand(1,29));
    }

    function next_random_date( int $indate ){

        $out_data   = generate_date();
        $out_data_n = (int) str_replace("-", "",  $out_data);
        return $out_data_n > $indate ? $out_data :  next_random_date( $indate );
    }