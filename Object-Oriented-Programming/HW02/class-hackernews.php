<?php

/**
 * YCombinator aka HackerNews feed reader
 *
 * https://news.ycombinator.com/
 * https://github.com/HackerNews/API
 */
class  HackerNews implements Message_Producer {

	private $api     = 'https://hacker-news.firebaseio.com/v0/';

	private $limit   = 15;
	private $latest  = 0;
	private $feed;

	function __construct( int $limit ) {
		$this->limit = $limit;
		$this->feed = new SplDoublyLinkedList();
		$this->update_feed();
	}

	/**
	 * Return Object that implements Message
	 *
	 * @return Message
	 */
	public function get() : Message {
		return $this->feed->pop();
	}

	/**
	 * Checks if list empty?
	 *
	 * @return boolean
	 */
	public function next() : bool {
		return ! $this->feed->isEmpty();
	}


	public function update_feed() {
		$data  = $this->retrive( 'newstories.json' );
		$items = array_slice( $data, 0, $this->limit);


		for ( $i = $this->limit - 1; $i >= 0; $i-- ) {

			if ( ! isset( $items[ $i ] ) || $items[ $i ] < $this->latest ) {
				continue;
			}

			$item = $this->retrive( sprintf( 'item/%s.json', $items[ $i ] ) );

			if ( is_null( $item ) ) {
				continue;
			}

			$this->latest = $items[ $i ];

			$this->feed->push(
				new Message_Link( $item['title'],
					empty( $item['url'] ) ? "" : $item['url'] )
			);

			if ( $this->feed->count() > $this->limit ) {
				$this->feed->pop();
			}
		}
	}

	private function retrive( $endpoint ){
		return json_decode( file_get_contents( $this->api . $endpoint ), true );
	}

}