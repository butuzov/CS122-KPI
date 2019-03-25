<?php 
    header("Content-Type: text/plain;");
    $data = file( __DIR__ ."/sp_08_SearchInHospitalBySpeciality.sql");
    
    foreach( $data as $k => $line ) {
      echo sprintf( "%'.02d    %s\n", $k+1, rtrim($line));
    }