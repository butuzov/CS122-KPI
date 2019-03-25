<?php 

    set_time_limit(0);
    include_once "../conf.php"; 

    $db->exec("TRUNCATE TABLE `registry`");
    $facilities = $db->exec( "SELECT * FROM facilities WHERE Type != 'Laboratory' " );
    $n = 0;
    foreach( $facilities as $facility ) {
        $beds = $db->exec("SELECT 
                    frb.ID as Bed, 
                    fr.ID as Room, 
                    fr.DepartmentID as Department 
                    FROM facilities_rooms fr, 
                         facilities_rooms_beds frb
                    WHERE fr.FacilityID = {$facility->ID} 
                    AND fr.ID = frb.RoomID");

        if ( count( $beds ) == 0 ) {
            continue;
        }
        $n++;
        $doctors = $db->exec("SELECT WorkerID as Doctor, `Start` FROM `workers_facilities` 
            WHERE `Status` = 'Active' 
                AND `FacilityID` = {$facility->ID} 
                AND `Type` = 'Medical'  ");
        $beds_t = count($beds);
        foreach( $doctors as $doctor ) {
            $time = time() - strtotime($doctor->Start);
            $patients = (int) ($time / ( 60 * 60 * 24 * 10));
            
            $patients = $db->exec("SELECT * FROM `patients` 
                WHERE Birth > '{$doctor->Start}' ORDER BY RAND() LIMIT {$patients}");

            $start = strtotime($doctor->Start);
            foreach( $patients as $patient ) {

                $bed = $beds[rand(0, $beds_t-1)];
                var_dump($bed);

                $data = array(
                    'FacilityID'  => (int) $facility->ID,
                    'Type'        => 'Stationary',
                    'DepartmentID'=> (int) $bed->Department,
                    'RoomID'      => (int) $bed->Room,
                    'BedID'       => (int) $bed->Bed,
                    'DoctorID'    => (int) $doctor->Doctor,
                    'PatientID'   => (int) $patient->ID,
                    'Temperature' => (float) (rand(350, 400)) / 10,
                    'SignIn'      => date("Y-m-d", rand($start,  time())),
                );

                $ts = strtotime( $data['SignIn'] );
                $SignOut = rand( $ts, $ts + (4 * 7 * 24 * 60 * 60) );
                if ( $SignOut < time() ) {
                    $data['SignOut'] = date("Y-m-d", $SignOut);
                }

                 create_if_not_exists( 'registry', $data );       
                 $n++;
            }
        }
    }

    var_dump($n);