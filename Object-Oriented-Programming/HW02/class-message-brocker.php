<?php

class Message_Brocker {
	private $dso;

	private $agregators = [];

	public function __construct( Message_Producer $mp ) {
		$this->dso = $mp;

	}

	public function run(){

		while( $this->dso->next() ) {
			$message = $this->dso->get();

			foreach( $this->agregators as $consumer ) {
				$consumer->consume( $message );
			}
		}

	}

	private function hasAgregators() : bool {
		return ! empty( $this->agregators );
	}


	public function subscribe( Message_Consumer $mc ) {
		foreach ( $this->agregators as $agr_mc ) {
			if ( $agr_mc == $mc ) {
				return;
			}
		}
		$this->agregators[] = $mc;
	}

	public function unsubscribe ( Message_Consumer $nc ) {
		if ( ! $this->hasAgregators() ) {
			return;
		}

		foreach ( $this->agregators as $k => $agr_mc ) {
			if ( $agr_mc == $mc ) {
				unset( $this->agregators[ $k ] );
				return;
			}
		}
	}
}