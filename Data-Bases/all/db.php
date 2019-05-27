<?php

    /**
     * Abstraction Layer
     */
    class db   {
        
        private $query = [];
        private $result;
        private $db;


        function __construct( $host, $user, $pass, $name ) {
            $this->db = new mysqli( $host, $user, $pass, $name );
            $this->db->query("SET NAMES utf8mb4");
        }


        public function exists( $table, $conditions ) : bool {

            $query = sprintf(
                " SELECT count(*) as count FROM %s WHERE %s ", 
                $table,
                $this->and( $this->wrap( $conditions ) )
            );

            return $this->exec($query)[0]->count != 0;
        }

        public function exec_t( $query ){
            $t = microtime(true);
            $r = $this->exec( $query );
            return array(
                'time'    => microtime(true) - $t,
                'results' => $r
            );
        }

        public function exec( $query ) {
            $this->query = array();
            $this->query['query'] = trim($query);
            $this->query['type'] = substr($this->query['query'], 0, 
                                        strpos($this->query['query'], " ")); 

            if ( $this->query['type'] === "SELECT" ) {
                $results = array();

                if ($result = $this->db->query($this->query['query'])) {
                    while ($row = $result->fetch_object()){
                        $results[] = $row;
                    }
                    $result->close();
                } else {
                    die(var_dump("ERROR:", $this->db->error, $this->query));
                }

                return $results;
            }

            if ( $this->query['type'] === "DELETE" ) {
                return $this->db->query($this->query['query']);
            }

            $res = $this->db->query($this->query['query']);

             
            
        }

        public function update( $table, $id, $args ) {
            
            $update = $this->and( $this->wrap( $args ) );
            $query = sprintf(" UPDATE %s SET %s WHERE ID = %d", $table, $update, $id);
            $this->exec($query);

            return $this->get( $table, ['ID' => $id ] );
        }



        private function pair( $key, $value ){
            return sprintf("`%s` = '%s'", $key, $this->db->escape_string($value) );
        }

        private function wrap( $args ) {
            
            if ( is_string( $conditions ) ) {
                return  $conditions;
            }

            return array_map( [ $this, 'pair' ], array_keys($args), array_values($args));
        }

        public function and( $args ){
            return implode(" AND ", $args );
        }

        public function comma( $args ) {
            return implode(", ", $args );
        }

        public function drop( $table, $conditions ){
            
            $delete = $this->wrap( $conditions );
            $query = sprintf( "DELETE FROM %s WHERE %s", 
                $table, $this->and( $this->wrap( $conditions ) ) );

            $this->exec( $query );
        }

        public function insert( $table, $conditions ) {
            $query = sprintf(
                "INSERT INTO %s (%s) VALUES (%s)", $table,
                
                // Keys 
                implode( ',', array_map( function( $i ){
                    return "`{$i}`";
                }, array_keys( $conditions ) ) ),

                // Values
                implode( ',', array_map( function( $i ){
                    return sprintf("'%s'", $this->db->escape_string($i));
                }, array_values( $conditions ) ) )
            );
            
            $r = $this->exec($query);
            
           var_dump($r, $this->db);

            return $this->get( $table, $conditions );
        }

        public function get( $table, $conditions ) {
            $query = sprintf(
                "SELECT * FROM %s WHERE %s ", 
                $table,
                $this->and( $this->wrap( $conditions ) )
            );

//            var_dump( 'GET:', $query );

            return $this->exec($query);
        }


        
        
    }   