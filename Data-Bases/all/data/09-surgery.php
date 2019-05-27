<?php 

    set_time_limit(0);
    include_once "../conf.php";    


    

   // var_dump($patients);

    $surgeons = $db->exec( "SELECT * FROM `workers_facilities` WHERE Role LIKE '%хирург%'" );
    foreach( $surgeons as $surgeon ) {

        $startDate =  $surgeon->Start;
        $endDate = (is_null( $surgeon->End ) 
            ? date("Y-m-d") :  $surgeon->Start ) ;

        $patients = $db->exec( 'SELECT * FROM patients ORDER BY RAND() LIMIT '.rand(10, 30));

        foreach( $patients as $patient ) {
            
            $surgery = [
                'FacilityID' => $surgeon->FacilityID,
                'PatientID' => $patient->ID,
                'Date' => generate_date_between( $startDate, $endDate ),
            ];

            $surgery = create_if_not_exists( 'surgeries', $surgery );
          
            $surgery_doctor = [
                'SurgeryID' => $surgery[0]->ID,
                'WorkerID'  => $surgeon->WorkerID,
            ];

            
            var_dump(  create_if_not_exists( 'surgeries_doctors', $surgery_doctor ) );
            // var_dump($surgery, $surgery_doctor, $surgery); 
        }        
    }


    function generate_date_between( $start, $end ){
        return date("Y-m-d", mt_rand(strtotime($start), strtotime($end)));
    }