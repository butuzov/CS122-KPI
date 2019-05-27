<?php

class padre {
	public $text = "Soy padre";


	public function __construct(){
		printf("Empezar: %s\n", $this->text);
	}

	public function __destruct(){
		printf("Fin: %s\n", $this->text);
	}

	public function test(){
		echo $this->privado();
		echo $this->protegido();
	}

	private function privado(){
		echo "Soy privado\n";
	}

	protected function protegido(){
		echo "Soy protegido\n";
	}


}

class hijo extends padre {
	public $text = "Soy hijo";

	private function privado(){
		echo "Soy hijo privado\n";
	}

	protected function protegido(){
		echo "Soy hijo protegido\n";
	}
}


(new padre())->test();

echo str_repeat("-", 90) . PHP_EOL;

(new hijo())->test();
