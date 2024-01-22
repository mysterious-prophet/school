<?php

// Kickstart the framework
$f3=require('lib/base.php');

if ((float)PCRE_VERSION<8.0)
	trigger_error('PCRE version is out of date');

// Load configuration
$f3->config('config.ini');
$f3->config('routes.ini');

//print_r($f3);
//echo '<br>', basename($f3->get('PATH'));


// web presentation
$f3->run();
