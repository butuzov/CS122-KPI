<?php

// Subjects

return array(

	// Група - Екзамени

	// Object Orientd Programming
	// array(
	// 	'name' => 'Object Orientd Programming',
	// 	'teacher' => array(
	// 		'name' => 'Rykhalskiy OU',
	// 	),
	// 	'checkpoints' => [
	// 		[
	// 			'type'     => 'ekzamen',
	// 			'is_final' => true,
	// 		],
	// 		[
	// 			'type'     => 'cursova',
	// 			'is_final' => true,
	// 		],
	// 	],
	// ),
	// Data Bases
	array(
		'name' => 'Data Bases',
		'teacher' => array(
			'name' => 'Muhin VE',
		),
		'checkpoints' => [
			[
				'type'     => 'ekzamen',
				'is_final' => true,
				'checkpoints' => [
					[
						'type'   => 'lab',
						'id'     => 'lab1',
						'points' => '33',
					],
					[
						'type' => 'lab',
						'id'   => 'lab2',
						'points' => '33',
					],
					[
						'type' => 'lab',
						'id'   => 'lab3',
						'points' => '33',
					],
				],
			],
			[
				'type'     => 'cursova',
				'is_final' => true,
			],
		],
	),
	// Computer Networks
	array(
		'name' => 'Computer Networks',
		'teacher' => array(
			'name' => 'Kuharev SO',
		),
		'checkpoints' => [
			[
				'type'     => 'ekzamen',
				'is_final' => true,
				'checkpoints' => [
					[
						'type'   => 'lab',
						'id'     => 'lab1',
					],
					[
						'type' => 'lab',
						'id'   => 'lab2',
					],
					[
						'type' => 'lab',
						'id'   => 'lab3',
					],
				],
			],
		],
	),
	// Probability Theory
	array(
		'name' => 'Probability Theory',
		'teacher' => array(
			'name' => 'Kaniovska IU',
		),
		'checkpoints' => [
			[
				'type'     => 'ekzamen',
				'is_final' => true,
				'checkpoints' => [
					[
						'type'   => 'rozrahunkova',
						'id'     => 'rozrahunkova',
					],
				],
			],
		],
	),
	// Operations Research
	array(
		'name' => 'Operations Research',
		'teacher' => array(
			'name' => 'Zaichenko OU',
		),
		'checkpoints' => [
			[
				'type'     => 'ekzamen',
				'is_final' => true,
				'checkpoints' => [
					[
						'type'   => 'rozrahunkova',
						'id'     => 'rozrahunkova',
					],
				],
			],
		],
	),
	// Група - Автоматичні Заліки

	// Calculus
	array(
		'name' => 'Calculus - 2',
		'teacher' => array(
			'name' => 'Baranovska LV',
		),
		'checkpoints' => null,
	),
	// Discrete Mathematics
	array(
		'name' => 'Discrete Mathematics',
		'teacher' => array(
			'name' => 'Spektorsky IJ',
		),
		'checkpoints' => null,
	),


	// Група - Заліки

	// Time Series
	array(
		'name' => 'Time Series Analysis',
		'teacher' => array(
			'name' => 'Biduk PI',
		),
		'checkpoints' => array(
			[
				'type'     => 'zalik',
				'is_final' => true,
				'checkpoints' => [
					[
						'type'   => 'lab',
						'id'     => 'lab1',
						'points' => '33',
					],
					[
						'type' => 'lab',
						'id'   => 'lab2',
						'points' => '33',
					],
					[
						'type' => 'lab',
						'id'   => 'lab3',
						'points' => '33',
					],
				],
			]
		),
	),

	// Numerical Analysis
	array(
		'name' => 'Numerical Analysis',
		'teacher' => array(
			'name' => 'Shubenkova IA',
		),
		'checkpoints' => array(
			[
				'type'     => 'zalik',
				'is_final' => true,
				'points'   => 100,
			]
		),
	),
);
