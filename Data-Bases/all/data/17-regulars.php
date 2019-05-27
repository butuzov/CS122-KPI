<?php 

    set_time_limit(0);
    include_once "../conf.php"; 


    $facilities = $db->exec( "SELECT * FROM facilities WHERE Type != 'Laboratory' " );
    $n = 0;
    foreach( $facilities as $facility ) {

        $cabinets = $db->exec("SELECT  
                    fr.ID as Cabinet, 
                    fr.DepartmentID as Department 
                    FROM facilities_rooms fr 
                    WHERE fr.FacilityID = {$facility->ID} AND fr.Type = 'Cabinet'");
        
        $t_cabinets = count($cabinets)-1;

        $n++;
        $doctors = $db->exec("SELECT WorkerID as Doctor, `Start` FROM `workers_facilities` 
            WHERE `Status` = 'Active' 
                AND `FacilityID` = {$facility->ID} 
                AND `Type` = 'Medical'  ");

        foreach( $doctors as $doctor ) {
            $time = time() - strtotime($doctor->Start);
            $patients = mt_rand(0, 40);
            
            $patients = $db->exec("SELECT * FROM `patients` 
                WHERE Birth > '{$doctor->Start}' ORDER BY RAND() LIMIT {$patients}");
            
            $start = strtotime($doctor->Start);
            foreach( $patients as $patient ) {

                $cabinet = $cabinets[rand(0, $t_cabinets)];
                
                $data = array(
                    'FacilityID'  => (int) $facility->ID,
                    'Type'        => ['Regular','Periodic'][ rand( 0,1 ) ],
                    'DepartmentID'=> (int) $cabinet->Department,
                    'RoomID'      => (int) $cabinet->Cabinet,
                    'DoctorID'    => (int) $doctor->Doctor,
                    'PatientID'   => (int) $patient->ID, 
                    'SignIn'      => date("Y-m-d", rand($start, $start+24*14*60*60 )),
                   // 'SignIn'      => date("Y-m-d", rand($start,  time())),
                );
                $data['SignOut'] = $data['SignIn'] ;  
                create_if_not_exists( 'registry', $data );       
                $n++; 
            }
        } 

    }

    var_dump($n);