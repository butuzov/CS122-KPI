<?php 

    set_time_limit(0);
    include_once "../conf.php"; 

    $data = $db->exec( "SELECT `LaboratoryID`, FacilityID, `Start` FROM laboratory_contracts" );

    // $types = $db->exec( "SELECT `LaboratoryID`, `Start` FROM laboratory_examination_types" );

    // var_dump($data, $types); 
    foreach( $data as $laboratory ) {
        var_dump($laboratory);

        $tests = $db->exec("
            SELECT * FROM  laboratory_examination_types WHERE Type = 'Test' AND ParentID in (
                SELECT ID FROM laboratory_examination_types WHERE ID IN (
                    SELECT ExaminationTypeInclude 
                    FROM laboratories 
                    WHERE LaboratoryID = $laboratory->LaboratoryID
                ) OR ParentID IN (
                    SELECT ExaminationTypeInclude 
                    FROM laboratories 
                    WHERE LaboratoryID = $laboratory->LaboratoryID
                )
            ) 
        ");

        $patients = $db->exec("SELECT * FROM `patients` WHERE Birth < '{$laboratory->Start}' ORDER BY RAND() LIMIT ".rand(300, 600));
                    

        foreach ( $patients as $patient ) {
            $data = [
                'LaboratoryID' => $laboratory->LaboratoryID,
                'FacilityID'   => $laboratory->FacilityID,
                'PatientID'    => $patient->ID,
                'Date'         => date("Y-m-d", rand(strtotime($laboratory->Start), time())),
                'ExaminationID'=> $tests[rand(0, count($tests)-1)]->ID,
            ];

            create_if_not_exists( 'laboratory_examinations', $data );
        } 
       

    }
 