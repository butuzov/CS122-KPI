<?php
    set_time_limit(0);
    include_once "../conf.php";     

    $genders = ["Male", "Female"];
    $exts = ["050", "096", "097", "095", "078", "068" ];
    
    for ( $i = 0; $i < rand(1000, 2000); $i++ ) {

        $gender = $genders[rand(0,1)];

        $person = array(
            'Name' => name(strtolower($gender)[0]),
            'Gender' => $gender,
            'Phone' => sprintf("+38 (%s) %'3s-%'2s-%'2s", $exts[ rand(0, count($exts)-1)], 
                                            rand(100, 999), rand(0, 99), rand(0, 99) ),
            'Birth' => sprintf("%'04s-%'02s-%'02s", rand(1927, 2017), rand(1,2), rand(1,29)),
        );

        $db->insert('patients', $person);
    }