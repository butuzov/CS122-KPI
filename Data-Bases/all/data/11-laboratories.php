<?php 

    set_time_limit(0);
    include_once "../conf.php";    

    $data = file_get_contents('https://www.synevo.ua/uk/gde-sdat-analizy/kiev/');

    preg_match_all('/addresses="(.*?)"/si', $data, $m);

    foreach ( $m[1] as $item ) {

        $data = array(
            'Affiliation' => 'Sinevo',
            'Title'       => 'Лабораторія Sinevo',
            'Type'        => 'Laboratory',
            'Address'     => str_replace("Київ, ", "", $item),
        );

        $p = create_if_not_exists( 'facilities', $data );

        $tests = $db->exec("SELECT * FROM laboratory_examination_types 
            WHERE Type = 'Category' AND `ParentID` = 0 ORDER BY RAND() LIMIT 3");

        foreach ( $tests as $test ) {
            create_if_not_exists( 'laboratories',[
                'LaboratoryID' => $p[0]->ID,
                'ExaminationTypeInclude' => $test->ID,
            ]);
        }
    }
    

