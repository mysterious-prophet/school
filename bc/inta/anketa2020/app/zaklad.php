<?php

class zaklad {
	protected $db; // pristup k DB

	//! HTTP route post-processor
	function afterroute() {
		//$f3->set('cesta','http://'.$_SERVER['SERVER_NAME']);// DODELAT! $f3
		// Render HTML layout
		echo Template::instance()->render('_layout.html');
		// echo View::instance()->render('layout.htm');
		$f3 = Base::instance();
		if (null !== $f3->get('SESSION.error'))
			$f3->clear('SESSION.error');
		if (null !== $f3->get('SESSION.ok'))
			$f3->clear('SESSION.ok');
	}

	//! Instantiate class
	function __construct() {
		$f3=Base::instance();
//		new Session();
		// Connect to the database
		$this->db = new DB\SQL($f3->get('db'));
		
		// Database creating
		if (file_exists('setup.sql')) {
			// Initialize database with default setup
			$this->db->exec(explode(';',$f3->read('setup.sql')));
			// Make default setup inaccessible
			rename('setup.sql','setup.$ql');
		}
	/*	// Use database-managed sessions
		new DB\SQL\Session($db);
		// Save frequently used variables
		$this->db=$db;
	*/
	}
	
	// test přihlášeného uživatele
	protected function test_logged() {
		$f3 = Base::instance();
		if (null == $f3->get('SESSION.userID')) {
			$f3->set('SESSION.error','Požadovanou akci smí provádět pouze přihlášený uživatel!');
			$f3->reroute('/');
		}
	}
		
	// vykreslení úvodní stránky
	function home(\Base $f3) {
        // $hash = password_hash("kopretina", PASSWORD_DEFAULT);
		// $f3->set('subtitle',"Úvodní stránka ... $hash");

//		$f3->set('subtitle',"Úvodní stránka"); // $hash");
//        $f3->set('content','home.html'); // jen úvodní text

        $anketa = new anketa();
        $prehled = $anketa->summary(); // metoda vrátí ankety s přidaným sloupcem
        $f3->set('ankety',$prehled); // předáme data pro VIEW (template)
        $f3->set('subtitle',"Přehled anket");
        $f3->set('content','ankety_prehled.html'); // přehled anket (front-end i back-end)
	}
	
}
