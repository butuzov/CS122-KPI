<?php

  for ( $i = 0; $i < 100; $i++){

      $list = array();
      while( count($list) != 32 ){
          $item = mt_rand(0, 99);
          if ( ! in_array( $item, $list ) ){
              $list[] = $item;
          }
      }
      file_put_contents(__DIR__ . '/tests.txt', implode(" ", $list).PHP_EOL, 8);

  }
