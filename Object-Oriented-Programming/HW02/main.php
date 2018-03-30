<?php
include_once 'core.php';

$mb = new Message_Brocker(
	new HackerNews(5)
);
$mb->subscribe(new Black_Hole());
$mb->run();