<?php 

    include_once "db.php";
    $db = new db( "mysql", "root", "123", "cursova");

    include "functions.php";

    $sql = get_sql('SQL_Statments/05-Academic-Title.sql');
    $results = $db->exec_t( "Call" );
   // SHOW PROFILES;
    var_dump( $results);